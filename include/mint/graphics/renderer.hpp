#pragma once

#include "mint/common/defines.hpp"

#include "mint/math/vector.hpp"
#include "mint/core/window.hpp"

namespace mnt::graphics
{
    class vao;
    class shader;
    
    class MINT_API renderer
    {
    public:
        renderer();
        ~renderer();

        virtual b8 initialize(window* win) = 0;
        virtual void shutdown() = 0;

        virtual void begin_render() = 0;
        virtual void end_render() = 0;

        virtual void set_clear_color(const math::vector4& color) = 0;
        virtual void clear() = 0;

        virtual void draw_indexed(vao* vao, shader* shader) = 0;

        static renderer* create();

    protected:
        window* m_window = nullptr;
    };
}