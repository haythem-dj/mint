#include "mint/render_backend/opengl/gl_ebo.hpp"

#include <glad/gl.h>

namespace mnt::graphics
{
    gl_ebo::gl_ebo()
    {}

    gl_ebo::~gl_ebo()
    {}

    b8 gl_ebo::initialize(u32 count, u32* data)
    {
        if (m_is_initialized) return false;
        
        m_count = count;
        
        glGenBuffers(1, &m_id);
        
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(u32), data, GL_STATIC_DRAW);

        m_is_initialized = true;
        return true;
    }

    void gl_ebo::shutdown()
    {
        glDeleteBuffers(1, &m_id);
    }

    void gl_ebo::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void gl_ebo::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}