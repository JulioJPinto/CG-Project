#include "save3d.hpp"

void save3DAdvancedfile(const std::vector<Point>& points,
                        const std::vector<Point>& normals,
                        const std::vector<Point2D>& textures,
                        const char* filepath) {
  std::ofstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return;
  }

  file << "# " << points.size() << std::endl;

  for (size_t i = 0; i < points.size(); i++) {
    file << "p " << points[i].x << " " << points[i].y << " " << points[i].z
         << std::endl;
  }

  for (size_t i = 0; i < normals.size(); i++) {
    file << "n " << normals[i].x << " " << normals[i].y << " " << normals[i].z
         << std::endl;
  }

  for (size_t i = 0; i < textures.size(); i++) {
    file << "t " << textures[i].x << " " << textures[i].y << std::endl;
  }

  file.close();
}