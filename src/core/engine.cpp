#include "mint/core/engine.hpp"

#include "mint/core/application.hpp"
#include "mint/core/window.hpp"

namespace mnt
{
    engine* engine::s_instance = nullptr;

    engine::engine() {}

    engine::~engine() {}

    engine& engine::get()
    {
        if (!s_instance) s_instance = new engine();
        return *s_instance;
    }

    b8 engine::initialize(application* app)
    {
        if (m_is_initialized) return false;

        if (!m_logger.initialize("MINT")) return false;

        window_props props;
        if (!m_window.initialize(props)) return false;

        if (!m_keyboard.initialize()) return false;
        if (!m_mouse.initialize()) return false;

        m_renderer = graphics::renderer::create();
        if (!m_renderer->initialize(&m_window)) return false;

        m_app = app;
        if (!m_app->initialize()) return false;

        m_is_initialized = true;
        MINT_INFO("Engine initialized.");
        m_is_running = true;
        return true;
    }

    void engine::shutdown()
    {
        m_app->shutdown();
        m_renderer->shutdown();
        m_keyboard.shutdown();
        m_mouse.shutdown();
        m_window.shutdown();
        m_logger.shutdown();
        MINT_INFO("Engine shuted down");
        m_is_initialized = false;
    }

    void engine::on_event(event& e)
    {
        if (!m_is_initialized) return;
        event_dispatcher dispatcher(e);
        dispatcher.dispatch<window_close>([this](window_close& e) { return this->on_window_close(e); });
        dispatcher.dispatch<window_resize>([this](window_resize& e) { return this->on_window_resize(e); });

        m_app->on_event(e);
    }

    void engine::run()
    {
        while (m_is_running)
        {
            update(1);
            render();
        }
    }

    void engine::update(f32 dt)
    {
        m_window.process_messages();
        m_keyboard.update();
        m_app->update(dt);
    }

    void engine::render()
    {
        m_renderer->begin_render();
        m_app->render();
        m_renderer->end_render();
    }

    b8 engine::on_window_close(window_close& wc)
    {
        m_is_running = false;
        MINT_TRACE("Exiting with code: %d", wc.get_code());
        return true;
    }

    b8 engine::on_window_resize(window_resize& wr) { return false; }
} // namespace mnt
