#ifndef SAVE3D_HPP
#define SAVE3D_HPP

#include <fstream>
#include <vector>

#include "utils.hpp"

void save3Dfile(const std::vector<Point>& points,
                const std::vector<Point>& normals,
                const std::vector<Point2D>& textures, const char* filepath);

#endif  // SAVE3D_HPP