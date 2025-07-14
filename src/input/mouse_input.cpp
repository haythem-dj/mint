#include "mint/input/key_input.hpp"

#include "mint/core/logger.hpp"
#include "mint/core/engine.hpp"

#include <cstring>

namespace mnt::input
{
	mouse::mouse()
	{}

	mouse::~mouse()
	{}

	b8 mouse::initialize()
	{
		if (m_is_initialized) return false;

		memset(m_mouse_present, 0, 5*sizeof(b8));
		memset(m_mouse_previous, 0, 5*sizeof(b8));

		m_is_initialized = true;
		return true;
	}

	void mouse::shutdown()
	{}

	void mouse::update()
	{
		memcpy(m_mouse_previous, m_mouse_present, 5*sizeof(b8));
	}

	b8 mouse::is_button_down(mouse_button button) const
	{
		return m_mouse_present[(u32)button];
	}

    b8 mouse::is_button_up(mouse_button button) const
    {
    	return !m_mouse_present[(u32)button];
    }

	b8 mouse::is_button_pressed(mouse_button button) const
	{
		return (m_mouse_present[(u32)button] && !m_mouse_previous[(u32)button]);
	}

	void process_button(mouse_button button, b8 pressed)
	{
		if (engine::get().get_mouse().m_mouse_present[(u32)button] != pressed)
			engine::get().get_mouse().m_mouse_present[(u32)button] = pressed;
	}
}