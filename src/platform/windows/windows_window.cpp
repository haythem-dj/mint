#ifdef MINT_PLATFORM_WINDOWS

#include <glad/gl.h>
#include <glad/wgl.h>
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
        HGLRC render_context;
    };
    static window_state state
    {
        .hwnd = NULL,
        .hinstance = NULL,
        .device_context = NULL,
        .render_context = NULL
    };

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

        RECT window_rect = {0, 0, (LONG)props.width, (LONG)props.height};
        AdjustWindowRectEx(&window_rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW);
        i32 adjusted_width = window_rect.right - window_rect.left;
        i32 adjusted_height = window_rect.bottom - window_rect.top;

        state.hwnd = CreateWindowEx(
            WS_EX_APPWINDOW,
            CLASS_NAME,
            props.title.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            adjusted_width,
            adjusted_height,
            NULL,
            NULL,
            state.hinstance,
            NULL
        );

        if (state.hwnd == NULL)
        {
            MessageBox(NULL, "Window Creation Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
            return false;
        }

        ShowWindow(state.hwnd, SW_SHOW);
        UpdateWindow(state.hwnd);

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
        if (pixel_format == 0)
        {
            MINT_ERROR("ChoosePixelFormat (dummy) failed. Error: %d", GetLastError());
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }
        if (!SetPixelFormat(state.device_context, pixel_format, &pfd))
        {
            MINT_ERROR("SetPixelFormat (dummy) failed. Error: %d", GetLastError());
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        HGLRC context = wglCreateContext(state.device_context);
        if (!context)
        {
            MINT_ERROR("wglCreateContext (dummy) failed. Error: %d", GetLastError());
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        if (!wglMakeCurrent(state.device_context, context))
        {
            MINT_ERROR("wglMakeCurrent (dummy) failed. Error: %d", GetLastError());
            wglDeleteContext(context);
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        if (!gladLoadWGL(state.device_context, (GLADloadfunc)wglGetProcAddress))
        {
            MINT_ERROR("Failed to load wgl extensions.");
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(context);
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        if (!GLAD_WGL_ARB_create_context || !GLAD_WGL_ARB_pixel_format)
        {
            MINT_ERROR("WGL_ARB_create_context or WGL_ARB_pixel_format is not supported!");
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(context);
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(context);

        const i32 pixel_attribs[] = {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
            WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
            WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
            WGL_COLOR_BITS_ARB,     32,
            WGL_ALPHA_BITS_ARB,     8,
            WGL_DEPTH_BITS_ARB,     24,
            WGL_STENCIL_BITS_ARB,   8,
            0
        };

        u32 num_formats;
        if (!wglChoosePixelFormatARB(state.device_context, pixel_attribs, NULL, 1, &pixel_format, &num_formats) || num_formats == 0)
        {
            MINT_ERROR("wglChoosePixelFormatARB failed. Error: %d", GetLastError());
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        DescribePixelFormat(state.device_context, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
        if (!SetPixelFormat(state.device_context, pixel_format, &pfd))
        {
            MINT_ERROR("SetPixelFormat (real) failed. Error: %d", GetLastError());
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        const i32 context_attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        state.render_context = wglCreateContextAttribsARB(state.device_context, NULL, context_attribs);
        if (!state.render_context)
        {
            MINT_ERROR("wglCreateContextAttribsARB failed. Error: %d", GetLastError());
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        if (!wglMakeCurrent(state.device_context, state.render_context))
        {
            MINT_ERROR("wglMakeCurrent (real) failed. Error: %d", GetLastError());
            wglDeleteContext(state.render_context);
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
            return false;
        }

        if (!gladLoaderLoadGL())
        {
            MINT_ERROR("Failed to init glad (core)");
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(state.render_context);
            ReleaseDC(state.hwnd, state.device_context);
            state.render_context = NULL;
            state.device_context = NULL;
            return false;
        }

        MINT_TRACE("OpenGL Version: %s", glGetString(GL_VERSION));
        MINT_TRACE("OpenGL Renderer: %s", glGetString(GL_RENDERER));
        glViewport(0, 0, props.width, props.height);

        MINT_INFO("Window initialized.");
        m_is_initialized = true;
        return true;
    }

    void window::shutdown()
    {
        if (!m_is_initialized) return;

        if (state.render_context)
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(state.render_context);
            state.render_context = NULL;
        }

        if (state.device_context)
        {
            ReleaseDC(state.hwnd, state.device_context);
            state.device_context = NULL;
        }

        if (state.hwnd)
        {
            DestroyWindow(state.hwnd);
            state.hwnd = NULL;
        }
        UnregisterClass(CLASS_NAME, state.hinstance);

        MINT_INFO("Window shuted down.");
        m_is_initialized = false;
    }

    void window::process_messages()
    {
        if (!m_is_initialized) return;
        MSG msg;
        while (PeekMessage(&msg, state.hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    b8 window::make_current_context()
    {
        if (!m_is_initialized) return false;
        if (!state.device_context) return false;
        if (!state.render_context) return false;

        return wglMakeCurrent(state.device_context, state.render_context);
    }

    void window::swap_buffers()
    {
        if (!m_is_initialized) return;

        SwapBuffers(state.device_context);
    }

    void* window::get_window_handle() const
    {
        return state.hwnd;
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


            input::process_position(x, y);
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
