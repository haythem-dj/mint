#include "mint/graphics/texture.hpp"

#include "mint/render_backend/opengl/gl_texture.hpp"

namespace mnt::graphics
{
    texture::texture()
    {}

    texture::~texture()
    {}

    std::shared_ptr<texture> texture::create()
    {
        return std::make_shared<gl_texture>();
    }
}