#include "mint/render_backend/opengl/gl_renderer.hpp"

#include "mint/core/logger.hpp"
#include "mint/core/engine.hpp"

#include <glad/gl.h>

namespace mnt::graphics
{
    gl_renderer::gl_renderer()
    {}

    gl_renderer::~gl_renderer()
    {}

    b8 gl_renderer::initialize(window* win)
    {
        if (m_is_initialized) return false;

        if (!win)
        {
            MINT_ERROR("gl_renderer::initialize - invalide window.");
            return false;
        }

        m_window = win;
        
        MINT_INFO("GL Renderer initialized.");
        m_is_initialized = true;
        return true;
    }

    void gl_renderer::shutdown()
    {
        if (!m_is_initialized) return;
        
        m_window = nullptr;
    }

    void gl_renderer::begin_render()
    {
        m_window->make_current_context();
    }

    void gl_renderer::end_render()
    {
        m_window->swap_buffers();
    }

    void gl_renderer::set_clear_color(const math::vector4& color)
    {
        if (!m_is_initialized) return;

        glClearColor(color.r, color.g, color.b, color.a);
    }

    void gl_renderer::clear()
    {
        if (!m_is_initialized) return;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}