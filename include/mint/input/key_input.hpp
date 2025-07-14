#pragma once

#include "mint/common/defines.hpp"

#include "mint/input/key_codes.hpp"

namespace mnt::input
{
    class MINT_API keyboard
    {
    friend void process_key(key_code key, b8 pressed);
    public:
        keyboard();
        ~keyboard();

        b8 initialize();
        void shutdown();

        void update();

        b8 is_key_down(key_code key) const;
        b8 is_key_up(key_code key) const;
        b8 is_key_pressed(key_code key) const;

    private:
        b8 m_is_initialized = false;

        b8 m_keys_present[256];
        b8 m_keys_previous[256];
    };

    void process_key(key_code key, b8 pressed);
}

#define MINT_IS_KEY_DOWN(key) ::mnt::engine::get().get_keyboard().is_key_down(key)
#define MINT_IS_KEY_UP(key) ::mnt::engine::get().get_keyboard().is_key_up(key)
#define MINT_IS_KEY_PRESSED(key) ::mnt::engine::get().get_keyboard().is_key_pressed(key)