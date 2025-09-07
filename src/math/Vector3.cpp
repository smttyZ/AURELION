#include "include/Vector3.h"

namespace math {

    Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3::Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z) {}

    Vector3& Vector3::operator=(const Vector3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    Vector3 Vector3::operator+(const Vector3& rhs) const {
        return {x + rhs.x, y + rhs.y, z + rhs.z};
    }

    Vector3 Vector3::operator-(const Vector3& rhs) const {
        return {x - rhs.x, y - rhs.y, z - rhs.z};
    }

    Vector3 Vector3::operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vector3 Vector3::operator/(float scalar) const {
        return {x / scalar, y / scalar, z / scalar}; // TODO: handle divide by zero
    }

    Vector3& Vector3::operator+=(const Vector3& rhs) {
        x += rhs.x; y += rhs.y; z += rhs.z;
        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& rhs) {
        x -= rhs.x; y -= rhs.y; z -= rhs.z;
        return *this;
    }

    Vector3& Vector3::operator*=(float scalar) {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    Vector3& Vector3::operator/=(float scalar) {
        x /= scalar; y /= scalar; z /= scalar; // TODO: handle divide by zero
        return *this;
    }

    float Vector3::length() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    float Vector3::lengthSquared() const {
        return x*x + y*y + z*z;
    }

    Vector3 Vector3::normalized() const {
        float len = length();
        if (len == 0) return {0,0,0};
        return *this / len;
    }

    void Vector3::normalize() {
        float len = length();
        if (len == 0) return;
        *this /= len;
    }

    float Vector3::dot(const Vector3& rhs) const {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }

    Vector3 Vector3::cross(const Vector3& rhs) const {
        return {
            y*rhs.z - z*rhs.y,
            z*rhs.x - x*rhs.z,
            x*rhs.y - y*rhs.x
        };
    }

    // --- Debug ---
    void Vector3::print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")\n";
    }





} // namespace math
