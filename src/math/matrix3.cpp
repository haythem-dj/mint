#include "mint/math/matrix3.hpp"

#include "mint/math/vector2.hpp"

namespace mnt::math
{
    matrix3::matrix3()
    {
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                data[i][j] = i == j ? 1 : 0;
    }

    matrix3::matrix3(f32 value)
    {
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                data[i][j] = value;
    }

    matrix3::matrix3(std::initializer_list<f32> values)
    {
        auto it = values.begin();
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++, ++it)
                data[i][j] = *it;
    }

    f32* matrix3::operator[](u32 index)
    {
        return data[index];
    }

    const f32* matrix3::operator[](u32 index) const
    {
        return data[index];
    }

    matrix3 matrix3::operator+(const matrix3& mat) const
    {
        matrix3 result;
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                result.data[i][j] = data[i][j] + mat.data[i][j];

        return result;
    }

    matrix3& matrix3::operator+=(const matrix3& mat)
    {
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                data[i][j] += mat.data[i][j];

        return *this;
    }

    matrix3 matrix3::operator-(const matrix3& mat) const
    {
        matrix3 result;
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                result.data[i][j] = data[i][j] - mat.data[i][j];

        return result;
    }

    matrix3& matrix3::operator-=(const matrix3& mat)
    {
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                data[i][j] -= mat.data[i][j];

        return *this;
    }

    matrix3 matrix3::operator*(const matrix3& mat) const
    {
        matrix3 result(0);
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                for (u32 k = 0; k < 3; k++)
                {
                    result.data[i][j] += data[i][k] * mat.data[k][j];
                }

        return result;
    }

    matrix3 matrix3::operator%(const matrix3& mat) const
    {
        matrix3 result;
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                result.data[i][j] = data[i][j] * mat.data[i][j];

        return result;
    }

    matrix3& matrix3::operator%=(const matrix3& mat)
    {
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                data[i][j] *= mat.data[i][j];

        return *this;
    }

    matrix3 matrix3::operator+(f32 scalar) const
    {
        matrix3 result;
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                result.data[i][j] = data[i][j] + scalar;

        return result;
    }

    matrix3& matrix3::operator+=(f32 scalar)
    {
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                data[i][j] += scalar;

        return *this;
    }

    matrix3 matrix3::operator-(f32 scalar) const
    {
        matrix3 result;
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                result.data[i][j] = data[i][j] - scalar;

        return result;
    }

    matrix3& matrix3::operator-=(f32 scalar)
    {
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                data[i][j] -= scalar;

        return *this;
    }

    matrix3 matrix3::operator*(f32 scalar) const
    {
        matrix3 result;
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                result.data[i][j] = data[i][j] * scalar;
                
        return result;
    }

    matrix3& matrix3::operator*=(f32 scalar)
    {
        for (u32 i = 0; i < 3; i++)
            for (u32 j = 0; j < 3; j++)
                data[i][j] *= scalar;

        return *this;
    }

    matrix3 operator+(f32 scalar, const matrix3& mat)
    {
        return mat + scalar;
    }

    matrix3 operator-(f32 scalar, const matrix3& mat)
    {
        return mat - scalar;
    }

    matrix3 operator*(f32 scalar, const matrix3& mat)
    {
        return mat * scalar;
    }

    void matrix3::translate(const vector2& vec)
    {
        data[0][2] = vec.x;
        data[1][2] = vec.y;
    }

    void matrix3::scale(const vector2& vec)
    {
        data[0][0] = vec.x;
        data[1][1] = vec.y;
    }

    matrix3 translate(const matrix3& mat, const vector2& vec)
    {
        matrix3 res = mat;
        res.translate(vec);
        return res;
    }

    matrix3 scale(const matrix3& mat, const vector2& vec)
    {
        matrix3 res = mat;
        res.scale(vec);
        return res;
    }
}