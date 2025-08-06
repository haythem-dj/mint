#include "mint/graphics/texture.hpp"

#include "mint/render_backend/opengl/gl_texture.hpp"

namespace mnt::graphics
{
    texture::texture()
    {}

    texture::~texture()
    {}

    texture* texture::create()
    {
        return new gl_texture();
    }
}