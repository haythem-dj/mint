#include "mint/graphics/ebo.hpp"

#include "mint/render_backend/opengl/gl_ebo.hpp"

namespace mnt::graphics
{
    ebo::ebo()
    {}

    ebo::~ebo()
    {}

    ebo* ebo::create()
    {
        return new gl_ebo();
    }
}