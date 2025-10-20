#pragma once

#include <cmath>

struct Vector3
{
    Vector3() = default;
    Vector3(Vector3&&) = default;
    Vector3(const Vector3&) = default;
    inline explicit Vector3(double n) : x{n}, y{n}, z{n} {};
    inline Vector3(double x, double y, double z) : x{x}, y{y}, z{z} {};

    Vector3& operator=(Vector3&&) = default;
    Vector3& operator=(const Vector3&) = default;

    ~Vector3() = default;

    inline Vector3& operator+=(const Vector3& v);
    inline Vector3& operator-=(const Vector3& v);
    inline Vector3& operator*=(double f);
    inline Vector3& operator/=(double f);

    inline double Magnitude() const { return std::sqrt((x * x) + (y * y) + (z * z)); };
    inline double MagnitudeSquared() const { return ((x * x) + (y * y) + (z * z)); };

    double x;
    double y;
    double z;
};

Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vector3& Vector3::operator*=(double f)
{
    x *= f;
    y *= f;
    z *= f;

    return *this;
}

Vector3& Vector3::operator/=(double f)
{
    x /= f;
    y /= f;
    z /= f;

    return *this;
}

inline Vector3 operator-(const Vector3& u)
{
    return {-u.x, -u.y, -u.z};
}

inline Vector3 operator+(const Vector3& u, const Vector3& v)
{
    return {u.x + v.x, u.y + v.y, u.z + v.z};
}

inline Vector3 operator-(const Vector3& u, const Vector3& v)
{
    return {u.x - v.x, u.y - v.y, u.z - v.z};
}

inline Vector3 operator*(const Vector3& u, double f)
{
    return {u.x * f, u.y * f, u.z * f};
}

inline Vector3 operator*(double f, const Vector3& u)
{
    return (u * f);
}

inline Vector3 operator/(const Vector3& u, double f)
{
    return (u * (1 / f));
}

inline double DotProduct(const Vector3& u, const Vector3& v)
{
    return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

inline Vector3 CrossProduct(const Vector3& u, const Vector3& v)
{
    return {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x};
}

inline Vector3 Normalize(const Vector3& u)
{
    return (u / u.Magnitude());
};