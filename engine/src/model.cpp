#include <GL/glew.h>
extern "C" {
#include <GL/gl.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
}

#define _USE_MATH_DEFINES
#include <math.h>

#include <unordered_map>

#include "model.hpp"

unsigned int counter = 0;

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

std::vector<unsigned int> generateIBO(const std::vector<Point>& points,
                                      const std::vector<Point>& vbo) {
  std::vector<unsigned int> ibo;
  std::unordered_map<Point, int, PointHash> index_map;
  for (size_t i = 0; i < vbo.size(); ++i) {
    index_map[vbo[i]] = i;
  }
  for (const Point& point : points) {
    ibo.push_back(index_map[point]);
  }
  return ibo;
}

Model::Model() {
  this->filename = "";
  this->id = -1;
  this->initialized = false;
  counter++;
}

Model::Model(std::string filename, std::vector<Point> vbo,
             std::vector<unsigned int> ibo, int id, std::vector<Point> points) {
  this->filename = filename;
  this->vbo = vbo;
  this->ibo = ibo;
  this->id = id;
  this->initialized = false;
  this->_points = points;
}

Model::Model(std::string filename, std::vector<Point> points) {
  this->filename = filename;
  this->id = counter;
  this->vbo = generateVBO(points);
  this->ibo = generateIBO(points, this->vbo);
  this->initialized = false;
  this->_points = points;
  counter++;
}

Model::Model(std::string filename, std::vector<Point> points,
             std::vector<Point> normals, std::vector<Point2D> textures) {
  this->filename = filename;
  this->id = counter;
  this->vbo = generateVBO(points);
  this->ibo = generateIBO(points, this->vbo);
  this->normals = normals;
  this->textures = textures;
  this->initialized = false;
  this->_points = points;
  counter++;
}

void Model::setupModel() {
  std::vector<float> floats = vPointstoFloats(this->vbo);

  // Generate and bind vertex buffer
  glGenBuffers(1, &this->_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floats.size(), floats.data(),
               GL_STATIC_DRAW);

  // Generate and bind index buffer
  glGenBuffers(1, &this->_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->ibo.size(),
               this->ibo.data(), GL_STATIC_DRAW);

  if (normals.size() > 0) {
    std::vector<float> normalFloats = vPointstoFloats(this->normals);
    glGenBuffers(1, &this->_normals);
    glBindBuffer(GL_ARRAY_BUFFER, this->_normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normalFloats.size(),
                 normalFloats.data(), GL_STATIC_DRAW);
  }
}

void Model::drawModel() {
  if (!this->initialized) {
    this->initialized = true;
    setupModel();
  }

  glColor3f(1.0f, 1.0f, 1.0f);
  glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);
  glDrawElements(GL_TRIANGLES, this->ibo.size(), GL_UNSIGNED_INT, 0);
}

std::vector<Point> Model::getPoints() { return this->_points; }
