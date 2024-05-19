#include "read.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "model.hpp"

std::unordered_map<std::string, Model> hash_models;

Model readOBJfile(const char* filepath) {
  std::vector<Point> points;
  std::vector<Point> normals;
  std::vector<Point2D> textures;
  std::vector<Vertex> vertices;
  std::ifstream file(filepath);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filepath << std::endl;
    return Model();  // Return an empty model or handle the error as appropriate
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if (type == "v") {
      Point point;
      iss >> point.x >> point.y >> point.z;
      points.push_back(point);
    } else if (type == "vn") {
      Point normal;
      iss >> normal.x >> normal.y >> normal.z;
      normals.push_back(normal);
    } else if (type == "vt") {
      Point2D texture;
      iss >> texture.x >> texture.y;
      textures.push_back(texture);
    } else if (type == "f") {
      std::string vertex;

      while (iss >> vertex) {
        std::istringstream index_stream(vertex);
        std::string index_str;
        std::vector<int> indices;
        while (std::getline(index_stream, index_str, '/')) {
          if (!index_str.empty())
            indices.push_back(std::stoi(index_str) - 1);
          else
            indices.push_back(-1);  // If texture or normal index is missing
        }
        int point_index = indices[0];
        int texture_index = indices[1];
        int normal_index = indices[2];
        float x, y, z, nx, ny, nz, tx, ty;
        x = points[point_index].x;
        y = points[point_index].y;
        z = points[point_index].z;
        nx = normals[normal_index].x;
        ny = normals[normal_index].y;
        nz = normals[normal_index].z;
        tx = 0;
        ty = 1;

        if (texture_index == -1) {
          printf("Texture index is -1\n");
        }
        if (normal_index == -1) {
          printf("Normal index is -1\n");
        }
        if (texture_index > textures.size()) {
          printf("Texture index is out of bounds\n");
        }
        if (normal_index > normals.size()) {
          printf("Normal index is out of bounds\n");
        }

        vertices.push_back(Vertex(x, y, z, nx, ny, nz, tx, ty));
      }
    }
  }
  printf("texturas: %d\n", textures.size());
  printf("normais: %d\n", normals.size());
  printf("pontos: %d\n", points.size());
  printf("vertices: %d\n", vertices.size());
  printf("tex.x: %f\n", textures[70725].x);
  printf("tex.x: %f\n", textures[0].x);
  file.close();

  Model model(filepath, vertices);

  // Assuming hash_models is a global or member variable
  hash_models[filepath] = model;

  return model;
}

Model read3DAdvancedFile(const char* filepath) {
  std::ifstream file(filepath);

  std::vector<Vertex> points;

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    char type;
    float x, y, z, nx, ny, nz, tx, ty;
    if (iss >> type >> x >> y >> z >> nx >> ny >> nz >> tx >> ty) {
      points.push_back(Vertex(x, y, z, nx, ny, nz, tx, ty));
    }
  }

  Model model(filepath, points);
  hash_models[filepath] = model;

  return model;
}

Model read3DSimpleFile(const char* filepath) {
  std::ifstream file(filepath);

  std::vector<Vertex> points;

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    char type;
    float x, y, z, nx, ny, nz, tx, ty;
    if (iss >> type >> x >> y >> z) {
      points.push_back(Vertex(Point(x, y, z)));
    }
  }

  Model model(filepath, points);
  hash_models[filepath] = model;

  return model;
}

Model read3DFile(const char* filepath) {
  std::ifstream file(filepath);

  char type;
  if (file >> type) {
    if (type == '#') {
      return read3DAdvancedFile(filepath);
    } else {
      return read3DSimpleFile(filepath);
    }
  }

  return Model();
}

Model readFile(const char* filepath) {
  std::ifstream file(filepath);

  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return Model();
  }

  if (hash_models.find(filepath) != hash_models.end()) {
    std::cout << filepath << " already read." << std::endl;
    return hash_models[filepath];
  }

  if (std::filesystem::path(filepath).extension() == ".3d") {
    return read3DFile(filepath);
  } else if (std::filesystem::path(filepath).extension() == ".obj") {
    return readOBJfile(filepath);
  }

  return Model();
}
