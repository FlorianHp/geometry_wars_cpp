#pragma once

#include <cmath>

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    Vec2() = default;
    Vec2(float xin, float yin) : x(xin), y(yin) {}

    Vec2 operator+(const Vec2& rhs) const {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2 operator-(const Vec2& rhs) const {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2 operator*(float val) const {
        return Vec2(x * val, y * val);
    }

    Vec2 operator/(float val) const {
        return Vec2(x / val, y / val);
    }

    Vec2& operator+=(const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2& operator*=(float val) {
        x *= val;
        y *= val;
        return *this;
    }

    Vec2& operator/=(float val) {
        x /= val;
        y /= val;
        return *this;
    }

    bool operator==(const Vec2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Vec2& rhs) const {
        return !(*this == rhs);
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2 normalized() const {
        float len = length();
        if (len == 0.0f) return Vec2(0.0f, 0.0f);
        return Vec2(x / len, y / len);
    }

    void normalize() {
        float len = length();
        if (len == 0.0f) return;
        x /= len;
        y /= len;
    }

    float dot(const Vec2& rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    float distance(const Vec2& rhs) const {
        float dx = x - rhs.x;
        float dy = y - rhs.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};