#include <mint/mint.hpp>

#include <iostream>

class test_app : public mnt::application
{
public:
    b8 initialize() override { return true; }

    void shutdown() override {}

    void update(f32 dt) override
    {
        if (MINT_IS_KEY_DOWN(mnt::input::key_code::a)) MINT_DEBUG("a is down");
        if (MINT_IS_BUTTON_DOWN(mnt::input::mouse_button::left)) MINT_DEBUG("mouse left is down");
    }

    void render() override {}

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
