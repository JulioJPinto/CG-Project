#ifndef DRAW_HPP
#define DRAW_HPP

#include <math.h>

#include <vector>

#include "../../common/include/utils.hpp"
#include "draw.hpp"
#include "parse.hpp"

void drawTriangles(const std::vector<Point>& points, Group group);

void drawGroup(Group group);

#endif  // DRAW_HPP
