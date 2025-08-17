#include "mint/graphics/vbo.hpp"

#include "mint/render_backend/opengl/gl_vbo.hpp"

namespace mnt::graphics
{
    vbo::vbo()
    {}

    vbo::~vbo()
    {}

    std::shared_ptr<vbo> vbo::create()
    {
        return std::make_shared<gl_vbo>();
    }
}