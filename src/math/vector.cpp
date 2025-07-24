#include "mint/math/vector.hpp"

#include "mint/math/math.hpp"

namespace mnt::math
{
	vector2::vector2()
		:x(0.f), y(0.f)
	{}

	vector2::vector2(f32 p_x, f32 p_y)
		:x(p_x), y(p_y)
	{}

	vector2::vector2(f32 value)
		:x(value), y(value)
	{}

	f32 vector2::length_sqr() const
	{
		return x*x + y*y;
	}

	f32 vector2::length() const
	{
		return sqrt(length_sqr());
	}

	void vector2::normalize()
	{
		f32 l = length();
		if (l != 0)
		{
			x /= l;
			y /= l;
		}
	}


	vector2 vector2::operator*(f32 scalar) const
	{
		return vector2(x*scalar, y*scalar);
	}

	f32 vector2::operator*(const vector2& vector) const
	{
		return x*vector.x + y*vector.y;
	}

	vector2 operator*(f32 scalar, const vector2& vector)
	{
		return vector * scalar;
	}

	vector3::vector3()
		:x(0.f), y(0.f), z(0.f)
	{}

	vector3::vector3(f32 p_x, f32 p_y, f32 p_z)
		:x(p_x), y(p_y), z(p_z)
	{}

	vector3::vector3(f32 value)
		:x(value), y(value), z(value)
	{}

	f32 vector3::length_sqr() const
	{
		return x*x + y*y +z*z;
	}

	f32 vector3::length() const
	{
		return sqrt(length_sqr());
	}

	void vector3::normalize()
	{
		f32 l = length();
		if (l != 0)
		{
			x /= l;
			y /= l;
			z /= l;
		}
	}

	vector3 vector3::operator*(f32 scalar) const
	{
		return vector3(x*scalar, y*scalar, z*scalar);
	}

	f32 vector3::operator*(const vector3& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	vector3 operator*(f32 scalar, const vector3& vector)
	{
		return vector * scalar;
	}

	vector4::vector4()
		:x(0.f), y(0.f)
	{}

	vector4::vector4(f32 p_x, f32 p_y, f32 p_z, f32 p_w)
		:x(p_x), y(p_y), z(p_z), w(p_w)
	{}

	vector4::vector4(f32 value)
		:x(value), y(value), z(value), w(value)
	{}

	f32 vector4::length_sqr() const
	{
		return x*x + y*y + z*z + w*w;
	}

	f32 vector4::length() const
	{
		return sqrt(length_sqr());
	}

	void vector4::normalize()
	{
		f32 l = length();
		if (l != 0)
		{
			x /= l;
			y /= l;
			z /= l;
			w /= l;
		}
	}

	vector4 vector4::operator*(f32 scalar) const
	{
		return vector4(scalar * x, scalar * y, scalar * z, scalar * w);
	}

	f32 vector4::operator*(const vector4& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
	}

	vector4 operator*(f32 scalar, const vector4& vector)
	{
		return vector * scalar;
	}
}