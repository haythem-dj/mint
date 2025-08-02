#pragma once

#include "mint/common/defines.hpp"

#include "mint/graphics/renderer.hpp"

namespace mnt::graphics
{
    class gl_renderer : public renderer
    {
    public:
        gl_renderer();
        ~gl_renderer();

        b8 initialize(window* win) override;
        void shutdown() override;

        void begin_render() override;
        void end_render() override;

        void set_clear_color(const math::vector4& color) override;
        void clear() override;

    private:
        b8 m_is_initialized = false;
    };
}