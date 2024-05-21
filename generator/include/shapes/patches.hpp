#ifndef PATCHES_HPP
#define PATCHES_HPP

#include <string>

#include "utils.hpp"

std::pair<std::pair<std::vector<Point>, std::vector<Point>>,
          std::vector<Point2D>>
patchTriangles(const char* bezier_patch, const int tessellation);

bool generatePatch(const char* bezier_patch, const int tessellation,
                   const char* fileName, bool advanced);

float bernstein(int i, float t);

Point bezierPatch(const std::vector<Point>& controlPoints, float u, float v);

float bernsteinDerivative(int i, float t);

Point calculateNormal(const Point& p1, const Point& p2, const Point& p3);

#endif  // PATCHES_HPP