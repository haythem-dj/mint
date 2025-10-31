#pragma once

#include "mint/common/defines.hpp"

#include <initializer_list>

namespace mnt::math
{
    class vector3;
    class vector4;

    class MINT_API matrix4
    {
    public:
        f32 data[4][4];

        matrix4();
        matrix4(f32 value);
        matrix4(std::initializer_list<f32> values);

        f32* operator[](u32 index);
        const f32* operator[](u32 index) const;

        matrix4 operator+(const matrix4& mat) const;
        matrix4& operator+=(const matrix4& mat);

        matrix4 operator-(const matrix4& mat) const;
        matrix4& operator-=(const matrix4& mat);

        matrix4 operator*(const matrix4& mat) const;
        vector4 operator*(const vector4& mat) const;

        matrix4 operator%(const matrix4& mat) const;
        matrix4& operator%=(const matrix4& mat);

        matrix4 operator+(f32 scalar) const;
        matrix4& operator+=(f32 scalar);

        matrix4 operator-(f32 scalar) const;
        matrix4& operator-=(f32 scalar);

        matrix4 operator*(f32 scalar) const;
        matrix4& operator*=(f32 scalar);

        void transpose();
    };

    MINT_API matrix4 identity();

    MINT_API matrix4 operator+(f32 scalar, const matrix4& mat);
    MINT_API matrix4 operator-(f32 scalar, const matrix4& mat);
    MINT_API matrix4 operator*(f32 scalar, const matrix4& mat);

    MINT_API matrix4 transpose(const matrix4& mat);

    MINT_API matrix4 translate(const vector3& vec);
    MINT_API matrix4 scale(const vector3& vec);
    MINT_API matrix4 rotate(const vector3& vec);

    MINT_API matrix4 view(const vector3& position, const vector3& forward, const vector3& right, const vector3& up);
    
    MINT_API matrix4 orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
}