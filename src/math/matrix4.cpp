#include "mint/math/matrix4.hpp"

#include "mint/math/math.hpp"
#include "mint/math/vector3.hpp"

namespace mnt::math
{
    matrix4::matrix4()
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                data[i][j] = i == j ? 1 : 0;
    }

    matrix4::matrix4(f32 value)
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                data[i][j] = value;
    }

    matrix4::matrix4(std::initializer_list<f32> values)
    {
        auto it = values.begin();
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++, ++it)
                data[i][j] = *it;
    }

    f32* matrix4::operator[](u32 index)
    {
        return data[index];
    }

    const f32* matrix4::operator[](u32 index) const
    {
        return data[index];
    }

    matrix4 matrix4::operator+(const matrix4& mat) const
    {
        matrix4 result;
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                result.data[i][j] = data[i][j] + mat.data[i][j];

        return result;
    }

    matrix4& matrix4::operator+=(const matrix4& mat)
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                data[i][j] += mat.data[i][j];

        return *this;
    }

    matrix4 matrix4::operator-(const matrix4& mat) const
    {
        matrix4 result;
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                result.data[i][j] = data[i][j] - mat.data[i][j];

        return result;
    }

    matrix4& matrix4::operator-=(const matrix4& mat)
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                data[i][j] -= mat.data[i][j];

        return *this;
    }

    matrix4 matrix4::operator*(const matrix4& mat) const
    {
        matrix4 result(0);
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                for (u32 k = 0; k < 4; k++)
                {
                    result.data[i][j] += data[i][k] * mat.data[k][j];
                }

        return result;
    }

    matrix4 matrix4::operator%(const matrix4& mat) const
    {
        matrix4 result;
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                result.data[i][j] = data[i][j] * mat.data[i][j];

        return result;
    }

    matrix4& matrix4::operator%=(const matrix4& mat)
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                data[i][j] *= mat.data[i][j];

        return *this;
    }

    matrix4 matrix4::operator+(f32 scalar) const
    {
        matrix4 result;
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                result.data[i][j] = data[i][j] + scalar;

        return result;
    }

    matrix4& matrix4::operator+=(f32 scalar)
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                data[i][j] += scalar;

        return *this;
    }

    matrix4 matrix4::operator-(f32 scalar) const
    {
        matrix4 result;
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                result.data[i][j] = data[i][j] - scalar;

        return result;
    }

    matrix4& matrix4::operator-=(f32 scalar)
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                data[i][j] -= scalar;

        return *this;
    }

    matrix4 matrix4::operator*(f32 scalar) const
    {
        matrix4 result;
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                result.data[i][j] = data[i][j] * scalar;
                
        return result;
    }

    matrix4& matrix4::operator*=(f32 scalar)
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = 0; j < 4; j++)
                data[i][j] *= scalar;

        return *this;
    }

    matrix4 operator+(f32 scalar, const matrix4& mat)
    {
        return mat + scalar;
    }

    matrix4 operator-(f32 scalar, const matrix4& mat)
    {
        return mat - scalar;
    }

    matrix4 operator*(f32 scalar, const matrix4& mat)
    {
        return mat * scalar;
    }

    matrix4 translate(const vector3& vec)
    {
        matrix4 res;
        res[0][3] = vec.x;
        res[1][3] = vec.y;
        res[2][3] = vec.z;
        return res;
    }

    matrix4 scale(const vector3& vec)
    {
        matrix4 res;
        res[0][0] = vec.x;
        res[1][1] = vec.y;
        res[2][2] = vec.z;
        return res;
    }

    matrix4 rotate(const vector3& vec)
    {
        matrix4 rot_x({
            1.0f, 0.0f,       0.0f,        0.0f,
            0.0f, cos(vec.x), -sin(vec.x), 0.0f,
            0.0f, sin(vec.x), cos(vec.x),  0.0f ,
            0.0f, 0.0f,       0.0f,        1.0f,
        });

        matrix4 rot_y({
            cos(vec.y),  0.0f, sin(vec.y), 0.0f,
            0.0f,        1.0f, 0.0f,       0.0f,
            -sin(vec.y), 0.0f, cos(vec.y), 0.0f,
            0.0f,        0.0f, 0.0f,       1.0f
        });

        matrix4 rot_z({
            cos(vec.z), -sin(vec.z), 0.0f, 0.0f,
            sin(vec.z), cos(vec.z),  0.0f, 0.0f,
            0.0f,       0.0f,        1.0f, 0.0f,
            0.0f,       0.0f,        0.0f, 1.0f
        });

        return rot_z * rot_x * rot_y;
    }
}