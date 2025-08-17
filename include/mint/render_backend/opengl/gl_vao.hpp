#pragma once

#include "mint/graphics/vao.hpp"

namespace mnt::graphics
{
    class gl_vao : public vao
    {
    public:
        gl_vao();
        ~gl_vao();

        b8 initialize() override;
        void shutdown() override;

        void bind() const override;
        void unbind() const override;

        void add_vertex_buffer(std::shared_ptr<vbo> vbo, const std::vector<u32>& layout) override;
        void set_index_buffer(std::shared_ptr<ebo> ebo) override { m_ebo = ebo; }

        u32 get_element_count() const override;

    private:
        b8 m_is_initialized = false;

        std::shared_ptr<ebo> m_ebo = nullptr;

        u32 m_index = 0;
        
    };
}