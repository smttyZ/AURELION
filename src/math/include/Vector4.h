#pragma once

namespace math
{
    class Vector4
    {
    public:
        float wl; /**< The w component of the vector. */
        float x;  /**< The x component of the vector. */
        float y;  /**< The y component of the vector. */
        float z;  /**< The z component of the vector. */

        // --- Constructors ---
        Vector4();
        Vector4(float wl, float x, float y, float z);
        Vector4(const Vector4 &other);

        // --- Basic arithmetic operations ---
        Vector4 operator=(const Vector4 &rhs) const;
        Vector4 operator+(const Vector4 &rhs) const;
        Vector4 operator-(const Vector4 &rhs) const;
        Vector4 operator*(float scalar) const;
        Vector4 operator/(float scalar) const;

        // --- Compound assignment operators ---
        Vector4 &operator+=(const Vector4 &rhs);
        Vector4 &operator-=(const Vector4 &rhs);
        Vector4 &operator*=(float scalar);
        Vector4 &operator/=(float scalar);

        // --- Vector operations ---
        float length() const;
        float lengthSquared() const;
        Vector4 normalized() const;

        // --- Dot product ---
        float dot(const Vector4 &other) const;
        // --- Equality operators ---
        bool operator==(const Vector4 &rhs) const;
        bool operator!=(const Vector4 &rhs) const;

        // --- Utility ---
        void set(float wl, float x, float y, float z);
        void zero();
    };
}