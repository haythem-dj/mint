#pragma once

#include <mint/mint.hpp>

class player
{
public:
    b8 initialize(const mnt::math::vector2& pos);
    void shutdown();

    void update(f32 dt);
    void render(mnt::graphics::renderer& renderer);

    void on_resize(u32 width, u32 height);

private:
    void rotate(f32 dt);
    void move(f32 dt);

private:
    std::shared_ptr<mnt::graphics::shader> m_shader = mnt::graphics::shader::create();
    std::shared_ptr<mnt::graphics::vao> m_vao = mnt::graphics::vao::create();
    std::shared_ptr<mnt::graphics::vbo> m_vbo = mnt::graphics::vbo::create();
    std::shared_ptr<mnt::graphics::ebo> m_ebo = mnt::graphics::ebo::create();
    std::shared_ptr<mnt::graphics::texture> m_texture = mnt::graphics::texture::create();

    mnt::math::vector3 m_position{0.0f};
    mnt::math::vector3 m_rotation{90.0f, 0.0f, 0.0f};
    mnt::math::vector3 m_velocity{0.0f};
    mnt::math::vector3 m_rotation_velocity{0.0f};

    mnt::math::matrix4 m_transform;

    mnt::scene::orthographic_camera m_camera;

    f32 angle = 0.0f;

    const f32 m_speed = 3.0f;
    const f32 m_rotation_speed = 10.0f;
};