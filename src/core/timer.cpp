#include "mint/core/timer.hpp"

namespace mnt
{
    timer::timer()
    {}

    timer::~timer()
    {}

    f64 timer::get_seconds()
    {
        time_point now = clock::now();
        return std::chrono::duration<f64>(now.time_since_epoch()).count();
    }

    f64 timer::get_milliseconds()
    {
        time_point now = clock::now();
        return std::chrono::duration<f64>(now.time_since_epoch()).count();
    }
    
    f64 timer::elapsed() const
    {
        time_point end = clock::now();
        std::chrono::duration<f64> duration = end-m_start;
        return duration.count();
    }

    f64 timer::elapsed_milli() const
    {
        time_point end = clock::now();
        std::chrono::duration<f64, std::milli> duration = end-m_start;
        return duration.count();
    }

    void timer::reset()
    {
        m_start = clock::now();
    }
}