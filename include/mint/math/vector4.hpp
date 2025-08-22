#pragma once

#include "mint/common/defines.hpp"

namespace mnt::math
{
    class MINT_API vector4
	{
	public:
		union
		{
			f32 x, r;
		};
		union
		{
			f32 y, g;
		};
		union
		{
			f32 z, b;
		};
		union
		{
			f32 w, a;
		};
		

		vector4();
		vector4(f32 p_x, f32 p_y, f32 p_z, f32 p_a);
		vector4(f32 value);

		f32 length_sqr() const;
		f32 length() const;
		void normalize();

        vector4 operator+(const vector4& vector) const;
		vector4& operator+=(const vector4& vector);
		
		vector4 operator-(const vector4& vector) const;
		vector4& operator-=(const vector4& vector);
		
		f32 operator*(const vector4& vector) const;
		
		vector4 operator%(const vector4& vector) const;
		vector4& operator%=(const vector4& vector);

		vector4 operator+(f32 scalar) const;
		vector4& operator+=(f32 scalar);
		
		vector4 operator-(f32 scalar) const;
		vector4& operator-=(f32 scalar);
		
		vector4 operator*(f32 scalar) const;
		vector4& operator*=(f32 scalar);
	};

    MINT_API vector4 operator+(f32 scalar, const vector4& vector);
	MINT_API vector4 operator-(f32 scalar, const vector4& vector);
	MINT_API vector4 operator*(f32 scalar, const vector4& vector);
}