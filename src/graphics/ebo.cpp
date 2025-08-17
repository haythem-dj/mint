#include "mint/graphics/ebo.hpp"

#include "mint/render_backend/opengl/gl_ebo.hpp"

namespace mnt::graphics
{
    ebo::ebo()
    {}

    ebo::~ebo()
    {}

    std::shared_ptr<ebo> ebo::create()
    {
        return std::make_shared<gl_ebo>();
    }
}