
#include <GL/glew.h>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <unordered_map>

#include "model.hpp"

#define MAX 5

std::vector<float> vPointstoFloats(std::vector<Point> points) {
  std::vector<float> floats;
  for (size_t i = 0; i < points.size(); i++) {
    floats.push_back(points[i].x);
    floats.push_back(points[i].y);
    floats.push_back(points[i].z);
  }
  return floats;
}

std::vector<Point> generateVBO(const std::vector<Point>& points) {
  std::vector<Point> vbo;
  std::unordered_map<Point, int, PointHash> index_map;
  for (const Point& point : points) {
    if (index_map.find(point) == index_map.end()) {
      index_map[point] = vbo.size();
      vbo.push_back(point);
    }
  }
  return vbo;
}

std::vector<int> generateIBO(const std::vector<Point>& points,
                             const std::vector<Point>& vbo) {
  std::vector<int> ibo;
  std::unordered_map<Point, int, PointHash> index_map;
  for (size_t i = 0; i < vbo.size(); ++i) {
    index_map[vbo[i]] = i;
  }
  for (const Point& point : points) {
    std::cout << "Point: " << point.x << " " << point.y << " " << point.z
              << std::endl;
    ibo.push_back(index_map[point]);
    std::cout << index_map[point] << std::endl;
  }
  return ibo;
}
