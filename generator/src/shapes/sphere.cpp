#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"

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
      float x1 = radius * std::sin(theta1) * std::cos(phi1);
      float y1 = radius * std::sin(theta1) * std::sin(phi1);
      float z1 = radius * std::cos(theta1);

      float x2 = radius * std::sin(theta1) * std::cos(phi2);
      float y2 = radius * std::sin(theta1) * std::sin(phi2);
      float z2 = radius * std::cos(theta1);

      float x3 = radius * std::sin(theta2) * std::cos(phi1);
      float y3 = radius * std::sin(theta2) * std::sin(phi1);
      float z3 = radius * std::cos(theta2);

      float x4 = radius * std::sin(theta2) * std::cos(phi2);
      float y4 = radius * std::sin(theta2) * std::sin(phi2);
      float z4 = radius * std::cos(theta2);

      // Push vertices in counter-clockwise order
      points.push_back(Point(y1, x1, z1));
      points.push_back(Point(y2, x2, z2));
      points.push_back(Point(y4, x4, z4));

      points.push_back(Point(y1, x1, z1));
      points.push_back(Point(y4, x4, z4));
      points.push_back(Point(y3, x3, z3));
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