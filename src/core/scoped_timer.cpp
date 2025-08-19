#include "mint/core/scoped_timer.hpp"

#include "mint/core/engine.hpp"

namespace mnt
{
    scoped_timer::scoped_timer(const std::string& name)
        : m_name(name)
    {
        m_timer.reset();
    }

    scoped_timer::~scoped_timer()
    {
        f64 duration_ms = m_timer.elapsed_milli();
        f64 duration_s = m_timer.elapsed();
        MINT_INFO("[TIMER] %s: [%.3f s]   [%.3f ms]", m_name.c_str(), duration_s, duration_ms);
    }

} // namespace mnt
