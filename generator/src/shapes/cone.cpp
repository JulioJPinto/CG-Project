#include <cmath>
#include <fstream>
#include <iostream>
#include <save3d.hpp>
#include <vector>

#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
coneTriangles(const float radius, const float height, const size_t slices,
              const size_t stacks) {
  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

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

      points.push_back(top_left);
      points.push_back(bottom_left);
      points.push_back(bottom_right);

      points.push_back(top_left);
      points.push_back(bottom_right);
      points.push_back(top_right);

      Point n = (radius * sin(slice * alfa), radius * cos(slice * alfa),
                 radius * sin(slice * alfa));
      for (int i = 0; i < 6; i++) {
        normals.push_back(n);
      }

      textures.push_back(Point2D(0.0f, 0.0f));
      textures.push_back(Point2D(0.0f, 1.0f));
      textures.push_back(Point2D(1.0f, 1.0f));

      textures.push_back(Point2D(0.0f, 0.0f));
      textures.push_back(Point2D(1.0f, 1.0f));
      textures.push_back(Point2D(1.0f, 0.0f));
    }

    const Point base_bottom_left =
        Point(radius * sin(slice * alfa), 0, radius * cos(slice * alfa));
    const Point base_bottom_right = Point(radius * sin((slice + 1) * alfa), 0,
                                          radius * cos((slice + 1) * alfa));

    points.push_back(base_middle);
    points.push_back(base_bottom_right);
    points.push_back(base_bottom_left);

    Point n(0, -1, 0);
    for (int i = 0; i < 3; i++) {
      normals.push_back(n);
    }

    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));
  }

  return std::make_pair(std::make_pair(points, normals), textures);
}

bool generateCone(float radius, float height, int slices, int stacks,
                  const char* filepath, bool advanced) {
  std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
            std::vector<Point2D>>
      cone = coneTriangles(radius, height, slices, stacks);

  if (advanced) {
    save3DAdvancedfile(cone.first.first, cone.first.second, cone.second,
                       filepath);
  } else {
    saveToFile(cone.first.first, filepath);
  }
  return true;
}
