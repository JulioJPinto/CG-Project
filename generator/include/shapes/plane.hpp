#ifndef SOLAR_SYSTEM_PLANE_HPP
#define SOLAR_SYSTEM_PLANE_HPP


#include <vector>
#include <string>
#include "../utils.hpp"

std::vector<Point> calculateTriangles(float length, int divisions);

void saveToFile(const std::vector<Point>& points, const std::string& filepath);

bool generatePlane(float length, int divisions, const char* filepath);



#endif //SOLAR_SYSTEM_PLANE_HPP
