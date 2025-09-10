#include "include/Vector2.h"

namespace math {

    Vector2::Vector2() : x(0.0f), y(0.0f) {}

    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    Vector2::Vector2(const Vector2 &other) : x(other.x), y(other.y) {}

    Vector2 Vector2::operator+(const Vector2& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }

    Vector2 Vector2::operator-(const Vector2& rhs) const {
        return {x - rhs.x, y - rhs.y};
    }

    Vector2 Vector2::operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    Vector2 Vector2::operator/(float scalar) const {
        return {x / scalar, y / scalar}; // TODO: handle divide by zero
    }

    Vector2& Vector2::operator+=(const Vector2& rhs) {
        x += rhs.x; y += rhs.y;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& rhs) {
        x -= rhs.x; y -= rhs.y;
        return *this;
    }

    Vector2& Vector2::operator*=(float scalar) {
        x *= scalar; y *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(float scalar) {
        x /= scalar; y /= scalar; // TODO: handle divide by zero
        return *this;
    }

    float Vector2::length() const {
        return std::sqrt(x*x + y*y);
    }

    float Vector2::lengthSquared() const {
        return x*x + y*y;
    }

    Vector2 Vector2::normalized() const {
        float len = length();
        if (len == 0.0f) return {0.0f, 0.0f};
        return {x / len, y / len};
    }

    void Vector2::normalize() {
        float len = length();
        if (len != 0.0f) {
            x /= len;
            y /= len;
        }
    }

    float Vector2::dot(const Vector2& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    float Vector2::cross(const Vector2& rhs) const {
        return x * rhs.y - y * rhs.x;
    }
}