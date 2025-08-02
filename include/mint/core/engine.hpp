#pragma once

#include "mint/common/defines.hpp"

#include "mint/core/logger.hpp"
#include "mint/core/window.hpp"

#include "mint/event/event.hpp"
#include "mint/event/window_events.hpp"

#include "mint/input/key_input.hpp"
#include "mint/input/mouse_input.hpp"

#include "mint/graphics/renderer.hpp"
#include "mint/graphics/shader.hpp"
#include "mint/graphics/vbo.hpp"
#include "mint/graphics/ebo.hpp"

namespace mnt
{
    class application;
    class MINT_API engine
    {
    public:
        engine(engine&) = delete;
        engine& operator=(const engine&) = delete;
        engine(engine&&) = delete;
        engine&& operator=(const engine&&) = delete;
        ~engine();

        static engine& get();

        b8 initialize(application* app);
        void shutdown();

        void on_event(event& e);

        void run();

        void stop() { m_is_running = false; }

        inline application& get_app() { return *m_app; }
        inline logger& get_logger() { return m_logger; }
        inline window& get_window() { return m_window; }
        inline input::keyboard& get_keyboard() { return m_keyboard; }
        inline input::mouse& get_mouse() { return m_mouse; }
        inline graphics::renderer& get_renderer() { return *m_renderer; }

    private:
        engine();

        void update(f32 dt);
        void render();

        b8 on_window_close(window_close& wc);
        b8 on_window_resize(window_resize& wr);

    private:
        b8 m_is_initialized = false;
        b8 m_is_running = false;

        application* m_app = nullptr;
        logger m_logger;
        window m_window;
        input::keyboard m_keyboard;
        input::mouse m_mouse;

        graphics::renderer* m_renderer;

        graphics::shader* m_test;
        u32 m_vao;
        graphics::vbo* m_vbo;
        graphics::ebo* m_ebo;

    private:
        static engine* s_instance;
    };
} // namespace mnt
