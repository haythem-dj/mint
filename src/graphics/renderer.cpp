#include "mint/graphics/renderer.hpp"

#include "mint/render_backend/opengl/gl_renderer.hpp"

namespace mnt::graphics
{
    renderer::renderer()
    {}

    renderer::~renderer()
    {}

    renderer* renderer::create()
    {
        return new gl_renderer();
    }
}