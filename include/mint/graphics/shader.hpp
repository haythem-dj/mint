#pragma once

#include "mint/common/defines.hpp"

#include "mint/math/vector.hpp"

#include <string>

namespace mnt::graphics
{
	enum class shader_init_type
	{
		none = 0,
		src,
		file
	};

	class MINT_API shader
	{
	public:
		shader();
		~shader();

		virtual b8 initialize(shader_init_type type, const std::string& vertex, const std::string& fragment) = 0;
		virtual void shutdown() = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_int1(const std::string& name, i32 value) = 0;

		virtual void set_float1(const std::string& name, f32 value) = 0;
		virtual void set_float2(const std::string& name, const math::vector2& value) = 0;
		virtual void set_float3(const std::string& name, const math::vector3& value) = 0;
		virtual void set_float4(const std::string& name, const math::vector4& value) = 0;

		u32 get_id() const { return m_id; }

		static shader* create();

	protected:
		u32 m_id = 0;
	};
}