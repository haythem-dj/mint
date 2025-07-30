#pragma once

#include "mint/common/defines.hpp"

#include <string>

namespace mnt
{
    struct window_props
    {
        std::string title = "mint app";
        u32 width = 800;
        u32 height = 600;
    };

    class MINT_API window
    {
    public:
        window();
        ~window();

        b8 initialize(const window_props& props);
        void shutdown();

        void process_messages();
        b8 make_current_context();
        void swap_buffers();

        void* get_window_handle() const;

    private:
        b8 m_is_initialized = false;
        window_props m_props;
    };
} // namespace mnt
