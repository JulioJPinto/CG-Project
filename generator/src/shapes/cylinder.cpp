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

  Point v;
  Point n;
  Point2D t;


    float delta = 2.0f * M_PI / slices;

    for (int i = 0; i < slices; ++i) {
        // topo
        // ponto central
        n = {0.0f, 1.0f, 0.0f};
        v = {0.0f, height / 2.0f, 0.0f};
        t = {0.4375f, 0.1875f};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        v = {radius * sin(i * delta), height / 2.0f, radius * cos(i * delta)};
        t = {0.4375f + 0.1875 * sin(i * delta), 0.1875f + 0.1875 * cos(i * delta)};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        v = {radius * sin((i + 1) * delta), height / 2.0f, radius * cos((i + 1) * delta)};
        t = {0.4375f + 0.1875 * sin((i + 1) * delta), 0.1875f + 0.1875 * cos((i + 1) * delta)};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);


        // corpo
        
        n = {sin(i + 1 * delta), 0.0f, cos(i + 1 * delta)};
        v = {radius * sin((i + 1) * delta), height / 2.0f, radius * cos((i + 1) * delta)};
        t = {(i + 1) / static_cast<float>(slices), 1.0f};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        n = {sin(i * delta), 0.0f, cos(i * delta)};
        v = {radius * sin(i * delta), height / 2.0f, radius * cos(i * delta)};
        t = {i / static_cast<float>(slices), 1.0f};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        n = {sin(i * delta), 0.0f, cos(i * delta)};
        v = {radius * sin(i * delta), -height / 2.0f, radius * cos(i * delta)};
        t = {i / static_cast<float>(slices), 0.375f};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        n = {sin(i + 1 * delta), 0.0f, cos(i + 1 * delta)};
        v = {radius * sin((i + 1) * delta), -height / 2.0f, radius * cos((i + 1) * delta)};
        t = {(i + 1) / static_cast<float>(slices), 0.375f};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        n = {sin(i + 1 * delta), 0.0f, cos(i + 1 * delta)};
        v = {radius * sin((i + 1) * delta), height / 2.0f, radius * cos((i + 1) * delta)};
        t = {(i + 1) / static_cast<float>(slices), 1.0f};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        n = {sin(i * delta), 0.0f, cos(i * delta)};
        v = {radius * sin(i * delta), -height / 2.0f, radius * cos(i * delta)};
        t = {i / static_cast<float>(slices), 0.375f};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);


        // base

        n = {0.0f, -1.0f, 0.0f};
        v = {0.0f, -height / 2.0f, 0.0f};
        t = {0.8125f, 0.1875f};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        n = {0.0f, -1.0f, 0.0f};
        v = {radius * sin((i + 1) * delta), -height / 2.0f, radius * cos((i + 1) * delta)};
        t = {0.8125f + 0.1875 * sin((i + 1) * delta), 0.1875f + 0.1875 * cos((i + 1) * delta)};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        n = {0.0f, -1.0f, 0.0f};
        v = {radius * sin(i * delta), -height / 2.0f, radius * cos(i * delta)};
        t = {0.8125f + 0.1875 * sin(i * delta), 0.1875f + 0.1875 * cos(i * delta)};

        points.push_back(v);
        normals.push_back(n);
        textures.push_back(t);

        

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
