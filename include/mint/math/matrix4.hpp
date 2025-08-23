#pragma once

#include "mint/common/defines.hpp"

#include <initializer_list>

namespace mnt::math
{
    class vector3;

    class MINT_API matrix4
    {
    public:
        f32 data[4][4];

        matrix4();
        matrix4(f32 value);
        matrix4(std::initializer_list<f32> values);

        void translate(const vector3& vec);
        void scale(const vector3& vec);

        f32* operator[](u32 index);
        const f32* operator[](u32 index) const;

        matrix4 operator+(const matrix4& mat) const;
        matrix4& operator+=(const matrix4& mat);

        matrix4 operator-(const matrix4& mat) const;
        matrix4& operator-=(const matrix4& mat);

        matrix4 operator*(const matrix4& mat) const;

        matrix4 operator%(const matrix4& mat) const;
        matrix4& operator%=(const matrix4& mat);

        matrix4 operator+(f32 scalar) const;
        matrix4& operator+=(f32 scalar);

        matrix4 operator-(f32 scalar) const;
        matrix4& operator-=(f32 scalar);

        matrix4 operator*(f32 scalar) const;
        matrix4& operator*=(f32 scalar);
    };

    MINT_API matrix4 operator+(f32 scalar, const matrix4& mat);
    MINT_API matrix4 operator-(f32 scalar, const matrix4& mat);
    MINT_API matrix4 operator*(f32 scalar, const matrix4& mat);

    MINT_API matrix4 translate(const matrix4& mat, const vector3& vec);
    MINT_API matrix4 scale(const matrix4& mat, const vector3& vec);
}