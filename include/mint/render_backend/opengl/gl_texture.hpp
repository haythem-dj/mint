#pragma once

#include "mint/graphics/texture.hpp"

namespace mnt::graphics
{
    class gl_texture : public texture
    {
    public:
        gl_texture();
        ~gl_texture();

        b8 initialize(const std::string& path) override;
        void shutdown() override;

        void bind(u32 slot) const override;
        void unbind() const override;
        
    private:
        b8 m_is_initialized = false;
    };
}