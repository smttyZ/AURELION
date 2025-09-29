#pragma once

/**
 * @file Mat4.h
 * @brief Definition of a 4x4 matrix structure.
 * This structure is commonly used in 3D graphics for transformations.
 * It includes constructors and basic operations.
 *
 * @param m A 4x4 array representing the matrix elements.
 */
struct mat4
{
    // a 4x4 matrix represented as a 2D array
    float m[4][4];

    // default constructor initializes to identity matrix
    mat4();
    // parameterized constructor initializes to a diagonal matrix with given value
    explicit mat4(float d);

    // multiplication operator for matrix multiplication
    mat4 operator*(const mat4& other) const;
};
