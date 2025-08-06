#pragma once

#include "mint/common/defines.hpp"

namespace mnt::graphics
{
    class MINT_API vbo
    {
    public:
        vbo();
        ~vbo();

        virtual b8 initialize(u32 size, f32* data) = 0;
        virtual void shutdown() = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        u32 get_id() const { return m_id; }

        static vbo* create();

    protected:
        u32 m_id = 0;
    };
}