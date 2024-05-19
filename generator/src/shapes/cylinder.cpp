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

    Point n1(0.0f, -1.0f, 0.0f);
    for (int j = 0; j < 3; j++) {
      normals.push_back(n1);  // Push normals to normals vector
    }

    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));

    // face
    points.push_back(Point(px, -half, pz));
    points.push_back(Point(px, half, pz));

    Point n2(px, 0.0f, pz);
    for (int j = 0; j < 2; j++) {
      normals.push_back(n2);  // Push normals to normals vector
    }

    r -= alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, half, pz));

    n2 = Point(px, 0.0f, pz);
    normals.push_back(n2);  // Push normals to normals vector

    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));

    points.push_back(Point(px, half, pz));
    points.push_back(Point(px, -half, pz));

    Point n3 = Point(px, 0.0f, pz);

    for (int j = 0; j < 2; j++) {
      normals.push_back(n3);  // Push normals to normals vector
    }

    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, -half, pz));

    n3 = Point(px, 0.0f, pz);

    normals.push_back(n3);  // Push normals to normals vector

    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));

    // top
    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, half, pz));
    points.push_back(Point(0, half, 0));
    r -= alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, half, pz));

    Point n4(0.0f, 1.0f, 0.0f);
    for (int j = 0; j < 3; j++) {
      normals.push_back(n4);  // Push normals to normals vector
    }

    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));
    textures.push_back(Point2D(0.5f, 0.5f));
  }

  return std::make_pair(std::make_pair(points, normals), textures);
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
