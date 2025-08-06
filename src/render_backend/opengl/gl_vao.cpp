#include "mint/render_backend/opengl/gl_vao.hpp"

#include "mint/core/engine.hpp"

#include "mint/graphics/vbo.hpp"
#include "mint/graphics/ebo.hpp"

#include <glad/gl.h>

namespace mnt::graphics
{
    gl_vao::gl_vao()
    {}

    gl_vao::~gl_vao()
    {}

    b8 gl_vao::initialize()
    {
        if (m_is_initialized) return false;

        glGenVertexArrays(1, &m_id);
        
        m_is_initialized = true;
        return true;
    }

    void gl_vao::shutdown()
    {
        if (!m_is_initialized) return;

        glDeleteVertexArrays(1, &m_id);
    }

    void gl_vao::bind() const
    {
        glBindVertexArray(m_id);
        if (!m_ebo) return;

        m_ebo->bind();
    }

    void gl_vao::unbind() const
    {
        glBindVertexArray(0);
        if (!m_ebo) return;

        m_ebo->unbind();
    }

    void gl_vao::add_vertex_buffer(vbo* vbo, const std::vector<u32>& layout)
    {
        u32 stride = 0;
        for (u32 i : layout) stride += i;
        stride *= sizeof(float);

        bind();
        u32 offset = 0;
        for (u32 element : layout)
        {
            if (element > 4)
            {
                MINT_ERROR("vao::add_vertex_buffer - layout elements should be 1, 2, 3 or 4");
                return;
            }

            vbo->bind();
            glEnableVertexAttribArray(m_index);
            glVertexAttribPointer(m_index, element, GL_FLOAT, GL_FALSE, stride, (void*)(size)offset);
            offset += sizeof(f32) * element;

            m_index++;
        }
    }

    u32 gl_vao::get_element_count() const
    {
        if (!m_ebo)
        {
            MINT_WARN("vao::get_element_count - no ebo is set.");
            return 0;
        }

        return m_ebo->get_count();
    }
}

