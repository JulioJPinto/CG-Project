#include "shapes/patches.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "save3d.hpp"
#include "utils.hpp"

Point bezierPatch(const std::vector<Point>& controlPoints, float u, float v);
Point bezierPatchDU(const std::vector<Point>& controlPoints, float u, float v);
Point bezierPatchDV(const std::vector<Point>& controlPoints, float u, float v);
float bernstein(int i, float t);

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
        float u1 = static_cast<float>(u) / tessellation;
        float v1 = static_cast<float>(v) / tessellation;
        float u2 = static_cast<float>(u + 1) / tessellation;
        float v2 = static_cast<float>(v + 1) / tessellation;

        // Calculate points for the patch
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

        // Calculate normals using derivatives for smooth shading
        Point du1 = bezierPatchDU(patchControlPoints, u1, v1);
        Point dv1 = bezierPatchDV(patchControlPoints, u1, v1);
        Point normal1 = dv1.cross(du1);  // Switched the order
        float length1 =
            std::sqrt(normal1.x * normal1.x + normal1.y * normal1.y +
                      normal1.z * normal1.z);
        if (length1 != 0) {
          normal1.x /= length1;
          normal1.y /= length1;
          normal1.z /= length1;
        }

        Point du2 = bezierPatchDU(patchControlPoints, u2, v1);
        Point dv2 = bezierPatchDV(patchControlPoints, u2, v1);
        Point normal2 = dv2.cross(du2);  // Switched the order
        float length2 =
            std::sqrt(normal2.x * normal2.x + normal2.y * normal2.y +
                      normal2.z * normal2.z);
        if (length2 != 0) {
          normal2.x /= length2;
          normal2.y /= length2;
          normal2.z /= length2;
        }

        Point du3 = bezierPatchDU(patchControlPoints, u1, v2);
        Point dv3 = bezierPatchDV(patchControlPoints, u1, v2);
        Point normal3 = dv3.cross(du3);  // Switched the order
        float length3 =
            std::sqrt(normal3.x * normal3.x + normal3.y * normal3.y +
                      normal3.z * normal3.z);
        if (length3 != 0) {
          normal3.x /= length3;
          normal3.y /= length3;
          normal3.z /= length3;
        }

        Point du4 = bezierPatchDU(patchControlPoints, u2, v2);
        Point dv4 = bezierPatchDV(patchControlPoints, u2, v2);
        Point normal4 = dv4.cross(du4);  // Switched the order
        float length4 =
            std::sqrt(normal4.x * normal4.x + normal4.y * normal4.y +
                      normal4.z * normal4.z);
        if (length4 != 0) {
          normal4.x /= length4;
          normal4.y /= length4;
          normal4.z /= length4;
        }

        // Add normals to the list
        normals.push_back(normal1);
        normals.push_back(normal3);
        normals.push_back(normal2);

        normals.push_back(normal2);
        normals.push_back(normal3);
        normals.push_back(normal4);

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

Point bezierPatchDU(const std::vector<Point>& controlPoints, float u, float v) {
  Point p(0, 0, 0);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      float db = bernsteinDerivative(i, u) * bernstein(j, v);
      p.x += controlPoints[i * 4 + j].x * db;
      p.y += controlPoints[i * 4 + j].y * db;
      p.z += controlPoints[i * 4 + j].z * db;
    }
  }

  return p;
}

Point bezierPatchDV(const std::vector<Point>& controlPoints, float u, float v) {
  Point p(0, 0, 0);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      float db = bernstein(i, u) * bernsteinDerivative(j, v);
      p.x += controlPoints[i * 4 + j].x * db;
      p.y += controlPoints[i * 4 + j].y * db;
      p.z += controlPoints[i * 4 + j].z * db;
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

float bernsteinDerivative(int i, float t) {
  switch (i) {
    case 0:
      return -3 * pow(1 - t, 2);
    case 1:
      return 3 * pow(1 - t, 2) - 6 * t * (1 - t);
    case 2:
      return 6 * t * (1 - t) - 3 * pow(t, 2);
    case 3:
      return 3 * pow(t, 2);
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