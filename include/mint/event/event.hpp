#pragma once

#include <functional>
#include <string>

#include "mint/common/defines.hpp"

namespace mnt
{
enum class event_type
{
    none = 0,
    window_close,
    window_resize,
    key_press,
    key_release,
    mouse_press,
    mouse_release,
    mouse_move,
    mouse_scroll
};

class event
{
    friend class event_dispatcher;

   public:
    virtual event_type get_event_type() const = 0;
    virtual const char* get_name() const = 0;
    virtual std::string to_string() const { return get_name(); };

   private:
    b8 m_handeled = false;
};

#define EVENT_CLASS_TYPE(type)                                        \
    static event_type get_static_type() { return event_type::type; } \
    virtual event_type get_event_type() const override             \
    {                                                              \
        return get_static_type();                                  \
    }                                                              \
    virtual const char* get_name() const override { return #type; }

class event_dispatcher
{
    template <typename T>
    using event_fn = std::function<bool(T&)>;

   public:
    event_dispatcher(event& event) : m_event(event) {}

    template <typename T>
    b8 dispatch(event_fn<T> func)
    {
        if (m_event.get_event_type() == T::get_static_type())
        {
            m_event.m_handeled = func(*(T*)&m_event);
            return true;
        }
        return false;
    }

   private:
    event& m_event;
};
}  // namespace mnt
