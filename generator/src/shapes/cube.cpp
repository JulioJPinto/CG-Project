#include <fstream>
#include <iostream>
#include <vector>

#include "save3d.hpp"
#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
cubeAllPoints(float length, int divisions) {
  float halfSize = length / 2.0f;
  float step = length / divisions;

  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

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

      Point n1 = Point(0.0f, 0.0f, 1.0f);
      for (int i = 0; i < 6; i++) {
        normals.push_back(n1);
      }

      textures.push_back(Point2D(u1 / length, v1 / length));
      textures.push_back(Point2D(u2 / length, v1 / length));
      textures.push_back(Point2D(u1 / length, v2 / length));
      textures.push_back(Point2D(u1 / length, v2 / length));
      textures.push_back(Point2D(u2 / length, v1 / length));
      textures.push_back(Point2D(u2 / length, v2 / length));

      // Back Face
      points.push_back(Point(v1, u1, -halfSize));
      points.push_back(Point(v1, u2, -halfSize));
      points.push_back(Point(v2, u1, -halfSize));

      points.push_back(Point(v1, u2, -halfSize));
      points.push_back(Point(v2, u2, -halfSize));
      points.push_back(Point(v2, u1, -halfSize));

      Point n2 = Point(0.0f, 0.0f, -1.0f);
      for (int i = 0; i < 6; i++) {
        normals.push_back(n2);
      }

      textures.push_back(Point2D(1.0f - u1 / length, v1 / length));
      textures.push_back(Point2D(1.0f - u1 / length, v2 / length));
      textures.push_back(Point2D(1.0f - u2 / length, v1 / length));
      textures.push_back(Point2D(1.0f - u1 / length, v2 / length));
      textures.push_back(Point2D(1.0f - u2 / length, v2 / length));
      textures.push_back(Point2D(1.0f - u2 / length, v1 / length));

      // Left Face
      points.push_back(Point(-halfSize, v1, u1));
      points.push_back(Point(-halfSize, v1, u2));
      points.push_back(Point(-halfSize, v2, u1));

      points.push_back(Point(-halfSize, v1, u2));
      points.push_back(Point(-halfSize, v2, u2));
      points.push_back(Point(-halfSize, v2, u1));

      Point n3 = Point(-1.0f, 0.0f, 0.0f);
      for (int i = 0; i < 6; i++) {
        normals.push_back(n3);
      }

      textures.push_back(Point2D(v1 / length, 1.0f - u1 / length));
      textures.push_back(Point2D(v2 / length, 1.0f - u1 / length));
      textures.push_back(Point2D(v1 / length, 1.0f - u2 / length));
      textures.push_back(Point2D(v1 / length, 1.0f - u2 / length));
      textures.push_back(Point2D(v2 / length, 1.0f - u1 / length));
      textures.push_back(Point2D(v2 / length, 1.0f - u2 / length));

      // Right Face
      points.push_back(Point(halfSize, v1, u1));
      points.push_back(Point(halfSize, v2, u1));
      points.push_back(Point(halfSize, v1, u2));

      points.push_back(Point(halfSize, v1, u2));
      points.push_back(Point(halfSize, v2, u1));
      points.push_back(Point(halfSize, v2, u2));

      Point n4 = Point(1.0f, 0.0f, 0.0f);
      for (int i = 0; i < 6; i++) {
        normals.push_back(n4);
      }

      textures.push_back(Point2D(v1 / length, u1 / length));
      textures.push_back(Point2D(v2 / length, u1 / length));
      textures.push_back(Point2D(v1 / length, u2 / length));
      textures.push_back(Point2D(v1 / length, u2 / length));
      textures.push_back(Point2D(v2 / length, u1 / length));
      textures.push_back(Point2D(v2 / length, u2 / length));

      // Top Face
      points.push_back(Point(v1, halfSize, u1));
      points.push_back(Point(v1, halfSize, u2));
      points.push_back(Point(v2, halfSize, u1));

      points.push_back(Point(v1, halfSize, u2));
      points.push_back(Point(v2, halfSize, u2));
      points.push_back(Point(v2, halfSize, u1));

      Point n5 = Point(0.0f, 1.0f, 0.0f);
      for (int i = 0; i < 6; i++) {
        normals.push_back(n5);
      }

      textures.push_back(Point2D(u1 / length, 1.0f - v1 / length));
      textures.push_back(Point2D(u2 / length, 1.0f - v1 / length));
      textures.push_back(Point2D(u1 / length, 1.0f - v2 / length));
      textures.push_back(Point2D(u1 / length, 1.0f - v2 / length));
      textures.push_back(Point2D(u2 / length, 1.0f - v1 / length));
      textures.push_back(Point2D(u2 / length, 1.0f - v2 / length));

      // Bottom Face
      points.push_back(Point(v1, -halfSize, u1));
      points.push_back(Point(v2, -halfSize, u1));
      points.push_back(Point(v1, -halfSize, u2));

      points.push_back(Point(v1, -halfSize, u2));
      points.push_back(Point(v2, -halfSize, u1));
      points.push_back(Point(v2, -halfSize, u2));

      Point n6 = Point(0.0f, -1.0f, 0.0f);
      for (int i = 0; i < 6; i++) {
        normals.push_back(n6);
      }

      textures.push_back(Point2D(u1 / length, v1 / length));
      textures.push_back(Point2D(u2 / length, v1 / length));
      textures.push_back(Point2D(u1 / length, v2 / length));
      textures.push_back(Point2D(u1 / length, v2 / length));
      textures.push_back(Point2D(u2 / length, v1 / length));
      textures.push_back(Point2D(u2 / length, v2 / length));
    }
  }

  return std::pair(std::pair(points, normals), textures);
}

bool generateCube(float length, int divisions, const char* filepath) {
  std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
            std::vector<Point2D>>
      cube = cubeAllPoints(length, divisions);

  save3Dfile(cube.first.first, cube.first.second, cube.second, filepath);

  return true;
}
