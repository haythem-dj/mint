#pragma once

#include "mint/common/defines.hpp"

#include <string>
#include <memory>

namespace mnt::graphics
{
    class MINT_API texture
    {
    public:
        texture();
        ~texture();

        virtual b8 initialize(const std::string& path) = 0;
        virtual void shutdown() = 0;

        virtual void bind(u32 slot) const = 0;
        virtual void unbind() const = 0;

        u32 get_id() const { return m_id; }

        static std::shared_ptr<texture> create();

    protected:
        u32 m_id = 0;
    };
}