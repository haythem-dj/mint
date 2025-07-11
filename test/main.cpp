#include <mint/mint.hpp>

#include <iostream>

class test_app : public mnt::application
{
public:
    b8 initialize() override
    {
        return true;
    }

    void shutdown() override {}

    void update(f32 dt) override
    {
        MINT_TRACE("updating app.");
    }

    void render() override {}
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
