#pragma once

#include "mint/common/defines.hpp"

namespace mnt::graphics
{
    class MINT_API ebo
    {
    public:
        ebo();
        ~ebo();

        virtual b8 initialize(u32 count, u32* data) = 0;
        virtual void shutdown() = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        u32 get_id() const { return m_id; }

        static ebo* create();

    protected:
        u32 m_id = 0;
    };
}