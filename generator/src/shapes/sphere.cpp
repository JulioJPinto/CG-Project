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

      Point p1(x1, y1, z1);
      Point p2(x2, y2, z2);
      Point p3(x3, y3, z3);
      Point p4(x4, y4, z4);

      points.push_back(p1);
      points.push_back(p4);
      points.push_back(p2);
      points.push_back(p1);
      points.push_back(p3);
      points.push_back(p4);

      normals.push_back(p1.normalize());
      normals.push_back(p4.normalize());
      normals.push_back(p2.normalize());
      normals.push_back(p1.normalize());
      normals.push_back(p3.normalize());
      normals.push_back(p4.normalize());

      float u1 = static_cast<float>(i) / static_cast<float>(slices);
      float u2 = static_cast<float>(i + 1) / static_cast<float>(slices);
      float v1 = static_cast<float>(j) / static_cast<float>(stacks);
      float v2 = static_cast<float>(j + 1) / static_cast<float>(stacks);

      Point2D t1(u1, v1);
      Point2D t2(u2, v1);
      Point2D t3(u1, v2);
      Point2D t4(u2, v2);

      textures.push_back(t1);
      textures.push_back(t4);
      textures.push_back(t2);
      textures.push_back(t1);
      textures.push_back(t3);
      textures.push_back(t4);
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