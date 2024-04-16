#ifndef PATCHES_HPP
#define PATCHES_HPP

#include <string>

#include "../../common/include/utils.hpp"

std::vector<Point> patchTriangles(const char* bezier_patch, const int tessellation);

bool generatePatch(const char* bezier_patch, const int tessellation, const char* fileName);

float bernstein(int i, float t);

Point bezierPatch(const std::vector<Point>& controlPoints, float u, float v);

#endif  // PATCHES_HPP