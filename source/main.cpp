#include <iostream>
#include <limits>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "color.hpp"
#include "ray.hpp"
#include "sphere.hpp"

Color CastRay(const std::vector<Sphere>& scene, const Ray& ray);

int main()
{
    // image config
    const double aspectRatio = 16.0 / 9.0;
 
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // camera config
    const double viewportHeight = 2.0;
    const double viewportWidth = aspectRatio * viewportHeight;
    const double focalLength = 1.0;

    const Point3 cameraOrigin = Point3{0.0, 0.0, 0.0};
    const Vector3 horizontalDir = Vector3{viewportWidth, 0.0, 0.0};  // represents the horizontal direction in which the viewport spans
    const Vector3 verticalDir = Vector3{0.0, viewportHeight, 0.0};  // represents the vertical direction in which the viewport spans
    const Point3 lowerLeftCorner = cameraOrigin - (horizontalDir / 2.0) - (verticalDir / 2.0) - Vector3{0.0, 0.0, focalLength};

    // scene config
    const std::vector<Sphere> scene{
        Sphere{Point3{0.0, 0.0, -3.0}, 1.0},
        Sphere{Point3{-1.5, 0.0, -2.0}, 0.5},
        Sphere{Point3{1.0, 0.5, -2.5}, 0.7}
    };

    // rendering 
    std::ofstream imageFile{"output.ppm"};
    if (imageFile.is_open() == false)
    {
        throw std::runtime_error{"Failed to open image file."};
    }

    imageFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int y = imageHeight - 1; y >= 0; --y)
    {
        for (int x = 0; x < imageWidth; ++x)
        {
            const double u = static_cast<double>(x) / (imageWidth - 1);
            const double v = static_cast<double>(y) / (imageHeight - 1);

            // lowerLeftCorner + horizontalDir * u + verticalDir * v
            // calculates a point on the viewport for pixel(u, v) = vewportPoint
            // viewportPoint - cameraOrigin
            // (destination point) - (starting point) gives the direction from the camera to the point
            Ray ray{cameraOrigin, lowerLeftCorner + horizontalDir * u + verticalDir * v - cameraOrigin};
            
            Color pixelColor = CastRay(scene, ray);

            const int r = static_cast<int>(255.999 * pixelColor.x);
            const int g = static_cast<int>(255.999 * pixelColor.y);
            const int b = static_cast<int>(255.999 * pixelColor.z);

            imageFile << r << " " << g << " " << b << "\n";
        }
    }

    imageFile.close();

    return 0;
}

Color CastRay(const std::vector<Sphere>& scene, const Ray& ray)
{
    double tMin = std::numeric_limits<double>::infinity();
    for (const Sphere& sphere : scene)
    {
        const Vector3 oc = ray.origin - sphere.center;

        const double a = DotProduct(ray.direction, ray.direction);
        const double b = 2.0 * DotProduct(oc, ray.direction);
        const double c = DotProduct(oc, oc) - sphere.radius * sphere.radius;

        const double discriminant = b * b - 4 * a * c;
        double hitDistance;
        if (discriminant >= 0.0 && (hitDistance = (-b - std::sqrt(discriminant)) / (2.0 * a)) <= tMin)
        {
            tMin = hitDistance;
        }
    }
    
    if (std::isinf(tMin) == false)  // if ray hit something then calculate and return color of sphere
    {
        Point3 hitPoint = ray.At(tMin);
        Vector3 normal = Normalize(hitPoint - Point3{0.0, 0.0, -1.0});

        return Color{normal.x + 1.0, normal.y + 1.0, normal.z + 1.0} * 0.5;
    }

    const Vector3 direction = Normalize(ray.direction);
    const double a = 0.5 * (direction.y + 1.0);

    return Color{1.0, 1.0, 1.0} * (1.0 - a) + Color{0.5, 0.7, 1.0} * a;
}