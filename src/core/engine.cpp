#include "mint/core/engine.hpp"

#include "mint/core/application.hpp"

namespace mnt
{
    engine* engine::s_instance = nullptr;

    engine::engine()
    {}

    engine::~engine()
    {}

    engine& engine::get()
    {
        if (!s_instance) s_instance = new engine();
        return *s_instance;
    }

    b8 engine::initialize(application* app)
    {
        if (m_is_initialized) return false;

        if (!m_logger.initialize("MINT")) return false;
        m_logger.log_message(LOG_LEVEL_TRACE, "initializing the engine.");

        m_app = app;
        if (!m_app->initialize()) return false;

        m_is_initialized = true;
        return true;
    }

    void engine::shutdown()
    {
        m_app->shutdown();
        m_logger.shutdown();
    }

    void engine::on_event(event& e)
    {
        event_dispatcher dispatcher(e);
        dispatcher.dispatch<window_close>(
            [this](window_close& e) {
                return this->on_window_close(e);
            }
        );
    }

    void engine::run()
    {}

    void engine::update(f32 dt)
    {}

    void engine::render()
    {}

    bool engine::on_window_close(window_close& wc)
    {
        MINT_TRACE(wc.to_string());
    }
}