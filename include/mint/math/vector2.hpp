#pragma once

#include "mint/common/defines.hpp"

namespace mnt::math
{
    class MINT_API vector2
	{
	public:
		union
		{
			f32 x, u;
		};
		union
		{
			f32 y, v;
		};

		vector2();
		vector2(f32 p_x, f32 p_y);
		vector2(f32 value);

		f32 length_sqr() const;
		f32 length() const;
		void normalize();

		vector2 operator+(const vector2& vector) const;
		vector2& operator+=(const vector2& vector);
		
		vector2 operator-(const vector2& vector) const;
		vector2& operator-=(const vector2& vector);
		
		f32 operator*(const vector2& vector) const;
		
		vector2 operator%(const vector2& vector) const;
		vector2& operator%=(const vector2& vector);

		vector2 operator+(f32 scalar) const;
		vector2& operator+=(f32 scalar);
		
		vector2 operator-(f32 scalar) const;
		vector2& operator-=(f32 scalar);
		
		vector2 operator*(f32 scalar) const;
		vector2& operator*=(f32 scalar);
	};

	MINT_API vector2 operator+(f32 scalar, const vector2& vector);
	MINT_API vector2 operator-(f32 scalar, const vector2& vector);
	MINT_API vector2 operator*(f32 scalar, const vector2& vector);
}