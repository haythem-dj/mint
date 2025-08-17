#pragma once

#include "mint/graphics/shader.hpp"

namespace mnt::graphics
{
	class gl_shader : public shader
	{
	public:
		gl_shader();
		~gl_shader();
		
		b8 initialize(const std::filesystem::path& vertex, const std::filesystem::path& fragment) override;
		void shutdown() override;

		void bind() const override;
		void unbind() const override;

		void set_int1(const std::string& name, i32 value) override;

		void set_float1(const std::string& name, f32 value) override;
		void set_float2(const std::string& name, const math::vector2& value) override;
		void set_float3(const std::string& name, const math::vector3& value) override;
		void set_float4(const std::string& name, const math::vector4& value) override;

	private:
		u32 compile_shader(u32 type, const char* src);
		std::string load_shader(const std::filesystem::path& file_path);

	};
}