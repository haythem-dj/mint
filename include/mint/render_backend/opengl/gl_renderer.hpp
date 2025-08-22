#pragma once

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

        void on_resize(u32 width, u32 height) override;

        void begin_render() override;
        void end_render() override;

        void set_clear_color(const math::vector4& color) override;
        void clear() override;

        void draw_indexed(std::shared_ptr<vao> vao, std::shared_ptr<shader> shader) override;

    private:
        b8 m_is_initialized = false;
    };
}