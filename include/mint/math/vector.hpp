#pragma once

#include "mint/common/defines.hpp"

namespace mnt::math
{
	class MINT_API vector2
	{
	public:
		union
		{
			struct
			{
				f32 x;
				f32 y;
			};
			struct
			{
				f32 u;
				f32 v;
			};
		};

		vector2();
		vector2(f32 p_x, f32 p_y);
		vector2(f32 value);

		f32 length_sqr() const;
		f32 length() const;
		void normalize();

		vector2 operator*(f32 scalar) const;
		f32 operator*(const vector2& vector) const;
	};

	MINT_API vector2 operator*(f32 scalar, const vector2& vector);

	class MINT_API vector3
	{
	public:
		union
		{
			struct
			{
				f32 x;
				f32 y;
				f32 z;
			};
			struct
			{
				f32 r;
				f32 g;
				f32 b;
			};
		};

		vector3();
		vector3(f32 p_x, f32 p_y, f32 p_z);
		vector3(f32 value);

		f32 length_sqr() const;
		f32 length() const;
		void normalize();

		vector3 operator*(f32 scalar) const;
		f32 operator*(const vector3& vector) const;
	};

	MINT_API vector3 operator*(f32 scalar, const vector3& vector);

	class MINT_API vector4
	{
	public:
		union
		{
			struct
			{
				f32 x;
				f32 y;
				f32 z;
				f32 w;
			};
			struct
			{
				f32 r;
				f32 g;
				f32 b;
				f32 a;
			};
		};

		vector4();
		vector4(f32 p_x, f32 p_y, f32 p_z, f32 p_a);
		vector4(f32 value);

		f32 length_sqr() const;
		f32 length() const;
		void normalize();

		vector4 operator*(f32 scalar) const;
		f32 operator*(const vector4& vector) const;
	};

	MINT_API vector4 operator*(f32 scalar, const vector4& vector);
}