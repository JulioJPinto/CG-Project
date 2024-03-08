#include <fstream>
#include <iostream>
#include <vector>

#include "../../common/include/utils.hpp"

std::vector<Point> cubeTriangles(float length, int divisions) {
  float halfSize = length / 2.0f;
  float step = length / divisions;

  std::vector<Point> points;

  for (int i = 0; i < divisions; ++i) {
    for (int j = 0; j < divisions; ++j) {
      float v1 = -halfSize + i * step;
      float u1 = -halfSize + j * step;
      float v2 = v1 + step;
      float u2 = u1 + step;

      // Front Face
      points.push_back(Point(v1, u1, halfSize));
      points.push_back(Point(v2, u1, halfSize));
      points.push_back(Point(v1, u2, halfSize));

      points.push_back(Point(v1, u2, halfSize));
      points.push_back(Point(v2, u1, halfSize));
      points.push_back(Point(v2, u2, halfSize));

      // Back Face
      points.push_back(Point(v1, u1, -halfSize));
      points.push_back(Point(v1, u2, -halfSize));
      points.push_back(Point(v2, u1, -halfSize));

      points.push_back(Point(v1, u2, -halfSize));
      points.push_back(Point(v2, u2, -halfSize));
      points.push_back(Point(v2, u1, -halfSize));

      // Left Face
      points.push_back(Point(-halfSize, v1, u1));
      points.push_back(Point(-halfSize, v1, u2));
      points.push_back(Point(-halfSize, v2, u1));

      points.push_back(Point(-halfSize, v1, u2));
      points.push_back(Point(-halfSize, v2, u2));
      points.push_back(Point(-halfSize, v2, u1));

      // Right Face
      points.push_back(Point(halfSize, v1, u1));
      points.push_back(Point(halfSize, v2, u1));
      points.push_back(Point(halfSize, v1, u2));

      points.push_back(Point(halfSize, v1, u2));
      points.push_back(Point(halfSize, v2, u1));
      points.push_back(Point(halfSize, v2, u2));

      // Top Face
      points.push_back(Point(v1, halfSize, u1));
      points.push_back(Point(v1, halfSize, u2));
      points.push_back(Point(v2, halfSize, u1));

      points.push_back(Point(v1, halfSize, u2));
      points.push_back(Point(v2, halfSize, u2));
      points.push_back(Point(v2, halfSize, u1));

      // Bottom Face
      points.push_back(Point(v1, -halfSize, u1));
      points.push_back(Point(v2, -halfSize, u1));
      points.push_back(Point(v1, -halfSize, u2));

      points.push_back(Point(v1, -halfSize, u2));
      points.push_back(Point(v2, -halfSize, u1));
      points.push_back(Point(v2, -halfSize, u2));
    }
  }

  return points;
}

bool generateCube(float length, int divisions, const char* filepath) {
  std::vector<Point> triangles = cubeTriangles(length, divisions);

  if (triangles.empty()) {
    std::cerr << "Error: Empty vector of triangles.\n";
    return false;
  }

  saveToFile(triangles, filepath);

  return true;
}
