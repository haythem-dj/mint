#include "mint/math/vector2.hpp"

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

	vector2 vector2::operator+(const vector2& vector) const
	{
		return vector2(x+vector.x, y+vector.y);
	}

	vector2& vector2::operator+=(const vector2& vector)
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}
		
	vector2 vector2::operator-(const vector2& vector) const
	{
		return vector2(x-vector.x, y-vector.y);
	}

	vector2& vector2::operator-=(const vector2& vector)
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}
		
	f32 vector2::operator*(const vector2& vector) const
	{
		return x*vector.x+y*vector.y;
	}

	vector2 vector2::operator%(const vector2& vector) const
	{
		return vector2(x*vector.x, y*vector.y);
	}

	vector2& vector2::operator%=(const vector2& vector)
	{
		x *= vector.x;
		y *= vector.y;
		return *this;
	}

	vector2 vector2::operator+(f32 scalar) const
	{
		return vector2(x+scalar, y+scalar);
	}

	vector2& vector2::operator+=(f32 scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}
		
	vector2 vector2::operator-(f32 scalar) const
	{
		return vector2(x-scalar, y-scalar);
	}

	vector2& vector2::operator-=(f32 scalar)
	{
		x -= scalar;
		y -= scalar;
		return *this;
	}
	
	vector2 vector2::operator*(f32 scalar) const
	{
		return vector2(x*scalar, y*scalar);
	}
	
	vector2& vector2::operator*=(f32 scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	vector2 operator+(f32 scalar, const vector2& vector)
	{
		return vector + scalar;
	}

	vector2 operator-(f32 scalar, const vector2& vector)
	{
		return vector - scalar;
	}

	vector2 operator*(f32 scalar, const vector2& vector)
	{
		return vector * scalar;
	}
}