#include <mint/mint.hpp>

#include "test.hpp"

int main(void)
{
    mnt::engine& e = mnt::engine::get();
    test* app = new test();

    e.initialize(app);
    e.run();
    e.shutdown();

    delete app;

    return 0;
}
