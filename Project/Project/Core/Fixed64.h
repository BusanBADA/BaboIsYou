
#pragma once
#include <cstdint>
#include <cmath>
#include <iostream>


#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace BABO::Math {
    constexpr int64_t ONE_RAW = 1LL << 32;

    struct Fix64 {
        int64_t value;

        constexpr Fix64() : value(0) {}
        struct RawTag {};
        constexpr Fix64(int64_t raw, RawTag) : value(raw) {}
        constexpr Fix64(int v) : value(static_cast<int64_t>(v) << 32) {}
        constexpr Fix64(float v) : value(static_cast<int64_t>(v* ONE_RAW)) {}

        Fix64 operator+(const Fix64& o) const { return { value + o.value, RawTag{} }; }
        Fix64 operator-(const Fix64& o) const { return { value - o.value, RawTag{} }; }


        Fix64 operator*(const Fix64& o) const {
#ifdef _MSC_VER

            __int64 high;
            unsigned __int64 low = _mul128(value, o.value, &high);


            int64_t res = (int64_t)((low >> 32) | ((unsigned __int64)high << 32));
            return { res, RawTag{} };
#else

            __int128_t res = static_cast<__int128_t>(value) * o.value;
            return { static_cast<int64_t>(res >> 32), RawTag{} };
#endif
        }

        Fix64 operator/(const Fix64& o) const {
            if (o.value == 0) return { 0, RawTag{} };

#ifdef _MSC_VER

            __int64 remainder;
            __int64 result = _div128(value >> 32, value << 32, o.value, &remainder);
            return { result, RawTag{} };
#else

            __int128_t num = static_cast<__int128_t>(value) << 32;
            return { static_cast<int64_t>(num / o.value), RawTag{} };
#endif
        }

        bool operator==(const Fix64& o) const { return value == o.value; }
        bool operator!=(const Fix64& o) const { return value != o.value; }
        bool operator<(const Fix64& o) const { return value < o.value; }
        bool operator>(const Fix64& o) const { return value > o.value; }


        float ToFloat() const { return static_cast<float>(value) / ONE_RAW; }
        int ToInt() const { return static_cast<int>(value >> 32); }
        int64_t Raw() const { return value; }

        static Fix64 Zero() { return { 0, RawTag{} }; }
        static Fix64 One() { return { ONE_RAW, RawTag{} }; }

        static Fix64 Abs(Fix64 v) {
            return { v.value < 0 ? -v.value : v.value, RawTag{} };
        }
    };

    struct Vector2Fixed {
        Fix64 x, y;
        Vector2Fixed operator+(const Vector2Fixed& o) const { return { x + o.x, y + o.y }; }
        Vector2Fixed operator-(const Vector2Fixed& o) const { return { x - o.x, y - o.y }; }
        Vector2Fixed operator*(Fix64 s) const { return { x * s, y * s }; }
        bool operator==(const Vector2Fixed& o) const { return x == o.x && y == o.y; }
    };
}