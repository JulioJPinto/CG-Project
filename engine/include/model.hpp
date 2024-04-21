#ifndef MODEL_HPP
#define MODEL_HPP

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "../../common/include/utils.hpp"

std::vector<Point> generateVBO(const std::vector<Point>& points);

std::vector<unsigned int> generateIBO(const std::vector<Point>& points,
                                      const std::vector<Point>& vbo);

class Model {
 public:
  std::string filename;
  std::vector<Point> vbo;
  std::vector<unsigned int> ibo;
  int id;

  Model(std::string filename, std::vector<Point> points);

  void setupModel();

 private:
  Model(std::string filename, std::vector<Point> vbo,
        std::vector<unsigned int> ibo, int id);
};

void drawModel(const Model& model);

#endif  // MODEL_HPP