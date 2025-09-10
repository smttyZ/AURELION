#pragma once

#include <cmath>
#include <iostream>

namespace math
{
    class Vector2
    {
    public:
        float x;
        float y;

        // --- Constructors ---
        Vector2();
        Vector2(float x, float y);
        Vector2(const Vector2 &other);

        // --- Basic arithmetic operations ---
        Vector2 operator+(const Vector2 &rhs) const;
        Vector2 operator-(const Vector2 &rhs) const;
        Vector2 operator*(float scalar) const;
        Vector2 operator/(float scalar) const;

        // --- Compound assignment operators ---
        Vector2 &operator+=(const Vector2 &rhs);
        Vector2 &operator-=(const Vector2 &rhs);
        Vector2 &operator*=(float scalar);
        Vector2 &operator/=(float scalar);

        // --- Vector operations ---
        float length() const;
        float lengthSquared() const;
        Vector2 normalized() const;
        void normalize();
        float dot(const Vector2 &rhs) const;
        float cross(const Vector2 &rhs) const; // Note: In 2D, this returns a scalar representing the z-component of the 3D cross product.

        // --- Debugging / Utility ---
        friend std::ostream &operator<<(std::ostream &os, const Vector2 &v);
    };

} // namespace math