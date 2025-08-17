#include "mint/graphics/shader.hpp"

#include "mint/render_backend/opengl/gl_shader.hpp"

namespace mnt::graphics
{
	shader::shader()
	{}

	shader::~shader()
	{}

	std::shared_ptr<shader> shader::create()
	{
		return std::make_shared<gl_shader>();
	}
}