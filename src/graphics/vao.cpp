#include "mint/graphics/vao.hpp"

#include "mint/render_backend/opengl/gl_vao.hpp"

namespace mnt::graphics
{
    vao::vao()
    {}

    vao::~vao()
    {}

    std::shared_ptr<vao> vao::create()
    {
        return std::make_shared<gl_vao>();
    }
}