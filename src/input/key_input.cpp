#include "mint/input/key_input.hpp"

#include "mint/core/engine.hpp"

#include <cstring>

namespace mnt::input
{
	keyboard::keyboard()
	{}

	keyboard::~keyboard()
	{}

	b8 keyboard::initialize()
	{
		if (m_is_initialized) return false;

		memset(m_keys_present, 0, 256*sizeof(b8));
		memset(m_keys_previous, 0, 256*sizeof(b8));

		m_is_initialized = true;
		return true;
	}

	void keyboard::shutdown()
	{}

	void keyboard::update()
	{
		memcpy(m_keys_previous, m_keys_present, 256*sizeof(b8));
	}

	b8 keyboard::is_key_down(key_code key) const
	{
		return m_keys_present[(u32)key];
	}

    b8 keyboard::is_key_up(key_code key) const
    {
    	return !m_keys_present[(u32)key];
    }

	b8 keyboard::is_key_pressed(key_code key) const
	{
		return (m_keys_present[(u32)key] && !m_keys_previous[(u32)key]);
	}

	void process_key(key_code key, b8 pressed)
	{
		if (engine::get().get_keyboard().m_keys_present[(u32)key] != pressed)
			engine::get().get_keyboard().m_keys_present[(u32)key] = pressed;
	}
}