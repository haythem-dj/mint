#pragma once

#include "mint/common/defines.hpp"

#include "mint/event/event.hpp"

namespace mnt
{
    class MINT_API application
    {
    public:
        application(){};
        virtual ~application() {}

        virtual b8 initialize() { return true; }
        virtual void shutdown() {};

        virtual void update(f32 dt) { (void)dt; }
        virtual void render() {}

        virtual void on_event(event& event) { (void)event; }
        virtual void on_resize(u32 width, u32 height) { (void)width; (void)height; }
    };
} // namespace mnt
