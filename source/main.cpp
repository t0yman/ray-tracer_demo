#include <iostream>
#include <fstream>
#include <stdexcept>

int main()
{
    const int imageWidth = 256;
    const int imageHeight = 256;

    std::ofstream imageFile{"output.ppm"};
    if (imageFile.is_open() == false)
    {
        throw std::runtime_error{"Failed to open image file."};
    }

    imageFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    for (int y = 0; y < imageHeight; ++y)
    {
        for (int x = 0; x < imageWidth; ++x)
        {
            // calculate normalized coordinates [0.0, 1.0]
            const double u = static_cast<double>(x) / (imageWidth - 1);
            const double v = static_cast<double>(y) / (imageHeight - 1);

            // blend from white (top) to blue (bottom)
            const int r = static_cast<int>(255.999 * (1.0 - v + v * 0.5));  // white to light blue
            const int g = static_cast<int>(255.999 * (1.0 - v + v * 0.7));
            const int b = static_cast<int>(255.999 * 1.0);

            imageFile << r << " " << g << " " << b << "\n";
        }
    }
    imageFile.close();

    return 0;
}