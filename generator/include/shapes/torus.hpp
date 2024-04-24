#ifndef SOLAR_SYSTEM_TORUS_HPP
#define SOLAR_SYSTEM_TORUS_HPP

#include <string>
#include <vector>

#include "utils.hpp"

bool generateTorus(float majorRadius, float minorRadius, int sides, int rings,
                   const char* filepath);

#endif  // SOLAR_SYSTEM_TORUS_HPP