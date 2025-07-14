#pragma once

#include "mint/common/defines.hpp"

#include "mint/event/event.hpp"

namespace mnt
{
    class MINT_API application
    {
    public:
        application(){};
        virtual ~application(){};

        virtual b8 initialize() = 0;
        virtual void shutdown() = 0;

        virtual void update(f32 dt) = 0;
        virtual void render() = 0;

        virtual void on_event(event& event) = 0;
    };
} // namespace mnt
