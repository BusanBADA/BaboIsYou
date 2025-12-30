#pragma once
#include <cstdint>
#include <cmath>
#include <limits>


#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace BABO::Math {

    constexpr int64_t ONE_RAW = 1LL << 32;

    struct Fix64 {
        int64_t value;

        constexpr Fix64() : value(0) {}


        struct RawTag {};
        constexpr explicit Fix64(int64_t raw, RawTag) : value(raw) {}


        constexpr Fix64(int v) : value(static_cast<int64_t>(v) << 32) {}
        constexpr Fix64(float v) : value(static_cast<int64_t>(v* ONE_RAW)) {}
        constexpr Fix64(double v) : value(static_cast<int64_t>(v* ONE_RAW)) {}


        Fix64 operator+(const Fix64& o) const { return Fix64(value + o.value, RawTag{}); }
        Fix64 operator-(const Fix64& o) const { return Fix64(value - o.value, RawTag{}); }
        bool operator==(const Fix64& o) const { return value == o.value; }
        bool operator!=(const Fix64& o) const { return value != o.value; }
        bool operator<(const Fix64& o) const { return value < o.value; }
        bool operator>(const Fix64& o) const { return value > o.value; }


        Fix64 operator*(const Fix64& o) const {
#ifdef _MSC_VER

            int64_t high;
            unsigned __int64 low = _mul128(value, o.value, &high);

            int64_t res = (int64_t)((low >> 32) | ((unsigned __int64)high << 32));
            return Fix64(res, RawTag{});
#else

            __int128_t res = static_cast<__int128_t>(value) * o.value;
            return Fix64(static_cast<int64_t>(res >> 32), RawTag{});
#endif
        }


        Fix64 operator/(const Fix64& o) const {
            if (o.value == 0) return Fix64(0, RawTag{});

            return Fix64((double)value / ONE_RAW / ((double)o.value / ONE_RAW));
        }
        int32_t ToInt() const { return static_cast<int32_t>(value) / ONE_RAW; }
        float ToFloat() const { return static_cast<float>(value) / ONE_RAW; }
        int64_t Raw() const { return value; }
        static Fix64 Zero() { return Fix64(0, RawTag{}); }
        static Fix64 One() { return Fix64(ONE_RAW, RawTag{}); }
        static Fix64 Abs(Fix64 v) { return v.value < 0 ? Fix64(-v.value, RawTag{}) : v; }
    };

    struct Vector2Fix {
        Fix64 x, y;
        Vector2Fix operator+(const Vector2Fix& o) const { return { x + o.x, y + o.y }; }
        Vector2Fix operator-(const Vector2Fix& o) const { return { x - o.x, y - o.y }; }
        Vector2Fix operator*(Fix64 s) const { return { x * s, y * s }; }
    };
}