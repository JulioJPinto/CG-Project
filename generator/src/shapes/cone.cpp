#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

std::vector<Point> coneTriangles(float radius, float height, int slices, int stacks) {
    std::vector<Point> points;

    // Generate points for each stack
    for (int i = 0; i < stacks; ++i) {
        float y1 = height * i / stacks;
        float y2 = height * (i + 1) / stacks;

        for (int j = 0; j < slices; ++j) {
            float theta1 = 2.0f * M_PI * j / slices;
            float theta2 = 2.0f * M_PI * (j + 1) / slices;

            float x1 = radius * std::cos(theta1);
            float z1 = radius * std::sin(theta1);

            float x2 = radius * std::cos(theta2);
            float z2 = radius * std::sin(theta2);

            // Side triangles
            points.emplace_back(x1, y1, z1);
            points.emplace_back(x2, y1, z2);
            points.emplace_back(0.0f, y2, 0.0f);

            // Bottom triangles
            if (i == 0) {
                points.emplace_back(0.0f, 0.0f, 0.0f);
                points.emplace_back(x2, y1, z2);
                points.emplace_back(x1, y1, z1);
            }
        }
    }

    // Cone tip
    points.emplace_back(0.0f, height, 0.0f);

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
