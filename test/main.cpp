#include <mint/mint.hpp>

class test_app : public mnt::application
{
public:
    b8 initialize() override
    {
        return true;
    }

    void shutdown() override
    {}

    void update(f32 dt) override
    {}

    void render() override
    {}
};

int main(void)
{
    mnt::engine& e = mnt::engine::get();
    test_app* app = new test_app();
    
    e.initialize(app);

    MINT_FATAL("this is fatal message");

    e.run();
    e.shutdown();

    return 0;
}
