#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "save3d.hpp"
#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
sphereAllPoints(float radius, int slices, int stacks) {
  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

  for (int i = 0; i < slices; ++i) {
    float theta1 = static_cast<float>(i) * static_cast<float>(M_PI) /
                   static_cast<float>(slices);
    float theta2 = static_cast<float>(i + 1) * static_cast<float>(M_PI) /
                   static_cast<float>(slices);

    for (int j = 0; j < stacks; ++j) {
      float phi1 = static_cast<float>(j) * static_cast<float>(M_PI) /
                   static_cast<float>(stacks);
      float phi2 = static_cast<float>(j + 1) * static_cast<float>(M_PI) /
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

      points.push_back(Point(x1, y1, z1));
      points.push_back(Point(x4, y4, z4));
      points.push_back(Point(x2, y2, z2));

      // Second triangle
      points.push_back(Point(x1, y1, z1));
      points.push_back(Point(x3, y3, z3));
      points.push_back(Point(x4, y4, z4));

      // Normals (approximated as the vertex positions normalized)
      Point n1(x1 / radius, y1 / radius, z1 / radius);
      Point n2(x2 / radius, y2 / radius, z2 / radius);
      Point n3(x3 / radius, y3 / radius, z3 / radius);
      Point n4(x4 / radius, y4 / radius, z4 / radius);

      // Assign normals to each vertex of the triangles
      normals.push_back(n1);
      normals.push_back(n4);
      normals.push_back(n2);

      normals.push_back(n1);
      normals.push_back(n3);
      normals.push_back(n4);

      // Texture coordinates
      float u1 = static_cast<float>(i) / static_cast<float>(slices);
      float u2 = static_cast<float>(i + 1) / static_cast<float>(slices);
      float v1 = static_cast<float>(j) / static_cast<float>(stacks);
      float v2 = static_cast<float>(j + 1) / static_cast<float>(stacks);

      textures.push_back(Point2D(u1, v1));
      textures.push_back(Point2D(u2, v2));
      textures.push_back(Point2D(u2, v1));

      textures.push_back(Point2D(u1, v1));
      textures.push_back(Point2D(u1, v2));
      textures.push_back(Point2D(u2, v2));
    }
  }

  return std::pair(std::pair(points, normals), textures);
}

bool generateSphere(float radius, int slices, int stacks, const char* filepath,
                    bool advanced) {
  std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
            std::vector<Point2D>>
      sphere = sphereAllPoints(radius, slices, stacks);

  if (advanced) {
    save3DAdvancedfile(sphere.first.first, sphere.first.second, sphere.second,
                       filepath);
  } else {
    saveToFile(sphere.first.first, filepath);
  }

  return true;
}