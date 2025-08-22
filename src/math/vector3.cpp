#include "mint/math/vector3.hpp"

#include "mint/math/math.hpp"

namespace mnt::math
{
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

	vector3 vector3::operator+(const vector3& vector) const
	{
		return vector3(x+vector.x, y+vector.y, z+vector.z);
	}

	vector3& vector3::operator+=(const vector3& vector)
	{
		x += vector.x;
		y += vector.y;
        z += vector.z;
		return *this;
	}
		
	vector3 vector3::operator-(const vector3& vector) const
	{
		return vector3(x-vector.x, y-vector.y, z-vector.z);
	}

	vector3& vector3::operator-=(const vector3& vector)
	{
		x -= vector.x;
		y -= vector.y;
        z -= vector.z;
		return *this;
	}
		
	f32 vector3::operator*(const vector3& vector) const
	{
		return x*vector.x+y*vector.y+z*vector.z;
	}

	vector3 vector3::operator%(const vector3& vector) const
	{
		return vector3(x*vector.x, y*vector.y, z*vector.z);
	}

	vector3& vector3::operator%=(const vector3& vector)
	{
		x *= vector.x;
		y *= vector.y;
        z *= vector.z;
		return *this;
	}

	vector3 vector3::operator+(f32 scalar) const
	{
		return vector3(x+scalar, y+scalar, z+scalar);
	}

	vector3& vector3::operator+=(f32 scalar)
	{
		x += scalar;
		y += scalar;
        z += scalar;
		return *this;
	}
		
	vector3 vector3::operator-(f32 scalar) const
	{
		return vector3(x-scalar, y-scalar, z-scalar);
	}

	vector3& vector3::operator-=(f32 scalar)
	{
		x -= scalar;
		y -= scalar;
        z -= scalar;
		return *this;
	}
	
	vector3 vector3::operator*(f32 scalar) const
	{
		return vector3(x*scalar, y*scalar, z*scalar);
	}
	
	vector3& vector3::operator*=(f32 scalar)
	{
		x *= scalar;
		y *= scalar;
        z *= scalar;
		return *this;
	}

	vector3 operator+(f32 scalar, const vector3& vector)
	{
		return vector + scalar;
	}

	vector3 operator-(f32 scalar, const vector3& vector)
	{
		return vector - scalar;
	}

	vector3 operator*(f32 scalar, const vector3& vector)
	{
		return vector * scalar;
	}
}