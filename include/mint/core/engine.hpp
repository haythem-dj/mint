#pragma once

#include "mint/common/defines.hpp"

#include "mint/core/logger.hpp"

#include "mint/event/event.hpp"
#include "mint/event/window_events.hpp"

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

        inline application& get_app() { return *m_app; }
        inline logger& get_logger() { return m_logger; }
    
    private:
        engine();

        void update(f32 dt);
        void render();

        bool on_window_close(window_close& wc);
    
    private:
        b8 m_is_initialized = false;
        
        application* m_app = nullptr;
        logger m_logger;

    private:
        static engine* s_instance;
    };
}