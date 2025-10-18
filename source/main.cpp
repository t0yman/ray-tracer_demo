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
            const int r = 255;
            const int g = 0;
            const int b = 0;

            imageFile << r << " " << g << " " << b << "\n";
        }
    }
    imageFile.close();

    return 0;
}