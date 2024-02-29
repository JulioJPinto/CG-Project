#ifndef CONE_HPP
#define CONE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "../utils.hpp"

bool generateCone(float radius, float height, int slices, int stacks, const char* filepath);

#endif //CONE_HPP