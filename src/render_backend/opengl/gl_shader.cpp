#include "mint/render_backend/opengl/gl_shader.hpp"

#include "mint/core/engine.hpp"
#include "mint/core/logger.hpp"

#include <glad/glad.h>

#include <fstream>
#include <sstream>

namespace mnt::graphics
{
	gl_shader::gl_shader()
	{}

	gl_shader::~gl_shader()
	{}

	b8 gl_shader::initialize(shader_init_type type, const std::string& vertex, const std::string& fragment)
	{
		if (type == shader_init_type::none) return false;

		if (type == shader_init_type::src) return initialize_with_src(vertex, fragment);
		if (type == shader_init_type::file) return initialize_with_file(vertex, fragment);

		return false;
	}

	void gl_shader::shutdown()
	{
		glDeleteProgram(m_id);
		m_id = 0;
	}

	void gl_shader::bind() const
	{
		glUseProgram(m_id);
	}

	void gl_shader::unbind() const
	{
		glUseProgram(0);
	}

	b8 gl_shader::initialize_with_file(const std::string& vertex, const std::string& fragment)
	{
		std::string vertex_src = load_shader(vertex);
		std::string fragment_src = load_shader(fragment);

		return initialize_with_src(vertex_src, fragment_src);
	}

	b8 gl_shader::initialize_with_src(const std::string& vertex, const std::string& fragment)
	{
		m_id = glCreateProgram();

		i32 vertex_id = compile_shader(GL_VERTEX_SHADER, vertex.c_str());
		i32 fragment_id = compile_shader(GL_FRAGMENT_SHADER, fragment.c_str());

		if (vertex_id == -1 || fragment_id == -1)
		{
			MINT_ERROR("Could not compile shader");
			return false;
		}

		glAttachShader(m_id, vertex_id);
		glAttachShader(m_id, fragment_id);

		glLinkProgram(m_id);
		glValidateProgram(m_id);

		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);

		return true;
	}

	u32 gl_shader::compile_shader(u32 type, const char* src)
	{
		MINT_ASSERT((type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER), "shader type is not valid");

		i32 status;

		u32 shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (status != GL_TRUE)
		{
			i32 length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			const char* err = (char*)malloc(length * sizeof(char));
			glGetShaderInfoLog(shader, length, &length, (GLchar*)err);
			MINT_ERROR("%s shader compilation error: %s", type == GL_VERTEX_SHADER ? "vertex" : "fragment", err);
		}

		return shader;
	}

	std::string gl_shader::load_shader(const std::string& file_path)
	{
		std::ifstream shader(file_path);
		if (!shader.is_open())
		{
			MINT_ERROR("unable to open file: %s", file_path);
			return std::string();
		}

		std::string line;
		std::stringstream ss;

		while (getline(shader, line))
		{
			ss << line << "\n";
		}

		shader.close();

		return ss.str();
	}
}