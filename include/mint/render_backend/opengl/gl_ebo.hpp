#pragma once

#include "mint/graphics/ebo.hpp"

namespace mnt::graphics
{
    class gl_ebo : public ebo
    {
    public:
        gl_ebo();
        ~gl_ebo();

        b8 initialize(u32 count, u32* data) override;
        void shutdown() override;

        void bind() const override;
        void unbind() const override;

    private:
        b8 m_is_initialized = false;
    };
}