#pragma once

#include "mint/common/defines.hpp"

#include "mint/math/vector3.hpp"
#include "mint/math/matrix4.hpp"

namespace mnt::scene
{
    class MINT_API orthographic_camera
    {
    public:
        orthographic_camera();
        ~orthographic_camera();

        b8 initialize(const math::vector3& position, const math::vector3& forward);
        void shutdown();

        void on_resize(u32 width, u32 height);
        void update();

        void set_position(const math::vector3& position) { m_position = position; }

        void set_forward(const math::vector3& forward) { m_forward = forward; }

        const math::vector3& get_position() const { return m_position; }

        const math::vector3& get_forward() const { return m_forward; }
        const math::vector3& get_right() const { return m_right; }
        const math::vector3& get_up() const { return m_up; }

        const math::matrix4& get_view() const { return m_view; }
        const math::matrix4& get_projection() const { return m_projection; }

    private:
        math::vector3 m_position;

        math::vector3 m_forward;
        math::vector3 m_right;
        math::vector3 m_up;

        math::matrix4 m_view;
        math::matrix4 m_projection;
        
    };
}