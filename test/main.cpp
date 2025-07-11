#include <mint/mint.hpp>

class test_app : public mnt::application
{
public:
    b8 initialize() override { return true; }

    void shutdown() override {}

    void update(f32 dt) override {}

    void render() override {}
};

bool on_close(mnt::event& ev)
{
    MINT_TRACE(ev.to_string());
    return false;
}

int main(void)
{
    mnt::engine& e = mnt::engine::get();
    test_app* app = new test_app();

    e.initialize(app);

    MINT_FATAL("FATAL");
    MINT_ERROR("ERROR");
    MINT_WARN("WARN");
    MINT_INFO("INFO");
    MINT_DEBUG("DEBUG");
    MINT_TRACE("TRACE");

    mnt::window_close cls(15);
    mnt::window_resize rsz(1920, 1080);
    mnt::key_press kprs(41);
    mnt::key_release krls(41);
    mnt::mouse_press mprs(1);
    mnt::mouse_release mrls(1);
    mnt::mouse_move mv(150, 150);
    mnt::mouse_scroll scrl(-1);

    e.on_event(cls);

    e.run();
    e.shutdown();

    return 0;
}
