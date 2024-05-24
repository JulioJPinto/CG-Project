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

#include <stb_image/stb_image.h>

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "light.hpp"
#include "utils.hpp"
#include "vertex.hpp"
#include "frustsum.hpp"

std::vector<Vertex> generateVBO(const std::vector<Vertex>& points);

std::vector<unsigned int> generateIBO(const std::vector<Vertex>& points,
                                      const std::vector<Vertex>& vbo);

class Model {
 public:
  std::string filename, texture_filepath;
  std::vector<Vertex> vbo;
  std::vector<unsigned int> ibo;
  int id;
  bool initialized = false;
  BoundingSphere bounding_sphere;
  Material material;

  Model();
  Model(std::string filename, std::vector<Vertex> points);

  void initModel();
  void drawModel(const Frustsum& f);
  void setupModel();
  bool loadTexture();
  bool isInsideFrustsum(const Frustsum& frustsum) const;

  std::vector<Vertex> getPoints();

 private:
  GLuint _vbo, _ibo, _normals, _textures, _texture_id;
  std::vector<Vertex> _points;
  Model(std::string filename, std::vector<Vertex> vbo,
        std::vector<unsigned int> ibo, int id, std::vector<Vertex> points);
};

#endif  // MODEL_HPP