#include "mint/graphics/vbo.hpp"

#include "mint/render_backend/opengl/gl_vbo.hpp"

namespace mnt::graphics
{
    vbo::vbo()
    {}

    vbo::~vbo()
    {}

    vbo* vbo::create()
    {
        return new gl_vbo();
    }
}