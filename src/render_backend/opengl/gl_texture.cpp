#include "mint/render_backend/opengl/gl_texture.hpp"

#include "mint/core/engine.hpp"

#include <glad/gl.h>
#include <stb_image/stb_image.h>

namespace mnt::graphics
{
    gl_texture::gl_texture()
    {}

    gl_texture::~gl_texture()
    {}

    b8 gl_texture::initialize(const std::string& path)
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        i32 width, height, channels;
        u8* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (!data)
        {
            MINT_ERROR("texture::initialize - could not open file: %s", path);
            return false;
        }

        u32 internal_format = 0;
        u32 data_format = 0;

        if (channels == 3)
        {
            internal_format = GL_RGB8;
            data_format = GL_RGB;
        }
        else if (channels == 4)
        {
            internal_format = GL_RGBA8;
            data_format = GL_RGBA;
        }
        else
        {
            MINT_ERROR("texture::initialize - unsipported image format: %s", path.c_str());
            return false;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        return true;
    }

    void gl_texture::shutdown()
    {
        glDeleteTextures(1, &m_id);
    }

    void gl_texture::bind(u32 slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void gl_texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}