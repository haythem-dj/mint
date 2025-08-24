#include "player.hpp"

#include <math.h>

b8 player::initialize(const mnt::math::vector2& position)
{
    m_position = position;

    m_shader->initialize("res/shaders/test.vert.glsl", "res/shaders/test.frag.glsl");
    m_vao->initialize();

    f32 rect[] = {
        -0.2f, -0.2f, 0.0f, 0.0f, 0.0f,
        0.2f, -0.2f, 0.0f, 1.0f, 0.0f,
        0.2f,  0.2f, 0.0f, 1.0f, 1.0f,
        -0.2f,  0.2f, 0.0f, 0.0f, 1.0f
    };

    m_vbo->initialize(sizeof(rect), rect);
    m_vao->add_vertex_buffer(m_vbo, { 3, 2 });

    u32 rect_ind[] = {
        0, 1, 2, 0, 2, 3
    };

    m_ebo->initialize(6, rect_ind);
    m_vao->set_index_buffer(m_ebo);

    m_texture->initialize("res/textures/player.png");

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
    rotate(dt);

    m_rotation += m_rotation_velocity;
    mnt::math::matrix4 rot = mnt::math::rotate(m_rotation);
    
    move(dt);

    m_direction.normalize();
    m_velocity = m_direction * m_speed * dt;
    
    m_position += m_velocity;
    mnt::math::matrix4 tra = mnt::math::translate(mnt::math::vector3(m_position.x, m_position.y, 0));

    m_transform = tra * rot;

    m_shader->bind();
    m_shader->set_int1("u_diffuse", 0);
    m_shader->set_matrix4("u_transform", m_transform);
}

void player::render(mnt::graphics::renderer& renderer)
{
    m_texture->bind(0);
    renderer.draw_indexed(m_vao, m_shader);
}

void player::rotate(f32 dt)
{
    if (MINT_IS_KEY_DOWN(mnt::input::key_code::left)) m_rotation_velocity.z = m_rotation_speed * dt;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::right)) m_rotation_velocity.z = -m_rotation_speed * dt;
    else m_rotation_velocity.z = 0.0f;

    if (MINT_IS_KEY_DOWN(mnt::input::key_code::up)) m_rotation_velocity.x = m_rotation_speed * dt;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::down)) m_rotation_velocity.x = -m_rotation_speed * dt;
    else m_rotation_velocity.x = 0.0f;
    
    if (MINT_IS_KEY_DOWN(mnt::input::key_code::k)) m_rotation_velocity.y = m_rotation_speed * dt;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::l)) m_rotation_velocity.y = -m_rotation_speed * dt;
    else m_rotation_velocity.y = 0.0f;
}

void player::move(f32 dt)
{
    if (MINT_IS_KEY_DOWN(mnt::input::key_code::q)) m_direction.x = -1.0f;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::d)) m_direction.x = 1.0f;
    else m_direction.x = 0.0f;

    if (MINT_IS_KEY_DOWN(mnt::input::key_code::s)) m_direction.y = -1.0f;
    else if (MINT_IS_KEY_DOWN(mnt::input::key_code::z)) m_direction.y = 1.0f;
    else m_direction.y = 0.0f;
}