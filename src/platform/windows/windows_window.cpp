#ifdef MINT_PLATFORM_WINDOWS

#include <glad/glad.h>
#include <windows.h>

#include "mint/core/engine.hpp"
#include "mint/core/logger.hpp"
#include "mint/core/window.hpp"

#include "mint/event/key_events.hpp"
#include "mint/event/mouse_events.hpp"
#include "mint/event/window_events.hpp"

#include "mint/input/key_codes.hpp"
#include "mint/input/mouse_buttons.hpp"

namespace mnt
{
    struct window_state
    {
        HWND hwnd;
        HINSTANCE hinstance;
        HDC device_context;
    };
    static window_state state{.hwnd = NULL, .hinstance = NULL, .device_context = NULL};

    static const char* CLASS_NAME = "window class name";

    static LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    window::window() {}

    window::~window() {}

    b8 window::initialize(const window_props& props)
    {
        if (m_is_initialized)
        {
            MINT_ERROR("Window is already initialized.");
            return false;
        }
        state.hinstance = GetModuleHandle(NULL);
        WNDCLASS wc;
        ZeroMemory(&wc, sizeof(WNDCLASS));
        wc.lpfnWndProc = window_proc;
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.hInstance = state.hinstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpszClassName = CLASS_NAME;

        if (!RegisterClass(&wc))
        {
            MessageBox(NULL, "Window Registration Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
            return false;
        }

        state.hwnd = CreateWindowEx(WS_EX_APPWINDOW, CLASS_NAME, props.title.c_str(), WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, props.width, props.height, NULL, NULL, state.hinstance, NULL);

        if (state.hwnd == NULL)
        {
            MessageBox(NULL, "Window Creation Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
            return false;
        }

        ShowWindow(state.hwnd, SW_SHOW);

        state.device_context = GetDC(state.hwnd);
        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int pixel_format = ChoosePixelFormat(state.device_context, &pfd);
        SetPixelFormat(state.device_context, pixel_format, &pfd);

        HGLRC context = wglCreateContext(state.device_context);
        wglMakeCurrent(state.device_context, context);

        MINT_INFO("Window initialized.");
        m_is_initialized = true;
        return true;
    }

    void window::shutdown()
    {
        if (!m_is_initialized) return;
        if (state.hwnd)
        {
            DestroyWindow(state.hwnd);
            state.hwnd = NULL;
            MINT_INFO("Window shuted down.");
            m_is_initialized = false;
        }
    }

    void window::update()
    {
        if (!m_is_initialized) return;
        MSG msg;
        while (PeekMessage(&msg, state.hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        SwapBuffers(state.device_context);
    }

    LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg)
        {
        case WM_CLOSE: {
            window_close wc(0);
            engine::get().on_event(wc);
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_SIZE: {
            RECT r;
            GetClientRect(state.hwnd, &r);
            u32 width = r.right - r.left;
            u32 height = r.bottom - r.top;
            window_resize wr(width, height);
            engine::get().on_event(wr);
        }
        break;

        case WM_KEYDOWN:
        case WM_KEYUP: 
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP: {
            b8 pressed = false;
            if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)
            {
                key_press kp((input::key_code)wparam);
                engine::get().on_event(kp);
                pressed = true;
            }
            else if (msg == WM_KEYUP || msg == WM_SYSKEYUP)
            {
                key_release kr((input::key_code)wparam);
                engine::get().on_event(kr);
            }
            input::key_code key = (input::key_code)wparam;
            input::process_key(key, pressed);
        }
        break;

        case WM_MOUSEMOVE: {
            i32 x = LOWORD(lparam);
            i32 y = HIWORD(lparam);
            mouse_move mv(x, y);
            engine::get().on_event(mv);
        }
        break;

        case WM_MOUSEWHEEL: {
            i32 delta = 0;
            if (GET_WHEEL_DELTA_WPARAM(wparam) < 0) delta = -1;
            else if (GET_WHEEL_DELTA_WPARAM(wparam) > 0)
                delta = 1;

            mouse_scroll ms(delta);
            engine::get().on_event(ms);
        }
        break;

        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP: {
            b8 pressed = msg == WM_LBUTTONDOWN || msg == WM_MBUTTONDOWN || msg == WM_RBUTTONDOWN;
            input::mouse_button button = input::mouse_button::none;

            if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) button = input::mouse_button::left;
            else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) button = input::mouse_button::right;
            else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) button = input::mouse_button::middle;

            if (button != input::mouse_button::none)
            {
                if (pressed)
                {
                    mouse_press mp(button);
                    engine::get().on_event(mp);
                } else {
                    mouse_release mr(button);
                    engine::get().on_event(mr);
                }
                input::process_button(button, pressed);
            }
        }
        break;
        }

        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
} // namespace mnt
#endif
