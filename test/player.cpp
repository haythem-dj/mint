#include "player.hpp"

#include <math.h>

b8 player::initialize(const mnt::math::vector2& position)
{
    m_shader->initialize("res/shaders/test.vert.glsl", "res/shaders/test.frag.glsl");
    m_vao->initialize();

    f32 rect[] = {
        -2.0f, -2.0f, 0.0f, 0.0f, 0.0f,
        2.0f, -2.0f, 0.0f, 1.0f, 0.0f,
        2.0f,  2.0f, 0.0f, 1.0f, 1.0f,
        -2.0f,  2.0f, 0.0f, 0.0f, 1.0f
    };

    m_vbo->initialize(sizeof(rect), rect);
    m_vao->add_vertex_buffer(m_vbo, { 3, 2 });

    u32 rect_ind[] = {
        0, 1, 2, 0, 2, 3
    };

    m_ebo->initialize(6, rect_ind);
    m_vao->set_index_buffer(m_ebo);
    
    m_texture->initialize("res/textures/player.png");

    mnt::math::matrix4 tra = mnt::math::translate({ 0.0f, 0.0f, 0.0f });
    mnt::math::matrix4 rot = mnt::math::rotate({ 0.0f, 0.0f, 0.0f });

    m_transform = tra * rot;

    m_camera.initialize({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f });

    m_camera.on_resize(800, 600);
    m_camera.update();

    return true;
}

void player::shutdown()
{
    m_texture->shutdown();
    m_ebo->shutdown();
    m_vbo->shutdown();
    m_vao->shutdown();
    m_shader->shutdown();
}

void player::update(f32 dt)
{
    move(dt);
    rotate(dt);
    
    m_camera.update();

    m_shader->bind();
    m_shader->set_int1("u_diffuse", 0);
    m_shader->set_matrix4("u_transform", m_transform);
    m_shader->set_matrix4("u_view", m_camera.get_view());
    m_shader->set_matrix4("u_projection", m_camera.get_projection());
}

void player::render(mnt::graphics::renderer& renderer)
{
    m_texture->bind(0);
    renderer.draw_indexed(m_vao, m_shader);
}

void player::on_resize(u32 width, u32 height)
{
    m_camera.on_resize(width, height);
}

void player::rotate(f32 dt)
{
    m_rotation = 0.0f;

    if (MINT_IS_KEY_DOWN(mnt::input::key_code::left)) m_rotation -= m_rotation_speed * m_camera.get_up() * dt;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::right)) m_rotation += m_rotation_speed * m_camera.get_up() * dt;
    
    if (MINT_IS_KEY_DOWN(mnt::input::key_code::up)) m_rotation += m_rotation_speed * m_camera.get_right() * dt;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::down)) m_rotation -= m_rotation_speed * m_camera.get_right() * dt;
    
    if (MINT_IS_KEY_DOWN(mnt::input::key_code::k)) m_rotation_velocity.y = m_rotation_speed * dt;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::l)) m_rotation_velocity.y = -m_rotation_speed * dt;

    mnt::math::vector4 forward = mnt::math::vector4(m_camera.get_forward().x, m_camera.get_forward().y, m_camera.get_forward().z, 1.0f);
    mnt::math::vector4 new_forward = mnt::math::rotate(m_rotation) * forward;
    m_camera.set_forward(mnt::math::vector3(new_forward.x, new_forward.y, new_forward.z));
}

void player::move(f32 dt)
{
    if (MINT_IS_KEY_DOWN(mnt::input::key_code::q)) m_position -= m_camera.get_right() * m_speed * dt;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::d)) m_position += m_camera.get_right() * m_speed * dt;

    if (MINT_IS_KEY_DOWN(mnt::input::key_code::s)) m_position -= m_camera.get_up() * m_speed * dt;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::z)) m_position += m_camera.get_up() * m_speed * dt;

    m_camera.set_position(m_position);
}