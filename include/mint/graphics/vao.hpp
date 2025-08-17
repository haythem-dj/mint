#pragma once

#include "mint/common/defines.hpp"

#include <vector>
#include <memory>

namespace mnt::graphics
{
    class vbo;
    class ebo;
    
    class MINT_API vao
    {
    public:
        vao();
        ~vao();

        virtual b8 initialize() = 0;
        virtual void shutdown() = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void add_vertex_buffer(std::shared_ptr<vbo> vbo, const std::vector<u32>& layout) = 0;
        virtual void set_index_buffer(std::shared_ptr<ebo> ebo) = 0;

        virtual u32 get_element_count() const = 0;

        u32 get_id() const { return m_id; }

        static std::shared_ptr<vao> create();

    protected:
        u32 m_id = 0;
    };
}