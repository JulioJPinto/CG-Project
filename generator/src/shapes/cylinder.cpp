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

  Point2D t_top_center = Point2D(7.f / 16.f, 3.f / 16.f);
  Point2D t_bot_center = Point2D(13.f / 16.f, 3.f / 16.f);
  Point2D t_side = Point2D(0.f, 3.f / 8.f);
  float t_side_height = 5.f / 8.f;
  float t_radius = 3.f / 16.f;

  float curr_alpha = 0;
  float next_alpha = 0;

  for (int i = 0; i < slices; i++) {
    next_alpha = alpha * (i+1);

    // base
    float px = radius * sin(r);
    float pz = radius * cos(r);
    points.push_back(Point(px, -half, pz));
    points.push_back(Point(0, -half, 0));

    textures.push_back(Point2D(t_bot_center.x + t_radius * sin(r), t_bot_center.y + t_radius * cos(r)));
    textures.push_back(t_bot_center);


    r += alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, -half, pz));

    textures.push_back(Point2D(t_bot_center.x + t_radius * sin(r), t_bot_center.y + t_radius * cos(r)));

    Point n1(0.0f, -1.0f, 0.0f);
    for (int j = 0; j < 3; j++) {
      normals.push_back(n1);  // Push normals to normals vector
    }

    

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

    textures.push_back(Point2D(t_top_center.x + t_radius * sin(curr_alpha), t_top_center.y + t_radius * cos(curr_alpha)));
    textures.push_back(t_top_center);
    r -= alpha;
    px = radius * sin(r);
    pz = radius * cos(r);
    points.push_back(Point(px, half, pz));

    textures.push_back(Point2D(t_top_center.x + t_radius * sin(next_alpha), t_top_center.y + t_radius * cos(next_alpha)));

    Point n4(0.0f, 1.0f, 0.0f);
    for (int j = 0; j < 3; j++) {
      normals.push_back(n4);  // Push normals to normals vector
    }

    curr_alpha = next_alpha;
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
