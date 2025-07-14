#pragma once

#include "mint/common/defines.hpp"

#include "mint/input/mouse_buttons.hpp"

#include <tuple>

namespace mnt::input
{
    class MINT_API mouse
    {
    friend void process_button(mouse_button button, b8 pressed);
    public:
        mouse();
        ~mouse();

        b8 initialize();
        void shutdown();

        void update();

        b8 is_button_down(mouse_button button) const;
        b8 is_button_up(mouse_button button) const;
        b8 is_button_pressed(mouse_button button) const;

        // TODO: erplace with vector2
        std::tuple<i32, i32> get_position() { return {12, 12}; };        

    private:
        b8 m_is_initialized = false;
        
        b8 m_mouse_present[5];
        b8 m_mouse_previous[5];
    };

    void process_button(mouse_button button, b8 pressed);
}

#define MINT_IS_BUTTON_DOWN(btn) ::mnt::engine::get().get_mouse().is_button_down(btn)
#define MINT_IS_BUTTON_UP(btn) ::mnt::engine::get().get_mouse().is_button_up(btn)
#define MINT_IS_BUTTON_PRESSED(btn) ::mnt::engine::get().get_mouse().is_button_pressed(btn)