#include <GL/glew.h>
extern "C" {
#include <GL/gl.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
}

#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>

#include "model.hpp"

unsigned int counter = 0;

std::vector<float> positionsFloats(std::vector<Vertex> points) {
  std::vector<float> floats;
  for (const Vertex& point : points) {
    floats.push_back(point.position.x);
    floats.push_back(point.position.y);
    floats.push_back(point.position.z);
  }
  return floats;
}

std::vector<float> normalFloats(std::vector<Vertex> points) {
  std::vector<float> floats;
  for (const Vertex& point : points) {
    floats.push_back(point.normal.x);
    floats.push_back(point.normal.y);
    floats.push_back(point.normal.z);
  }
  return floats;
}

std::vector<float> textureFloats(std::vector<Vertex> points) {
  std::vector<float> floats;
  for (const Vertex& point : points) {
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
             std::vector<unsigned int> ibo, int id,
             std::vector<Vertex> points) {
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
  this->bounding_sphere = BoundingSphere(points);
  this->initialized = false;
  this->_points = points;
  counter++;
}

void Model::initModel() {
  if (!this->initialized) {
    this->initialized = true;
    setupModel();

    if (this->texture_filepath != "") {
      bool tex = loadTexture();
      if (!tex) {
        std::cerr << "Error loading texture\n";
      }
    }
  }
}

bool Model::loadTexture() {
  // Load image data
  int width, height, num_channels;
  unsigned char* image_data = stbi_load(this->texture_filepath.data(), &width,
                                        &height, &num_channels, STBI_rgb);

  if (!image_data) {
    std::cerr << "Failed to load texture: " << this->texture_filepath
              << std::endl;
    return false;
  }

  glGenTextures(1, &this->_texture_id);
  glBindTexture(GL_TEXTURE_2D, this->_texture_id);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Para provar que a textura do teapot ser diferente se deve ao Mipmap troca se os comandos abaixo pelos comentados
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  // Upload data to GPU
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image_data);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);

  // Free image data after uploading it
  stbi_image_free(image_data);

  return true;
}

void Model::setupModel() {
  std::vector<float> points = positionsFloats(this->vbo);
  std::vector<float> normals = normalFloats(this->vbo);
  std::vector<float> textures = textureFloats(this->vbo);

  // Generate and bind vertex buffer

  glGenBuffers(1, &this->_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(),
               GL_STATIC_DRAW);

  glGenBuffers(1, &this->_normals);
  glBindBuffer(GL_ARRAY_BUFFER, this->_normals);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(),
               GL_STATIC_DRAW);

  glGenBuffers(1, &this->_textures);
  glBindBuffer(GL_ARRAY_BUFFER, this->_textures);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textures.size(),
               textures.data(), GL_STATIC_DRAW);

  // Generate and bind index buffer
  glGenBuffers(1, &this->_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->ibo.size(),
               this->ibo.data(), GL_STATIC_DRAW);
}

void Model::drawModel() {
  initModel();

  glBindTexture(GL_TEXTURE_2D, this->_texture_id);

  glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, this->_normals);
  glNormalPointer(GL_FLOAT, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, this->_textures);
  glTexCoordPointer(2, GL_FLOAT, 0, 0);

  glColor3f(1.0, 1.0, 1.0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);
  glDrawElements(GL_TRIANGLES, this->ibo.size(), GL_UNSIGNED_INT, 0);

  glBindTexture(GL_TEXTURE_2D, 0);
}

std::vector<Vertex> Model::getPoints() { return this->_points; }
