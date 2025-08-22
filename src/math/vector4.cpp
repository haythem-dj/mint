#include "mint/math/vector4.hpp"

#include "mint/math/math.hpp"

namespace mnt::math
{
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

    vector4 vector4::operator+(const vector4& vector) const
	{
		return vector4(x+vector.x, y+vector.y, z+vector.z, w+vector.w);
	}

	vector4& vector4::operator+=(const vector4& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;
		return *this;
	}
		
	vector4 vector4::operator-(const vector4& vector) const
	{
		return vector4(x-vector.x, y-vector.y, z-vector.z, w-vector.w);
	}

	vector4& vector4::operator-=(const vector4& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;
		return *this;
	}
		
	f32 vector4::operator*(const vector4& vector) const
	{
		return x*vector.x + y*vector.y + z*vector.z + w*vector.w;
	}

	vector4 vector4::operator%(const vector4& vector) const
	{
		return vector4(x*vector.x, y*vector.y, z*vector.z, w*vector.w);
	}

	vector4& vector4::operator%=(const vector4& vector)
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		w *= vector.w;
		return *this;
	}

	vector4 vector4::operator+(f32 scalar) const
	{
		return vector4(x+scalar, y+scalar, z+scalar, w+scalar);
	}

	vector4& vector4::operator+=(f32 scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	}
		
	vector4 vector4::operator-(f32 scalar) const
	{
		return vector4(x-scalar, y-scalar, z-scalar, w-scalar);
	}

	vector4& vector4::operator-=(f32 scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	}
	
	vector4 vector4::operator*(f32 scalar) const
	{
		return vector4(x*scalar, y*scalar, z-scalar, w-scalar);
	}
	
	vector4& vector4::operator*=(f32 scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	vector4 operator+(f32 scalar, const vector4& vector)
	{
		return vector + scalar;
	}

	vector4 operator-(f32 scalar, const vector4& vector)
	{
		return vector - scalar;
	}

	vector4 operator*(f32 scalar, const vector4& vector)
	{
		return vector * scalar;
	}
}