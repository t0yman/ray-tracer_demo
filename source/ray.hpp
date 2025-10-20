#pragma once

#include "point3.hpp"
#include "vector3.hpp"

struct Ray
{
    Ray() = default;
    Ray(Ray&&) = default;
    Ray(const Ray&) = default;
    Ray(const Point3& origin, const Vector3& direction) : origin{origin}, direction{direction} {};

    Ray& operator=(Ray&&) = default;
    Ray& operator=(const Ray&) = default;

    ~Ray() = default;

    inline Point3 At(double t) const { return (origin + (direction * t)); };

    Point3 origin;
    Vector3 direction;
};