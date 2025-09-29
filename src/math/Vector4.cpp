// Implementation of Vector4
#include "include/Vector4.h"
#include <cmath>

namespace math
{

    // --- Constructors ---
    Vector4::Vector4() : wl(0), x(0), y(0), z(0) {}

    Vector4::Vector4(float wl_, float x_, float y_, float z_) : wl(wl_), x(x_), y(y_), z(z_) {}

    Vector4::Vector4(const Vector4 &other) : wl(other.wl), x(other.x), y(other.y), z(other.z) {}

    // --- Assignment operator ---
    Vector4 Vector4::operator=(const Vector4 &rhs) const
    {
        return Vector4(rhs.wl, rhs.x, rhs.y, rhs.z);
    }

    // --- Arithmetic operators ---
    Vector4 Vector4::operator+(const Vector4 &rhs) const
    {
        return Vector4(wl + rhs.wl, x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector4 Vector4::operator-(const Vector4 &rhs) const
    {
        return Vector4(wl - rhs.wl, x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector4 Vector4::operator*(float scalar) const
    {
        return Vector4(wl * scalar, x * scalar, y * scalar, z * scalar);
    }

    Vector4 Vector4::operator/(float scalar) const
    {
        return Vector4(wl / scalar, x / scalar, y / scalar, z / scalar);
    }

    // --- Compound assignment operators ---
    Vector4 &Vector4::operator+=(const Vector4 &rhs)
    {
        wl += rhs.wl;
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector4 &Vector4::operator-=(const Vector4 &rhs)
    {
        wl -= rhs.wl;
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vector4 &Vector4::operator*=(float scalar)
    {
        wl *= scalar;
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector4 &Vector4::operator/=(float scalar)
    {
        wl /= scalar;
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // --- Vector operations ---
    float Vector4::length() const
    {
        return std::sqrt(wl * wl + x * x + y * y + z * z);
    }

    float Vector4::lengthSquared() const
    {
        return wl * wl + x * x + y * y + z * z;
    }

    Vector4 Vector4::normalized() const
    {
        float len = length();
        if (len == 0)
            return Vector4(0, 0, 0, 0);
        return *this / len;
    }

    // --- Dot product ---
    float Vector4::dot(const Vector4 &other) const
    {
        return wl * other.wl + x * other.x + y * other.y + z * other.z;
    }

    // --- Equality operators ---
    bool Vector4::operator==(const Vector4 &rhs) const
    {
        return wl == rhs.wl && x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool Vector4::operator!=(const Vector4 &rhs) const
    {
        return !(*this == rhs);
    }

    // --- Utility ---
    void Vector4::set(float wl_, float x_, float y_, float z_)
    {
        wl = wl_;
        x = x_;
        y = y_;
        z = z_;
    }

    void Vector4::zero()
    {
        wl = x = y = z = 0;
    }

} // namespace math
