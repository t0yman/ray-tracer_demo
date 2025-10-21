
# C++ Ray Tracer

An implementation of a ray-tracer in C++, demonstrating fundamental computer graphics concepts.

## Features

- Ray-sphere intersection of multiple objects with surface normal shading.
- Virtual camera system with configurable viewport.
- 3D vector mathematics (dot product, cross product, normalization)
- PPM image output

## Technical Highlights

- Demonstrates understanding of graphics pipeline fundamentals.
- Implements scene composition with multiple geometric primitives.
- Clean, readable C++ code following modern practices.

## Sample Output

![Ray Traced Spheres](ray-tracer_demo_output.jpg)

# Build

```bash
g++ -std=c++11 source/main.cpp -o ray-tracer_demo
```

## Future Improvements

- Multiple objects and materials.
- Lighting models (diffuse, specular)
- Reflections and refractions