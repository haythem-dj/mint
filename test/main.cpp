#include <mint/mint.hpp>

struct mesh
{
    mnt::graphics::vao* vao;
    mnt::graphics::vbo* vbo;
    mnt::graphics::ebo* ebo;

    void initialize()
    {
        vao = mnt::graphics::vao::create();
        vbo = mnt::graphics::vbo::create();
        ebo = mnt::graphics::ebo::create();
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
        m_shader->initialize(mnt::graphics::shader_init_type::file, "res/shaders/default.vert.glsl", "res/shaders/default.frag.glsl");

        test_mesh.initialize();
        test_mesh.vao->initialize();
        {
            f32 buffer[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
            };
            // f32 buffer[] = {
            //     -0.5f, -0.5f, 0.0f,
            //     0.0f, 0.5f, 0.0f,
            //     0.5f, -0.5f, 0.0f
            // };
            test_mesh.vbo->initialize(sizeof(buffer), buffer);
        }

        {
            u32 buffer[] = { 0, 1, 2 };
            test_mesh.ebo->initialize(sizeof(buffer)/sizeof(u32), buffer);
        }

        test_mesh.vao->add_vertex_buffer(test_mesh.vbo, {3, 4});
        test_mesh.vao->set_index_buffer(test_mesh.ebo);
        
        m_renderer->set_clear_color({0.9f, 0.15f, 0.74f, 1.0f});

        return true;
    }

    void render() override
    {
        m_renderer->clear();
        m_renderer->draw_indexed(test_mesh.vao, m_shader);
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

    mnt::graphics::shader* m_shader;
    mesh test_mesh;

};

int main(void)
{
    mnt::engine& e = mnt::engine::get();
    test_app* app = new test_app();

    e.initialize(app);
    e.run();
    e.shutdown();

    return 0;
}
