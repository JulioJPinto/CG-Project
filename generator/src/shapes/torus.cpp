#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "save3d.hpp"
#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
torusAllPoints(float majorRadius, float minorRadius, int sides, int rings) {
  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

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

      // Normals
      Point n1 = Point(x1 - majorRadius * std::cos(theta1), y1,
                       z1 - majorRadius * std::sin(theta1));
      Point n2 = Point(x2 - majorRadius * std::cos(theta1), y2,
                       z2 - majorRadius * std::sin(theta1));
      Point n3 = Point(x3 - majorRadius * std::cos(theta2), y3,
                       z3 - majorRadius * std::sin(theta2));
      Point n4 = Point(x4 - majorRadius * std::cos(theta2), y4,
                       z4 - majorRadius * std::sin(theta2));

      // Assign normals to each vertex of the triangles
      normals.push_back(n1);
      normals.push_back(n2);
      normals.push_back(n4);

      normals.push_back(n1);
      normals.push_back(n4);
      normals.push_back(n3);

      // Texture coordinates
      float u1 = static_cast<float>(j) / static_cast<float>(sides);
      float u2 = static_cast<float>(j + 1) / static_cast<float>(sides);
      float v1 = static_cast<float>(i) / static_cast<float>(rings);
      float v2 = static_cast<float>(i + 1) / static_cast<float>(rings);

      textures.push_back(Point2D(u1, v1));
      textures.push_back(Point2D(u2, v1));
      textures.push_back(Point2D(u2, v2));

      textures.push_back(Point2D(u1, v1));
      textures.push_back(Point2D(u2, v2));
      textures.push_back(Point2D(u1, v2));
    }
  }

  return std::pair(std::pair(points, normals), textures);
}

bool generateTorus(float majorRadius, float minorRadius, int sides, int rings,
                   const char* filepath, bool advanced) {
  std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
            std::vector<Point2D>>
      torus = torusAllPoints(majorRadius, minorRadius, sides, rings);

  if (advanced) {
    save3DAdvancedfile(torus.first.first, torus.first.second, torus.second,
                       filepath);
  } else {
    saveToFile(torus.first.first, filepath);
  }

  return true;
}
