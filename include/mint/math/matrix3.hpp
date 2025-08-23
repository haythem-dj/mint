#pragma once

#include "mint/common/defines.hpp"

#include <initializer_list>

namespace mnt::math
{
    class vector2;

    class MINT_API matrix3
    {
    public:
        f32 data[3][3];

        matrix3();
        matrix3(f32 value);
        matrix3(std::initializer_list<f32> values);

        void translate(const vector2& vec);
        void scale(const vector2& vec);

        f32* operator[](u32 index);
        const f32* operator[](u32 index) const;

        matrix3 operator+(const matrix3& mat) const;
        matrix3& operator+=(const matrix3& mat);

        matrix3 operator-(const matrix3& mat) const;
        matrix3& operator-=(const matrix3& mat);

        matrix3 operator*(const matrix3& mat) const;

        matrix3 operator%(const matrix3& mat) const;
        matrix3& operator%=(const matrix3& mat);

        matrix3 operator+(f32 scalar) const;
        matrix3& operator+=(f32 scalar);

        matrix3 operator-(f32 scalar) const;
        matrix3& operator-=(f32 scalar);

        matrix3 operator*(f32 scalar) const;
        matrix3& operator*=(f32 scalar);
    };

    MINT_API matrix3 operator+(f32 scalar, const matrix3& mat);
    MINT_API matrix3 operator-(f32 scalar, const matrix3& mat);
    MINT_API matrix3 operator*(f32 scalar, const matrix3& mat);
}