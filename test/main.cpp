#include <mint/mint.hpp>

struct mesh
{
    std::shared_ptr<mnt::graphics::vao> vao;
    std::shared_ptr<mnt::graphics::vbo> vbo;
    std::shared_ptr<mnt::graphics::ebo> ebo;

    void initialize()
    {
        vao = mnt::graphics::vao::create();
        vbo = mnt::graphics::vbo::create();
        ebo = mnt::graphics::ebo::create();
    }

    void shutdown()
    {
        ebo->shutdown();
        vbo->shutdown();
        vao->shutdown();
    }
};

class test_app : public mnt::application
{
public:
    b8 initialize() override
    {
        m_engine = &mnt::engine::get();
        m_renderer = &m_engine->get_renderer();

        m_shader = mnt::graphics::shader::create();
        m_shader->initialize("res/shaders/default.vert.glsl", "res/shaders/default.frag.glsl");

        m_mesh.initialize();
        m_mesh.vao->initialize();
        {
            f32 buffer[] = {
                -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,   0.0f, 0.0f,
                 0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   0.5f, 1.0f,
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f
            };
            m_mesh.vbo->initialize(sizeof(buffer), buffer);
        }

        {
            u32 buffer[] = { 0, 1, 2 };
            m_mesh.ebo->initialize(sizeof(buffer)/sizeof(u32), buffer);
        }

        m_tex = mnt::graphics::texture::create();
        m_tex->initialize("res/textures/brick/brick_diffuse.png");

        m_mesh.vao->add_vertex_buffer(m_mesh.vbo, {3, 4, 2});
        m_mesh.vao->set_index_buffer(m_mesh.ebo);
        
        m_renderer->set_clear_color({0.9f, 0.15f, 0.74f, 1.0f});

        m_shader->set_float4("u_color", { 1.0f, 0.0f, 0.0f, 1.0f });
        m_shader->set_int1("u_diffuse", 0);

        return true;
    }

    void shutdown() override
    {
        m_tex->shutdown();
        m_mesh.shutdown();
        m_shader->shutdown();
    }

    void render() override
    {
        m_renderer->clear();
        m_tex->bind(0);
        m_renderer->draw_indexed(m_mesh.vao, m_shader);
    }

    void on_event(mnt::event& e) override
    {
        if (e.get_event_type() == mnt::event_type::key_press)
        {
            mnt::key_press kp = (mnt::key_press&)e;
            if (kp.get_key_code() == mnt::input::key_code::escape)
                mnt::engine::get().stop();
        }
    }

private:
    mnt::engine* m_engine = nullptr;
    mnt::graphics::renderer* m_renderer = nullptr;

    std::shared_ptr<mnt::graphics::shader> m_shader;
    mesh m_mesh;
    std::shared_ptr<mnt::graphics::texture> m_tex;

};

int main(void)
{
    mnt::engine& e = mnt::engine::get();
    test_app* app = new test_app();

    e.initialize(app);
    e.run();
    e.shutdown();

    delete app;

    return 0;
}
