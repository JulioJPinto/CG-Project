#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../common/include/utils.hpp"

std::vector<Point> torusTriangles(float majorRadius, float minorRadius,
                                  int sides, int rings) {
  std::vector<Point> points;

  for (int i = 0; i < rings; ++i) {
    float theta1 = static_cast<float>(i) * 2.0f * static_cast<float>(M_PI) /
                   static_cast<float>(rings);
    float theta2 = static_cast<float>(i + 1) * 2.0f * static_cast<float>(M_PI) /
                   static_cast<float>(rings);

    for (int j = 0; j < sides; ++j) {
      float phi1 = static_cast<float>(j) * 2.0f * static_cast<float>(M_PI) /
                   static_cast<float>(sides);
      float phi2 = static_cast<float>(j + 1) * 2.0f * static_cast<float>(M_PI) /
                   static_cast<float>(sides);

      // Vertices
      float x1 =
          (majorRadius + minorRadius * std::cos(phi1)) * std::cos(theta1);
      float y1 = minorRadius * std::sin(phi1);
      float z1 =
          (majorRadius + minorRadius * std::cos(phi1)) * std::sin(theta1);

      float x2 =
          (majorRadius + minorRadius * std::cos(phi2)) * std::cos(theta1);
      float y2 = minorRadius * std::sin(phi2);
      float z2 =
          (majorRadius + minorRadius * std::cos(phi2)) * std::sin(theta1);

      float x3 =
          (majorRadius + minorRadius * std::cos(phi1)) * std::cos(theta2);
      float y3 = minorRadius * std::sin(phi1);
      float z3 =
          (majorRadius + minorRadius * std::cos(phi1)) * std::sin(theta2);

      float x4 =
          (majorRadius + minorRadius * std::cos(phi2)) * std::cos(theta2);
      float y4 = minorRadius * std::sin(phi2);
      float z4 =
          (majorRadius + minorRadius * std::cos(phi2)) * std::sin(theta2);

      // Push vertices in counter-clockwise order
      points.push_back(Point(x1, y1, z1));
      points.push_back(Point(x2, y2, z2));
      points.push_back(Point(x4, y4, z4));

      points.push_back(Point(x1, y1, z1));
      points.push_back(Point(x4, y4, z4));
      points.push_back(Point(x3, y3, z3));
    }
  }

  return points;
}

bool generateTorus(float majorRadius, float minorRadius, int sides, int rings,
                   const char* filepath) {
  std::vector<Point> triangles =
      torusTriangles(majorRadius, minorRadius, sides, rings);

  if (triangles.empty()) {
    std::cerr << "Error: Empty vector of triangles.\n";
    return false;
  }

  saveToFile(triangles, filepath);

  return true;
}