#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <sstream>
#include <cmath>

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 operator-() const {
        return {-x, -y, -z};
    }

    Vector3 operator-(const Vector3 &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    friend Vector3 operator*(const Vector3 &v, const float scalar) {
        return {v.x * scalar, v.y * scalar, v.z * scalar};
    }

    friend Vector3 operator*(const float scalar, const Vector3 &v) {
        return {v.x * scalar, v.y * scalar, v.z * scalar};
    }

    friend Vector3 operator/(const Vector3 &v, const float scalar) {
        return {v.x / scalar, v.y / scalar, v.z / scalar};
    }

    float DotProduct(const Vector3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 CrossProduct(const Vector3 &other) const {
        return {
                y * other.z - z * other.y,
                x * other.z - z * other.x,
                x * other.y - y * other.x};
    }

    float Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 Normal() const {
        auto length = Length();
        return {x / length, y / length, z / length};
    }

    std::string ToString() const {
        std::ostringstream result;
        // Ternary to fix avoid precision mistakes resulting in "-0" int the output
        result << "(" << (x == 0 ? 0 : x) << ", " << (y == 0 ? 0 : y) << ", " << (z == 0 ? 0 : z) << ")";
        return result.str();
    }
};

#endif