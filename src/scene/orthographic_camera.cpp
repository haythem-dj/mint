#include "mint/scene/orthographic_camera.hpp"

#include "mint/math/math.hpp"
#include "mint/math/vector4.hpp"

#include "mint/core/engine.hpp"

namespace mnt::scene
{
    orthographic_camera::orthographic_camera()
    {}

    orthographic_camera::~orthographic_camera()
    {}

    b8 orthographic_camera::initialize(const math::vector3& position, const math::vector3& forward)
    {
        m_position = position;
        m_forward = forward;
        return true;
    }

    void orthographic_camera::shutdown()
    {}

    void orthographic_camera::on_resize(u32 width, u32 height)
    {
        f32 aspect = (f32)width / (f32)height;
        m_projection = mnt::math::orthographic(-aspect, aspect, -1.0f, 1.0f, -100.0f, 100.0f);
        MINT_DEBUG("projection:");
        MINT_DEBUG("\t%f, %f, %f, %f", m_projection[0][0], m_projection[0][1], m_projection[0][2], m_projection[0][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_projection[1][0], m_projection[1][1], m_projection[1][2], m_projection[1][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_projection[2][0], m_projection[2][1], m_projection[2][2], m_projection[2][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_projection[3][0], m_projection[3][1], m_projection[3][2], m_projection[3][3]);
    }

    void orthographic_camera::update()
    {
        m_forward.normalize();
        
        math::vector3 world_up{ 0.0f, 1.0f, 0.0f };

        m_right = m_forward ^ world_up;
        m_up = m_right ^ m_forward;

        MINT_DEBUG("forward: %f, %f, %f", m_forward.x, m_forward.y, m_forward.z);
        MINT_DEBUG("right: %f, %f, %f", m_right.x, m_right.y, m_right.z);
        MINT_DEBUG("up: %f, %f, %f", m_up.x, m_up.y, m_up.z);

        // m_view = math::view(m_position, m_forward, m_right, m_up);

        m_view = math::matrix4();
        MINT_DEBUG("view0:");
        MINT_DEBUG("\t%f, %f, %f, %f", m_view[0][0], m_view[0][1], m_view[0][2], m_view[0][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_view[1][0], m_view[1][1], m_view[1][2], m_view[1][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_view[2][0], m_view[2][1], m_view[2][2], m_view[2][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_view[3][0], m_view[3][1], m_view[3][2], m_view[3][3]);

        m_view = math::view(m_position, m_forward, m_right, m_up);

        MINT_DEBUG("view:");
        MINT_DEBUG("\t%f, %f, %f, %f", m_view[0][0], m_view[0][1], m_view[0][2], m_view[0][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_view[1][0], m_view[1][1], m_view[1][2], m_view[1][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_view[2][0], m_view[2][1], m_view[2][2], m_view[2][3]);
        MINT_DEBUG("\t%f, %f, %f, %f", m_view[3][0], m_view[3][1], m_view[3][2], m_view[3][3]);
    }
}