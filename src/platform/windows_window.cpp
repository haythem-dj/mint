#ifdef MINT_PLATFORM_WINDOWS

#include <windows.h>

#include "mint/core/engine.hpp"
#include "mint/core/logger.hpp"
#include "mint/core/window.hpp"

#include "mint/event/key_events.hpp"
#include "mint/event/mouse_events.hpp"
#include "mint/event/window_events.hpp"

namespace mnt
{
    struct window_state
    {
        HWND hwnd;
        HINSTANCE hinstance;
    };
    static window_state state{.hwnd = NULL, .hinstance = NULL};

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
            MessageBox(NULL, "Window Regestration Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
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

            // case WM_KEYDOWN:
            // case WM_KEYUP:
            // case WM_SYSKEYDOWN:
            // case WM_SYSKEYUP: {
            // }
            // break;

            // case WM_MOUSEMOVE: {
            // }
            // break;

            // case WM_MOUSEWHEEL: {
            // }
            // break;

            // case WM_LBUTTONDOWN:
            // case WM_MBUTTONDOWN:
            // case WM_RBUTTONDOWN:
            // case WM_LBUTTONUP:
            // case WM_MBUTTONUP:
            // case WM_RBUTTONUP: {
            // }
            // break;
        }

        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
} // namespace mnt
#endif
