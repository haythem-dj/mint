#include "mint/math/matrix4.hpp"

#include "mint/math/math.hpp"
#include "mint/math/vector3.hpp"
#include "mint/math/vector4.hpp"

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

    vector4 matrix4::operator*(const vector4& vec) const
    {
        vector4 res(0.0f);

        res.x += data[0][0] * vec.x;
        res.x += data[0][1] * vec.y;
        res.x += data[0][2] * vec.z;
        res.x += data[0][3] * vec.w;

        res.y += data[1][0] * vec.x;
        res.y += data[1][1] * vec.y;
        res.y += data[1][2] * vec.z;
        res.y += data[1][3] * vec.w;

        res.z += data[2][0] * vec.x;
        res.z += data[2][1] * vec.y;
        res.z += data[2][2] * vec.z;
        res.z += data[2][3] * vec.w;

        res.w += data[3][0] * vec.x;
        res.w += data[3][1] * vec.y;
        res.w += data[3][2] * vec.z;
        res.w += data[3][3] * vec.w;

        return res;
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

    void matrix4::transpose()
    {
        for (u32 i = 0; i < 4; i++)
            for (u32 j = i + 1; j < 4; j++)
            {
                f32 temp = data[i][j];
                data[i][j] = data[j][i];
                data[j][i] = temp;
            }
    }

    matrix4 identity()
    {
        matrix4 mat;
        return mat;
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

    matrix4 transpose(const matrix4& mat)
    {
        matrix4 res = mat;
        res.transpose();
        return res;
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

    matrix4 view(const vector3& position, const vector3& forward, const vector3& right, const vector3& up)
    {
        matrix4 res;
        res[0][0] = right.x;
        res[0][1] = right.y;
        res[0][2] = right.z;
        res[0][3] = -(right*position);

        res[1][0] = up.x;
        res[1][1] = up.y;
        res[1][2] = up.z;
        res[1][3] = -(up*position);

        res[2][0] = -forward.x;
        res[2][1] = -forward.y;
        res[2][2] = -forward.z;
        res[2][3] = (forward*position);

        return res;
    }

    matrix4 orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
    {
        matrix4 ortho;
        ortho[0][0] = 2.0f / (right - left);
        ortho[1][1] = 2.0f / (top - bottom);
        ortho[2][2] = 2.0f / (near - far);

        ortho[0][3] = (right + left) / (left - right);
        ortho[1][3] = (top + bottom) / (bottom - top);
        ortho[2][3] = (near + far) / (near - far);

        return ortho;
    }
}