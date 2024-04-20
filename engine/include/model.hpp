#ifndef MODEL_HPP
#define MODEL_HPP

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "../../common/include/utils.hpp"

std::vector<Point> generateVBO(const std::vector<Point>& points);

std::vector<int> generateIBO(const std::vector<Point>& points,
                             const std::vector<Point>& vbo);

class Model {
 public:
  std::string filename;
  std::set<Point> points;
  std::vector<int> indices;
  int id;

  Model(std::string filename, std::set<Point> points, std::vector<int> indices,
        int id);

  void setupIndexBuffer();
};

#endif  // MODEL_HPP