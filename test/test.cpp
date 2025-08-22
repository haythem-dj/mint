#include "test.hpp"

b8 test::initialize()
{
    m_engine = &mnt::engine::get();
    m_renderer = &m_engine->get_renderer();

    if (!m_player.initialize({0.0f, 0.0f})) return false;

    return true;
}

void test::shutdown()
{
    m_player.shutdown();
    m_engine = nullptr;
    m_renderer = nullptr;
}

void test::update(f32 dt)
{
    m_player.update(dt);
}

void test::render()
{
    m_renderer->clear();
    m_player.render(*m_renderer);
}

void test::on_event(mnt::event& event)
{
    if (event.get_event_type() == mnt::event_type::key_press)
    {
        mnt::key_press kp = (mnt::key_press&)event;
        if (kp.get_key_code() == mnt::input::key_code::escape)
            m_engine->stop();
    }
}