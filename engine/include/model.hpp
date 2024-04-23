#ifndef MODEL_HPP
#define MODEL_HPP

#include <GL/glut.h>

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
  bool initialized = false;

  Model(std::string filename, std::vector<Point> points);

  void setupModel();
  void drawModel();

 private:
  GLuint _vbo, _ibo;
  Model(std::string filename, std::vector<Point> vbo,
        std::vector<unsigned int> ibo, int id);
};

Model getModel(std::string filename);

#endif  // MODEL_HPP