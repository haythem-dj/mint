#pragma once

#include "mint/common/defines.hpp"

#include <chrono>

namespace mnt
{
    class MINT_API timer
    {
        using clock = std::chrono::high_resolution_clock;
        using time_point = std::chrono::time_point<clock>;
    public:
        timer();
        ~timer();

        static f64 get_seconds();
        static f64 get_milliseconds();
        
        f64 elapsed() const;
        f64 elapsed_milli() const;
        void reset();

    private:
        time_point m_start;
    };
}