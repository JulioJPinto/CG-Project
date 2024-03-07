#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../common/include/utils.hpp"

std::vector<Point> coneTriangles(const float radius, const float height,
                                 const size_t slices, const size_t stacks) {
  std::vector<Point> vertex;

  const auto alfa = 2 * M_PI / slices;
  const auto stackHeight = height / stacks;

  const auto base_middle = Point{0, 0, 0};

  for (int slice = 0; slice < slices; ++slice) {
    for (int stack = 0; stack < stacks; ++stack) {
      const float cRadius = radius - stack * radius / stacks;
      const float nRadius = radius - (stack + 1) * radius / stacks;

      const Point bottom_left =
          Point(cRadius * sin(slice * alfa), stack * stackHeight,
                cRadius * cos(slice * alfa));
      const Point bottom_right =
          Point(cRadius * sin((slice + 1) * alfa), stack * stackHeight,
                cRadius * cos((slice + 1) * alfa));
      const Point top_left =
          Point(nRadius * sin(slice * alfa), (stack + 1) * stackHeight,
                nRadius * cos(slice * alfa));
      const Point top_right =
          Point(nRadius * sin((slice + 1) * alfa), (stack + 1) * stackHeight,
                nRadius * cos((slice + 1) * alfa));

      vertex.push_back(top_left);
      vertex.push_back(bottom_left);
      vertex.push_back(bottom_right);

      vertex.push_back(top_left);
      vertex.push_back(bottom_right);
      vertex.push_back(top_right);
    }

    const Point base_bottom_left =
        Point(radius * sin(slice * alfa), 0, radius * cos(slice * alfa));
    const Point base_bottom_right = Point(radius * sin((slice + 1) * alfa), 0,
                                          radius * cos((slice + 1) * alfa));

    vertex.push_back(base_middle);
    vertex.push_back(base_bottom_right);
    vertex.push_back(base_bottom_left);
  }

  return vertex;
}

bool generateCone(float radius, float height, int slices, int stacks,
                  const char* filepath) {
  std::vector<Point> triangles = coneTriangles(radius, height, slices, stacks);

  if (triangles.empty()) {
    std::cerr << "Error: Empty vector of triangles.\n";
    return false;
  }

  saveToFile(triangles, filepath);

  return true;
}
