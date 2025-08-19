#pragma once

#include "mint/common/defines.hpp"

#include "mint/core/timer.hpp"

#include <string>

namespace mnt
{
    class MINT_API scoped_timer
    {
    public:
        scoped_timer(const std::string& name);
        ~scoped_timer();

    private:
        std::string m_name;
        timer m_timer;
    };
} // namespace mnt
