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

std::vector<float> vPointstoFloats(std::vector<Vertex> points) {
  std::vector<float> floats;
  for(const Vertex& point : points) {
    floats.push_back(point.position.x);
    floats.push_back(point.position.y);
    floats.push_back(point.position.z);
    floats.push_back(point.normal.x);
    floats.push_back(point.normal.y);
    floats.push_back(point.normal.z);
    floats.push_back(point.texture.x);
    floats.push_back(point.texture.y);
  }
  return floats;
}

std::vector<Vertex> generateVBO(const std::vector<Vertex>& points) {
  std::vector<Vertex> vbo;
  std::unordered_map<Vertex, int, VertexHash> index_map;
  for (const Vertex& point : points) {
    if (index_map.find(point) == index_map.end()) {
      index_map[point] = vbo.size();
      vbo.push_back(point);
    }
  }
  return vbo;
}

std::vector<unsigned int> generateIBO(const std::vector<Vertex>& points,
                                      const std::vector<Vertex>& vbo) {
  std::vector<unsigned int> ibo;
  std::unordered_map<Vertex, int, VertexHash> index_map;
  for (size_t i = 0; i < vbo.size(); ++i) {
    index_map[vbo[i]] = i;
  }
  for (const Vertex& point : points) {
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

Model::Model(std::string filename, std::vector<Vertex> vbo,
        std::vector<unsigned int> ibo, int id, std::vector<Vertex> points) {
  this->filename = filename;
  this->vbo = vbo;
  this->ibo = ibo;
  this->id = id;
  this->initialized = false;
  this->_points = points;

}

Model::Model(std::string filename, std::vector<Vertex> points) {
  this->filename = filename;
  this->id = counter;
  this->vbo = generateVBO(points);
  this->ibo = generateIBO(points, this->vbo);
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
               
  //Specify the layout of the position data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Specify the layout of the vertex normal data
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Specify the layout of the texture coordinate data
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // Generate and bind index buffer
  glGenBuffers(1, &this->_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->ibo.size(),
               this->ibo.data(), GL_STATIC_DRAW);

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

std::vector<Vertex> Model::getPoints() { return this->_points; }
