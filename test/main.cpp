#include <mint/mint.hpp>

#include <mint/math/math.hpp>
#include <mint/math/vector.hpp>

#include <iostream>

class test_app : public mnt::application
{
public:
    b8 initialize() override
    {
        m_engine = &mnt::engine::get();
        m_renderer = &m_engine->get_renderer();
        return true;
    }

    void shutdown() override {}

    void update(f32 dt) override {}

    void render() override
    {
        // m_renderer->set_clear_color({0.5f, 0.65f, 0.14f, 1.0f});
        // m_renderer->clear();
    }

    void on_event(mnt::event& e) override
    {
        if (e.get_event_type() == mnt::event_type::key_press)
        {
            mnt::key_press kp = (mnt::key_press&)e;
            if (kp.get_key_code() == mnt::input::key_code::escape)
                mnt::engine::get().stop();
        }
    }

private:
    b8 on_key_press(mnt::key_press& kp)
    {
        MINT_TRACE("%s", kp.to_string());
        return false;
    }

private:
    mnt::engine* m_engine = nullptr;
    mnt::graphics::renderer* m_renderer = nullptr;
};

int main(void)
{
    mnt::engine& e = mnt::engine::get();
    test_app* app = new test_app();

    e.initialize(app);
    e.run();
    e.shutdown();

    return 0;
}
