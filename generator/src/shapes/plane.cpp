#include <fstream>
#include <iostream>
#include <vector>

#include "../../common/include/utils.hpp"

std::vector<Point> planeTriangles(float length, int divisions) {
  float half = length / 2.0f;
  float steps = length / divisions;

  std::vector<Point> points;

  for (int i = 0; i < divisions; i++) {
    for (int j = 0; j < divisions; j++) {
      float y1 = 0.0f;
      float x1 = -half + i * steps;
      float z1 = -half + j * steps;
      float x2 = x1 + steps;
      float z2 = z1 + steps;

      Point p1(x1, y1, z1);
      Point p2(x2, y1, z1);
      Point p3(x1, y1, z2);
      Point p4(x2, y1, z2);

      points.push_back(p1);
      points.push_back(p3);
      points.push_back(p2);

      points.push_back(p2);
      points.push_back(p3);
      points.push_back(p4);
    }
  }

  return points;
}

bool generatePlane(float length, int divisions, const char* filepath) {
  std::vector<Point> triangles = planeTriangles(length, divisions);

  if (triangles.empty()) {
    std::cerr << "Error: Empty vector of triangles.\n";
    return false;
  }

  saveToFile(triangles, filepath);

  return true;
}
