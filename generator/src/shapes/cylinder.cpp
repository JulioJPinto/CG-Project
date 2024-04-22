#include "../../include/shapes/cylinder.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"

std::vector<Point> cylinderTriangles(const float radius, const float height,
                                     const int slices) {
  std::vector<Point> vertex;

  float alpha = 2 * M_PI / slices;
  float half = height / 2;

  float r = 0;

  for (int i = 0; i < slices; i++) {
    // base
    float px = radius * sin(r);
    float pz = radius * cos(r);
    vertex.push_back(Point(px, -half, pz));
    vertex.push_back(Point(0, -half, 0));
    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    vertex.push_back(Point(px, -half, pz));

    // face
    vertex.push_back(Point(px, -half, pz));
    vertex.push_back(Point(px, half, pz));
    r -= alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    vertex.push_back(Point(px, half, pz));

    vertex.push_back(Point(px, half, pz));
    vertex.push_back(Point(px, -half, pz));
    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    vertex.push_back(Point(px, -half, pz));

    // topo
    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    vertex.push_back(Point(px, half, pz));
    vertex.push_back(Point(0, half, 0));
    r -= alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    vertex.push_back(Point(px, half, pz));
  }

  return vertex;
}

bool generateCylinder(float radius, float height, int slices,
                      const char *filepath) {
  std::vector<Point> triangles = cylinderTriangles(radius, height, slices);

  if (triangles.empty()) {
    std::cerr << "Error: Empty vector of triangles.\n";
    return false;
  }

  saveToFile(triangles, filepath);

  return true;
}
