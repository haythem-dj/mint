#include "mint/render_backend/opengl/gl_shader.hpp"

#include "mint/core/engine.hpp"
#include "mint/core/logger.hpp"

#include <glad/gl.h>

#include <fstream>
#include <sstream>

namespace mnt::graphics
{
	gl_shader::gl_shader()
	{}

	gl_shader::~gl_shader()
	{}

	b8 gl_shader::initialize(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
	{
		std::string vertex_src = load_shader(vertex);
		std::string fragment_src = load_shader(fragment);

		m_id = glCreateProgram();

		i32 vertex_id = compile_shader(GL_VERTEX_SHADER, vertex_src.c_str());
		i32 fragment_id = compile_shader(GL_FRAGMENT_SHADER, fragment_src.c_str());

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

	void gl_shader::set_int1(const std::string& name, i32 value)
	{
		bind();
		glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
	}

	void gl_shader::set_float1(const std::string& name, f32 value)
	{
		bind();
		glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
	}

	void gl_shader::set_float2(const std::string& name, const math::vector2& value)
	{
		bind();
		glUniform2f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y);
	}

	void gl_shader::set_float3(const std::string& name, const math::vector3& value)
	{
		bind();
		glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
	}

	void gl_shader::set_float4(const std::string& name, const math::vector4& value)
	{
		bind();
		glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z, value.w);
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

	std::string gl_shader::load_shader(const std::filesystem::path& file_path)
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