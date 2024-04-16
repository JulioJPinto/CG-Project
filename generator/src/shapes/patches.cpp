#include "../../include/shapes/patches.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "../../common/include/utils.hpp"


std::vector<Point> patchTriangles(const char* bezier_patch, const int tessellation) {
  std::vector<Point> controlPoints;

  std::ifstream file(bezier_patch);
  if (!file.is_open()) {
    std::cerr << "Error opening file\n";
    return controlPoints;
  }

  size_t num_patches;
  file >> num_patches;

  std::vector<std::vector<size_t>> patches(num_patches, std::vector<size_t>(16));

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

  //calculate the coordinates of the points
  std::vector<Point> points;

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

        Point p1 = bezierPatch(patchControlPoints, u1, v1);
        Point p2 = bezierPatch(patchControlPoints, u2, v1);
        Point p3 = bezierPatch(patchControlPoints, u1, v2);
        Point p4 = bezierPatch(patchControlPoints, u2, v2);

        points.push_back(p1);
        points.push_back(p3);
        points.push_back(p2);

        points.push_back(p2);
        points.push_back(p3);
        points.push_back(p4);
      }
    }

  }

  return points;


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



bool generatePatch(const char* bezier_patch , const int tessellation, const char* fileName) {
  
  std::vector<Point> triangles = patchTriangles(bezier_patch, tessellation);

  if(triangles.empty()) {
    std::cerr << "Error generating patch\n";
    return false;
  }
  
  saveToFile(triangles, fileName);

  return true;
}