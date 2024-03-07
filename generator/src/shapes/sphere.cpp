#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../common/include/utils.hpp"

std::vector<Point> sphereTriangles(float radius, int slices, int stacks) {
  std::vector<Point> points;

  for (int i = 0; i < slices; ++i) {
    float theta1 = static_cast<float>(i) * static_cast<float>(M_PI) /
                   static_cast<float>(slices);
    float theta2 = static_cast<float>(i + 1) * static_cast<float>(M_PI) /
                   static_cast<float>(slices);

    for (int j = 0; j < stacks; ++j) {
      float phi1 = static_cast<float>(j) * 2.0f * static_cast<float>(M_PI) /
                   static_cast<float>(stacks);
      float phi2 = static_cast<float>(j + 1) * 2.0f * static_cast<float>(M_PI) /
                   static_cast<float>(stacks);

      // Vertices
      float z1 = radius * std::sin(theta1) * std::cos(phi1);
      float x1 = radius * std::sin(theta1) * std::sin(phi1);
      float y1 = radius * std::cos(theta1);

      float z2 = radius * std::sin(theta1) * std::cos(phi2);
      float x2 = radius * std::sin(theta1) * std::sin(phi2);
      float y2 = radius * std::cos(theta1);

      float z3 = radius * std::sin(theta2) * std::cos(phi1);
      float x3 = radius * std::sin(theta2) * std::sin(phi1);
      float y3 = radius * std::cos(theta2);

      float z4 = radius * std::sin(theta2) * std::cos(phi2);
      float x4 = radius * std::sin(theta2) * std::sin(phi2);
      float y4 = radius * std::cos(theta2);

      points.push_back(Point(x1, y1, z1));
      points.push_back(Point(x4, y4, z4));
      points.push_back(Point(x2, y2, z2));

      // Second triangle
      points.push_back(Point(x1, y1, z1));
      points.push_back(Point(x3, y3, z3));
      points.push_back(Point(x4, y4, z4));
    }
  }

  return points;
}

bool generateSphere(float radius, int slices, int stacks,
                    const char* filepath) {
  std::vector<Point> triangles = sphereTriangles(radius, slices, stacks);

  if (triangles.empty()) {
    std::cerr << "Error: Empty vector of triangles.\n";
    return false;
  }

  saveToFile(triangles, filepath);

  return true;
}