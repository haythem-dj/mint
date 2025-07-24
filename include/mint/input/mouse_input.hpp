#pragma once

#include "mint/common/defines.hpp"

#include "mint/input/mouse_buttons.hpp"

#include "mint/math/vector.hpp"

namespace mnt::input
{
    class MINT_API mouse
    {
    friend void process_button(mouse_button button, b8 pressed);
    friend void process_position(i32 x, i32 y);
    public:
        mouse();
        ~mouse();

        b8 initialize();
        void shutdown();

        void update();

        b8 is_button_down(mouse_button button) const;
        b8 is_button_up(mouse_button button) const;
        b8 is_button_pressed(mouse_button button) const;

        math::vector2 get_position() const;

    private:
        b8 m_is_initialized = false;
        
        b8 m_mouse_present[5];
        b8 m_mouse_previous[5];

        math::vector2 m_position;
    };

    void process_button(mouse_button button, b8 pressed);
    void process_position(i32 x, i32 y);
}

#define MINT_IS_BUTTON_DOWN(btn) ::mnt::engine::get().get_mouse().is_button_down(btn)
#define MINT_IS_BUTTON_UP(btn) ::mnt::engine::get().get_mouse().is_button_up(btn)
#define MINT_IS_BUTTON_PRESSED(btn) ::mnt::engine::get().get_mouse().is_button_pressed(btn)

#define MINT_GET_MOUSE_POS() ::mnt::engine::get().get_mouse().get_position();