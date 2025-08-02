#pragma once

#include "mint/graphics/vbo.hpp"

namespace mnt::graphics
{
    class gl_vbo : public vbo
    {
    public:
        gl_vbo();
        ~gl_vbo();

        b8 initialize(u32 size, f32* data) override;
        void shutdown() override;

        void bind() const override;
        void unbind() const override;

    private:
        b8 m_is_initialized = false;
    };
}