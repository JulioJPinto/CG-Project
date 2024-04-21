#include <GL/glew.h>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <unordered_map>

#include "model.hpp"

#define MAX 10

std::vector<Model> models;
int counter = 0;

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

Model::Model(std::string filename, std::vector<Point> vbo,
             std::vector<unsigned int> ibo, int id) {
  this->filename = filename;
  this->vbo = vbo;
  this->ibo = ibo;
  this->id = id;
}

Model::Model(std::string filename, std::vector<Point> points) {
  this->filename = filename;

  // Check if the model already exists in the models vector
  bool exists = false;
  for (const Model& model : models) {
    if (filename == model.filename) {
      exists = true;
      *this = model;
      break;
    }
  }

  if (!exists) {
    this->id = counter;
    this->vbo = generateVBO(points);
    this->ibo = generateIBO(points, this->vbo);
    models.push_back(*this);
    counter++;
  }
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
  this->initialized = true;
}

void Model::drawModel() {
  if(!this->initialized) {
    setupModel();
  }
  
  glColor3f(1.0f, 1.0f, 1.0f);
  glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);
  glDrawElements(GL_TRIANGLES, this->_ibo, GL_UNSIGNED_INT, 0);
}
