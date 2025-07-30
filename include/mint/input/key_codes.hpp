#pragma once

#include "mint/common/defines.hpp"

namespace mnt::input
{
    enum class key_code
    {
        none = 0x00,
        back_space = 0x08, tab,
        clear =	0x0c, enter,
        shift =	0x10, control, alt, pause, caps_lock,
        escape = 0x1b,
        space = 0x20, page_up, page_down, end, home, left, up, right, down, select,
        insert = 0x2d, del, help,
        zero, one, two, three, four, five, six, seven, eight, nine,
        a = 0x41, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
        sleep = 0x5f,
        multiply = 0x6a, add, separator, subtract, decimal, divide,
        num_lock = 0x90, scroll_lock, shift_left, shift_right, control_left, conrol_right, alt_left, alt_right
    };
}