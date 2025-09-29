#include "include/Mat4.h"

// Default constructor initializes to identity matrix
mat4::mat4()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// Parameterized constructor initializes to a diagonal matrix with given value
mat4::mat4(float d)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            m[i][j] = (i == j) ? d : 0.0f;
        }
    }
}

// Matrix multiplication
mat4 mat4::operator*(const mat4 &other) const
{
    mat4 result(0.0f);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}