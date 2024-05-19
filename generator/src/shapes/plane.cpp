#include <fstream>
#include <iostream>
#include <vector>

#include "save3d.hpp"
#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
planeAllPoints(float length, int divisions) {
  float half = length / 2.0f;
  float steps = length / divisions;

  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

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

      // Normals (assuming plane lies in the XY plane)
      for (int i = 0; i < 6; i++) {
        Point n(0.0f, 1.0f, 0.0f);
        normals.push_back(n);
      }

      // Texture coordinates
      float u1 = static_cast<float>(i) / static_cast<float>(divisions);
      float u2 = static_cast<float>(i + 1) / static_cast<float>(divisions);
      float v1 = static_cast<float>(j) / static_cast<float>(divisions);
      float v2 = static_cast<float>(j + 1) / static_cast<float>(divisions);

      textures.push_back(Point2D(u1, v1));
      textures.push_back(Point2D(u1, v2));
      textures.push_back(Point2D(u2, v1));

      textures.push_back(Point2D(u2, v1));
      textures.push_back(Point2D(u1, v2));
      textures.push_back(Point2D(u2, v2));
    }
  }

  return std::pair(std::pair(points, normals), textures);
}

bool generatePlane(float length, int divisions, const char* filepath,
                   bool advanced) {
  std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
            std::vector<Point2D>>
      plane = planeAllPoints(length, divisions);

  if (advanced) {
    save3DAdvancedfile(plane.first.first, plane.first.second, plane.second,
                       filepath);
  } else {
    saveToFile(plane.first.first, filepath);
  }

  return true;
}
