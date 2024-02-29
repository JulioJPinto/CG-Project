#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

std::vector<Point> coneTriangles(float radius, float height, int slices, int stacks) {
    std::vector<Point> points;
    float alfa = 2.0f * M_PI / slices;
    float yT = height / 2.0f;
    float yB = -height / 2.0f;
	float lastX = radius * cos(0);
	float lastZ = radius * sin(0);
    
    for (int i = 1; i <= slices; ++i) {
            float a = i * alfa;
            float x = radius * cos(a);
            float z = radius * sin(a);


            // Side triangles
            points.emplace_back(0, height, 0);
            points.emplace_back(x, 0, z);
            points.emplace_back(lastX, 0, lastZ);

            // Bottom triangles
            points.emplace_back(lastX, 0, lastZ);
            points.emplace_back(x, 0, z);
            points.emplace_back(0, 0, 0);

            lastX = x;
            lastZ = z;
        }

    return points;
}

bool generateCone(float radius, float height, int slices, int stacks, const char* filepath) {
    std::vector<Point> triangles = coneTriangles(radius, height, slices, stacks);

    if (triangles.empty()) {
        std::cerr << "Error: Empty vector of triangles.\n";
        return false;
    }

    saveToFile(triangles, filepath);

    return true;
}
