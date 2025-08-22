#pragma once

#include "mint/common/defines.hpp"

namespace mnt::math
{
    class MINT_API vector3
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

		vector3();
		vector3(f32 p_x, f32 p_y, f32 p_z);
		vector3(f32 value);

		f32 length_sqr() const;
		f32 length() const;
		void normalize();

        vector3 operator+(const vector3& vector) const;
		vector3& operator+=(const vector3& vector);
		
		vector3 operator-(const vector3& vector) const;
		vector3& operator-=(const vector3& vector);
		
		f32 operator*(const vector3& vector) const;
		
		vector3 operator%(const vector3& vector) const;
		vector3& operator%=(const vector3& vector);

		vector3 operator+(f32 scalar) const;
		vector3& operator+=(f32 scalar);
		
		vector3 operator-(f32 scalar) const;
		vector3& operator-=(f32 scalar);
		
		vector3 operator*(f32 scalar) const;
		vector3& operator*=(f32 scalar);
	};

    MINT_API vector3 operator+(f32 scalar, const vector3& vector);
	MINT_API vector3 operator-(f32 scalar, const vector3& vector);
	MINT_API vector3 operator*(f32 scalar, const vector3& vector);
}