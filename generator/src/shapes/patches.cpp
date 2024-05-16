#include "shapes/patches.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "save3d.hpp"
#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
patchTriangles(const char* bezier_patch, const int tessellation) {
  std::vector<Point> controlPoints;

  std::ifstream file(bezier_patch);
  if (!file.is_open()) {
    std::cerr << "Error opening file\n";
    return std::make_pair(
        std::make_pair(std::vector<Point>(), std::vector<Point>()),
        std::vector<Point2D>());
  }

  size_t num_patches;
  file >> num_patches;

  std::vector<std::vector<size_t>> patches(num_patches,
                                           std::vector<size_t>(16));

  for (size_t i = 0; i < num_patches; ++i) {
    for (size_t j = 0; j < 16; ++j) {
      size_t idx;
      file >> idx;
      file.ignore();
      patches[i][j] = idx;
    }
  }

  size_t numberOfControlPoints;
  file >> numberOfControlPoints;

  for (size_t i = 0; i < numberOfControlPoints; ++i) {
    float x, y, z;
    file >> x;
    file.ignore();
    file >> y;
    file.ignore();
    file >> z;
    file.ignore();

    controlPoints.push_back(Point(x, y, z));
  }

  file.close();

  // calculate the coordinates of the points
  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

  for (size_t i = 0; i < num_patches; ++i) {
    std::vector<Point> patchControlPoints;
    for (size_t j = 0; j < 16; ++j) {
      patchControlPoints.push_back(controlPoints[patches[i][j]]);
    }

    for (int u = 0; u < tessellation; ++u) {
      for (int v = 0; v < tessellation; ++v) {
        float u1 = (float)u / tessellation;
        float v1 = (float)v / tessellation;
        float u2 = (float)(u + 1) / tessellation;
        float v2 = (float)(v + 1) / tessellation;

        // Calculate points, normals, and textures for the patch
        Point p1 = bezierPatch(patchControlPoints, u1, v1);
        Point p2 = bezierPatch(patchControlPoints, u2, v1);
        Point p3 = bezierPatch(patchControlPoints, u1, v2);
        Point p4 = bezierPatch(patchControlPoints, u2, v2);

        // Add points to the list
        points.push_back(p1);
        points.push_back(p3);
        points.push_back(p2);

        points.push_back(p2);
        points.push_back(p3);
        points.push_back(p4);

        // Calculate normals for each vertex (for flat shading)
        Point normal1 = calculateNormal(p1, p3, p2);
        Point normal2 = calculateNormal(p2, p3, p4);

        // Add normals to the list
        normals.push_back(normal1);
        normals.push_back(normal1);
        normals.push_back(normal1);

        normals.push_back(normal2);
        normals.push_back(normal2);
        normals.push_back(normal2);

        // Calculate texture coordinates
        Point2D texCoord1(u1, v1);
        Point2D texCoord2(u2, v1);
        Point2D texCoord3(u1, v2);
        Point2D texCoord4(u2, v2);

        // Add texture coordinates to the list
        textures.push_back(texCoord1);
        textures.push_back(texCoord3);
        textures.push_back(texCoord2);

        textures.push_back(texCoord2);
        textures.push_back(texCoord3);
        textures.push_back(texCoord4);
      }
    }
  }

  return std::make_pair(std::make_pair(points, normals), textures);
}

Point calculateNormal(const Point& p1, const Point& p2, const Point& p3) {
  // Calculate normal using cross product
  Point v1 = (p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);  // (p2 - p1)
  Point v2 = (p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);  // (p3 - p1)

  printf("V1: %f %f %f\n", v1.x, v1.y, v1.z);
  printf("V2: %f %f %f\n", v2.x, v2.y, v2.z);

  Point n = (v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
             v1.x * v2.y - v1.y * v2.x);

  printf("Normal: %f %f %f\n", n.x, n.y, n.z);
  return n;
}

Point bezierPatch(const std::vector<Point>& controlPoints, float u, float v) {
  Point p(0, 0, 0);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      float b = bernstein(i, u) * bernstein(j, v);
      p.x += controlPoints[i * 4 + j].x * b;
      p.y += controlPoints[i * 4 + j].y * b;
      p.z += controlPoints[i * 4 + j].z * b;
    }
  }

  return p;
}

float bernstein(int i, float t) {
  switch (i) {
    case 0:
      return pow(1 - t, 3);
    case 1:
      return 3 * t * pow(1 - t, 2);
    case 2:
      return 3 * pow(t, 2) * (1 - t);
    case 3:
      return pow(t, 3);
    default:
      return 0;
  }
}

bool generatePatch(const char* bezier_patch, const int tessellation,
                   const char* fileName, bool advanced) {
  std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
            std::vector<Point2D>>
      patch = patchTriangles(bezier_patch, tessellation);

  if (advanced) {
    save3DAdvancedfile(patch.first.first, patch.first.second, patch.second,
                       fileName);
  } else {
    saveToFile(patch.first.first, fileName);
  }

  return true;
}