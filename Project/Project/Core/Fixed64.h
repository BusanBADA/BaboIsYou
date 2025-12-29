#pragma once
#include <cstdint>
#include <cmath>
using Fixed64 = int64_t;
const Fixed64 ONE = 65536; // 1.0
const Fixed64 HALF_TILE = 32768; // 0.5
inline Fixed64 ToFixed(float f) { return (Fixed64)(f * ONE); }
inline Fixed64 ToFixed(int i) { return (Fixed64)i * ONE; }
inline float ToFloat(Fixed64 x) { return (float)x / ONE; }

struct Vector2Fixed {
    Fixed64 x, y;

    Vector2Fixed operator+(const Vector2Fixed& other) const { return { x + other.x, y + other.y }; }
    Vector2Fixed operator-(const Vector2Fixed& other) const { return { x - other.x, y - other.y }; }
    Vector2Fixed operator*(Fixed64 scalar) const { return { (x * scalar) / ONE, (y * scalar) / ONE }; }
};