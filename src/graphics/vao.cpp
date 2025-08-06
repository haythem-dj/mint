#include "mint/graphics/vao.hpp"

#include "mint/render_backend/opengl/gl_vao.hpp"

namespace mnt::graphics
{
    vao::vao()
    {}

    vao::~vao()
    {}

    vao* vao::create()
    {
        return new gl_vao();
    }
}