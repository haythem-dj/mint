#include "mint/graphics/shader.hpp"

#include "mint/render_backend/opengl/gl_shader.hpp"

namespace mnt::graphics
{
	shader::shader()
	{}

	shader::~shader()
	{}

	shader* shader::create()
	{
		return new gl_shader();
	}
}