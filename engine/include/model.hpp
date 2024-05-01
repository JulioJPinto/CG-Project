#ifndef MODEL_HPP
#define MODEL_HPP

extern "C" {
#include <GL/gl.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
}

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "utils.hpp"

std::vector<Point> generateVBO(const std::vector<Point>& points);

std::vector<unsigned int> generateIBO(const std::vector<Point>& points,
                                      const std::vector<Point>& vbo);

class Model {
 public:
  std::string filename;
  std::vector<Point> vbo;
  std::vector<unsigned int> ibo;
  std::vector<Point> normals;
  std::vector<Point2D> textures;
  int id;
  bool initialized = false;

  Model();
  Model(std::string filename, std::vector<Point> points);
  Model(std::string filename, std::vector<Point> points,
        std::vector<Point> normals, std::vector<Point2D> textures);

  void setupModel();
  void drawModel();

  std::vector<Point> getPoints();

 private:
  GLuint _vbo, _ibo;
  std::vector<Point> _points;
  Model(std::string filename, std::vector<Point> vbo,
        std::vector<unsigned int> ibo, int id, std::vector<Point> points);
  Model(std::string filename, std::vector<Point> vbo,
        std::vector<unsigned int> ibo, int id, std::vector<Point> points,
        std::vector<Point> normals, std::vector<Point2D> textures);
};

#endif  // MODEL_HPP