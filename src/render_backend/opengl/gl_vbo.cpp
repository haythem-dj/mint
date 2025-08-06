#include "mint/render_backend/opengl/gl_vbo.hpp"

#include <glad/gl.h>

namespace mnt::graphics
{
    gl_vbo::gl_vbo()
    {}

    gl_vbo::~gl_vbo()
    {}

    b8 gl_vbo::initialize(u32 size, f32* data)
    {
        if (m_is_initialized) return false;
        glGenBuffers(1, &m_id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        m_is_initialized = true;
        return true;
    }

    void gl_vbo::shutdown()
    {
        glDeleteBuffers(1, &m_id);
    }

    void gl_vbo::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void gl_vbo::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}