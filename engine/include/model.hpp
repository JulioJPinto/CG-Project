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
#include <stb_image/stb_image.h>

#include "light.hpp"
#include "utils.hpp"
#include "vertex.hpp"

std::vector<Vertex> generateVBO(const std::vector<Vertex>& points);

std::vector<unsigned int> generateIBO(const std::vector<Vertex>& points,
                                      const std::vector<Vertex>& vbo);

class Model {
 public:
  std::string filename;
  std::vector<Vertex> vbo;
  std::vector<unsigned int> ibo;
  int id;
  bool initialized = false;
  Material material;

  Model();
  Model(std::string filename, std::vector<Vertex> points);

  void initModel();
  void drawModel();


  std::vector<Vertex> getPoints();

 private:
  GLuint _vbo, _ibo, _normals, _textures;
  std::vector<Vertex> _points;
  std::string _texture_filepath;
  Model(std::string filename, std::vector<Vertex> vbo,
        std::vector<unsigned int> ibo, int id, std::vector<Vertex> points);
  bool loadTexture();
  void setupModel();

};

#endif  // MODEL_HPP