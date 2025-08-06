#pragma once

#include "mint/graphics/shader.hpp"

namespace mnt::graphics
{
	class gl_shader : public shader
	{
	public:
		gl_shader();
		~gl_shader();
		
		b8 initialize(shader_init_type type, const std::string& vertex, const std::string& fragment) override;
		void shutdown() override;

		void bind() const override;
		void unbind() const override;

		void set_int1(const std::string& name, i32 value) override;

		void set_float1(const std::string& name, f32 value) override;
		void set_float2(const std::string& name, const math::vector2& value) override;
		void set_float3(const std::string& name, const math::vector3& value) override;
		void set_float4(const std::string& name, const math::vector4& value) override;

	private:
		b8 initialize_with_file(const std::string& vertex, const std::string& fragment);
		b8 initialize_with_src(const std::string& vertex, const std::string& fragment);

		u32 compile_shader(u32 type, const char* src);
		std::string load_shader(const std::string& file_path);

	};
}