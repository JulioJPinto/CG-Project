#include "shapes/cylinder.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "save3d.hpp"
#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
calculateCylinder(const float radius, const float height, const int slices) {
  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;

  float alpha = 2 * M_PI / slices;
  float half = height / 2;

  float r = 0;

  for (int i = 0; i < slices; i++) {
    // base
    float px = radius * sin(r);
    float pz = radius * cos(r);
    points.push_back(Point(px, -half, pz));
    points.push_back(Point(0, -half, 0));
    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, -half, pz));

    for (int i = 0; i < 3; i++) {
      Point n(0.0f, -1.0f, 0.0f);
      points.push_back(n);
    }

    // face
    points.push_back(Point(px, -half, pz));
    points.push_back(Point(px, half, pz));
    r -= alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, half, pz));

    for (int i = 0; i < 3; i++) {
      Point n(px, 0.0f, pz);
      points.push_back(n);
    }

    points.push_back(Point(px, half, pz));
    points.push_back(Point(px, -half, pz));
    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, -half, pz));

    for (int i = 0; i < 3; i++) {
      Point n(px, 0.0f, pz);
      points.push_back(n);
    }

    // topo
    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, half, pz));
    points.push_back(Point(0, half, 0));
    r -= alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, half, pz));

    for (int i = 0; i < 3; i++) {
      Point n(0.0f, 1.0f, 0.0f);
      points.push_back(n);
    }

    // Calculate texture coordinates
    float theta =
        static_cast<float>(i) / static_cast<float>(slices - 1) * 2.0f * M_PI;
    textures.push_back(
        Point2D(static_cast<float>(i) / static_cast<float>(slices - 1), 0.0f));
    textures.push_back(
        Point2D(static_cast<float>(i) / static_cast<float>(slices - 1), 1.0f));
    textures.push_back(Point2D(
        static_cast<float>((i + 1) % slices) / static_cast<float>(slices - 1),
        1.0f));

    textures.push_back(Point2D(
        static_cast<float>((i + 1) % slices) / static_cast<float>(slices - 1),
        1.0f));
    textures.push_back(Point2D(
        static_cast<float>((i + 1) % slices) / static_cast<float>(slices - 1),
        0.0f));
    textures.push_back(
        Point2D(static_cast<float>(i) / static_cast<float>(slices - 1), 0.0f));
  }

  return std::pair(std::pair(points, normals), textures);
}

bool generateCylinder(float radius, float height, int slices,
                      const char* filepath, bool advanced) {
  std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
            std::vector<Point2D>>
      cylinder = calculateCylinder(radius, height, slices);

  if (advanced) {
    save3DAdvancedfile(cylinder.first.first, cylinder.first.second,
                       cylinder.second, filepath);
  } else {
    saveToFile(cylinder.first.first, filepath);
  }

  return true;
}
