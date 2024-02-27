#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <vector>

float planeWidth = 5.0f;
float planeLength = 5.0f;
int divisions = 3;

std::vector<Point> calculateTriangles(float length, int divisions) {
    float half = length / 2.0f;
    float steps = length / divisions;

    std::vector<Point> points;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {

            float x1 = -half + i * steps;
            float y1 = 0.0f; // Adjusted for consistency with the Point constructor
            float z1 = -half + j * steps;
            float x2 = -half + (i + 1) * steps;
            float y2 = 0.0f; // Adjusted for consistency with the Point constructor
            float z2 = -half + (j + 1) * steps;

            Point p1(x1, y1, z1); // Corrected the constructor usage
            Point p2(x2, y1, z1);
            Point p3(x1, y1, z2);
            Point p4(x2, y1, z2);

            points.push_back(p1);
            points.push_back(p2);
            points.push_back(p3);

            points.push_back(p2);
            points.push_back(p4);
            points.push_back(p3);
        }
    }

    return points;
}

void saveToFile(const std::vector<Point>& points, const char* filepath) { // Changed parameter type to const char*
    std::ofstream file(filepath);

    if (file.is_open()) {
        for (const auto& point : points) {
            file << point.x << " " << point.y << " " << point.z << "\n";
        }
        file.close();
        std::cout << "File saved successfully.\n";
    } else {
        std::cerr << "Unable to open file: " << filepath << std::endl;
    }
}

bool generatePlane(float length, int divisions, const char* filepath) { // Changed parameter type to const char*
    std::vector<Point> triangles = calculateTriangles(length, divisions);

    if (triangles.empty()) {
        std::cerr << "Error: Empty vector of triangles.\n";
        return false;
    }

    saveToFile(triangles, filepath);

    return true;
}