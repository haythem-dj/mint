#pragma once

#include "mint/common/defines.hpp"

namespace mnt
{
    class MINT_API application
    {
    public:
        application() {};
        virtual ~application() {};

        virtual b8 initialize() = 0;
        virtual void shutdown() = 0;
        virtual void update(f32 dt) = 0;
        virtual void render() = 0;
    };
}