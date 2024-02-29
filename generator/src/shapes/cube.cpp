#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"

std::vector<Point> cubeTriangles(float length, int divisions) {
  float halfSize = length / 2.0f;
  float step = length / divisions;

  std::vector<Point> points;

  for (int i = 0; i < divisions; ++i) {
    for (int j = 0; j < divisions; ++j) {
      float x1 = -halfSize + i * step;
      float y1 = -halfSize + j * step;
      float x2 = x1 + step;
      float y2 = y1 + step;

      // Front Face
      points.push_back(Point(x1, y1, halfSize));
      points.push_back(Point(x2, y1, halfSize));
      points.push_back(Point(x1, y2, halfSize));

      points.push_back(Point(x1, y2, halfSize));
      points.push_back(Point(x2, y1, halfSize));
      points.push_back(Point(x2, y2, halfSize));

      // Back Face
      points.push_back(Point(x1, y1, -halfSize));
      points.push_back(Point(x1, y2, -halfSize));
      points.push_back(Point(x2, y1, -halfSize));

      points.push_back(Point(x1, y2, -halfSize));
      points.push_back(Point(x2, y2, -halfSize));
      points.push_back(Point(x2, y1, -halfSize));

      // Left Face
      points.push_back(Point(-halfSize, x1, y1));
      points.push_back(Point(-halfSize, x1, y2));
      points.push_back(Point(-halfSize, x2, y1));

      points.push_back(Point(-halfSize, x1, y2));
      points.push_back(Point(-halfSize, x2, y2));
      points.push_back(Point(-halfSize, x2, y1));

      // Right Face
      points.push_back(Point(halfSize, x1, y1));
      points.push_back(Point(halfSize, x2, y1));
      points.push_back(Point(halfSize, x1, y2));

      points.push_back(Point(halfSize, x1, y2));
      points.push_back(Point(halfSize, x2, y1));
      points.push_back(Point(halfSize, x2, y2));

      // Top Face
      points.push_back(Point(x1, halfSize, y1));
      points.push_back(Point(x1, halfSize, y2));
      points.push_back(Point(x2, halfSize, y1));

      points.push_back(Point(x1, halfSize, y2));
      points.push_back(Point(x2, halfSize, y2));
      points.push_back(Point(x2, halfSize, y1));

      // Bottom Face
      points.push_back(Point(x1, -halfSize, y1));
      points.push_back(Point(x2, -halfSize, y1));
      points.push_back(Point(x1, -halfSize, y2));

      points.push_back(Point(x1, -halfSize, y2));
      points.push_back(Point(x2, -halfSize, y1));
      points.push_back(Point(x2, -halfSize, y2));
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
