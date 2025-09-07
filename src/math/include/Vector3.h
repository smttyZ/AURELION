#pragma once

#include <cmath>
#include <iostream>

namespace math {

/**
 * @class Vector3
 * @brief Represents a 3D vector in Cartesian space.
 *
 * Provides basic arithmetic operations, normalization, dot and cross products,
 * and utility functions. Designed to be self-contained and used throughout AURELION
 * for physics, rendering, and transformations.
 *
 * Example usage:
 * @code
 * math::Vector3 a(1.0f, 2.0f, 3.0f);
 * math::Vector3 b(4.0f, 5.0f, 6.0f);
 * auto c = a + b;
 * c.normalize();
 * float dotProduct = a.dot(b);
 * @endcode
 */
class Vector3 {
public:
    float x; /**< The x component of the vector. */
    float y; /**< The y component of the vector. */
    float z; /**< The z component of the vector. */

    // --- Constructors ---

    /**
     * @brief Default constructor.
     *
     * Initializes all components to zero (0, 0, 0).
     */
    Vector3();

    /**
     * @brief Constructs a vector with specified components.
     *
     * @param x The x component.
     * @param y The y component.
     * @param z The z component.
     */
    Vector3(float x, float y, float z);

    /**
     * @brief Copy constructor.
     *
     * @param other The vector to copy from.
     */
    Vector3(const Vector3& other);

    /**
     * @brief Assignment operator.
     *
     * @param other The vector to assign from.
     * @return Reference to this vector.
     */
    Vector3& operator=(const Vector3& other);

    // --- Basic arithmetic operations ---

    /**
     * @brief Vector addition.
     *
     * @param rhs The vector to add.
     * @return A new Vector3 representing the sum.
     */
    Vector3 operator+(const Vector3& rhs) const;

    /**
     * @brief Vector subtraction.
     *
     * @param rhs The vector to subtract.
     * @return A new Vector3 representing the difference.
     */
    Vector3 operator-(const Vector3& rhs) const;

    /**
     * @brief Scalar multiplication.
     *
     * @param scalar The scalar value to multiply by.
     * @return A new Vector3 scaled by the given scalar.
     */
    Vector3 operator*(float scalar) const;

    /**
     * @brief Scalar division.
     *
     * @param scalar The scalar value to divide by.
     * @return A new Vector3 divided by the scalar.
     *
     * @note Behavior is undefined if scalar is zero.
     */
    Vector3 operator/(float scalar) const;

    // --- Compound assignment operators ---

    /**
     * @brief Compound addition assignment.
     *
     * @param rhs The vector to add.
     * @return Reference to this vector after addition.
     */
    Vector3& operator+=(const Vector3& rhs);

    /**
     * @brief Compound subtraction assignment.
     *
     * @param rhs The vector to subtract.
     * @return Reference to this vector after subtraction.
     */
    Vector3& operator-=(const Vector3& rhs);

    /**
     * @brief Compound multiplication assignment (scalar).
     *
     * @param scalar The scalar to multiply by.
     * @return Reference to this vector after scaling.
     */
    Vector3& operator*=(float scalar);

    /**
     * @brief Compound division assignment (scalar).
     *
     * @param scalar The scalar to divide by.
     * @return Reference to this vector after scaling.
     *
     * @note Behavior is undefined if scalar is zero.
     */
    Vector3& operator/=(float scalar);

    // --- Vector operations ---

    /**
     * @brief Computes the length (magnitude) of the vector.
     *
     * @return The Euclidean length of the vector.
     */
    float length() const;

    /**
     * @brief Computes the squared length of the vector.
     *
     * @return The squared Euclidean length (avoids sqrt, useful for comparisons).
     */
    float lengthSquared() const;

    /**
     * @brief Returns a normalized (unit length) copy of the vector.
     *
     * @return A new Vector3 in the same direction but with length 1.
     *
     * @note If the vector has zero length, returns (0,0,0).
     */
    Vector3 normalized() const;

    /**
     * @brief Normalizes this vector in-place to unit length.
     *
     * @note If the vector has zero length, it remains unchanged.
     */
    void normalize();

    /**
     * @brief Computes the dot product with another vector.
     *
     * @param rhs The other vector.
     * @return The scalar dot product.
     *
     * @note Measures similarity of direction; returns positive if same direction,
     * negative if opposite, zero if perpendicular.
     */
    float dot(const Vector3& rhs) const;

    /**
     * @brief Computes the cross product with another vector.
     *
     * @param rhs The other vector.
     * @return A new Vector3 perpendicular to both vectors.
     *
     * @note Follows right-hand rule.
     */
    Vector3 cross(const Vector3& rhs) const;

    // --- Debugging / Utility ---

    /**
     * @brief Prints the vector components to stdout.
     *
     * @note Useful for debugging purposes.
     */
    void print() const;
};

} // namespace math
