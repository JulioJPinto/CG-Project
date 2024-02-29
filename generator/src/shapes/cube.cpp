#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <vector>

std::vector<Point> cubeTriangles(float length, int divisions) {

    float halfSize = length / 2.0f; 
    float step = length / divisions;  

    std::vector<Point> points;

    // Front face
    for(int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            float x1 = -halfSize + i * step;
            float y1 = -halfSize + j * step;
            float x2 = x1 + step;
            float y2 = y1 + step;

            points.push_back(Point(x1, y1, halfSize));
            points.push_back(Point(x2, y1, halfSize));
            points.push_back(Point(x1, y2, halfSize));

            points.push_back(Point(x1, y2, halfSize));
            points.push_back(Point(x2, y1, halfSize));
            points.push_back(Point(x2, y2, halfSize));
        }
    }

    // Back face
    for(int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            float x1 = -halfSize + i * step;
            float y1 = -halfSize + j * step;
            float x2 = x1 + step;
            float y2 = y1 + step;

            points.push_back(Point(x1, y1, -halfSize));
            points.push_back(Point(x1, y2, -halfSize));
            points.push_back(Point(x2, y1, -halfSize));

            points.push_back(Point(x1, y2, -halfSize));
            points.push_back(Point(x2, y2, -halfSize));
            points.push_back(Point(x2, y1, -halfSize));
        }
    }

    // Left face
    for(int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            float y1 = -halfSize + i * step;
            float z1 = -halfSize + j * step;
            float y2 = y1 + step;
            float z2 = z1 + step;

            points.push_back(Point(-halfSize, y1, z1));
            points.push_back(Point(-halfSize, y1, z2));
            points.push_back(Point(-halfSize, y2, z1));

            points.push_back(Point(-halfSize, y1, z2));
            points.push_back(Point(-halfSize, y2, z2));
            points.push_back(Point(-halfSize, y2, z1));
        }
    }

    // Right face
    for(int j = 0; j < divisions; ++j) {
        for(int i = 0; i < divisions; ++i) {
            float y1 = -halfSize + j * step;
            float z1 = -halfSize + i * step;
            float y2 = y1 + step;
            float z2 = z1 + step;

            points.push_back(Point(halfSize, y1, z1));
            points.push_back(Point(halfSize, y2, z1));
            points.push_back(Point(halfSize, y1, z2));

            points.push_back(Point(halfSize, y1, z2));
            points.push_back(Point(halfSize, y2, z1));
            points.push_back(Point(halfSize, y2, z2));
        }
    }

    // Top face
    for(int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            float x1 = -halfSize + i * step;
            float z1 = -halfSize + j * step;
            float x2 = x1 + step;
            float z2 = z1 + step;

            points.push_back(Point(x1, halfSize, z1));
            points.push_back(Point(x1, halfSize, z2));
            points.push_back(Point(x2, halfSize, z1));

            points.push_back(Point(x1, halfSize, z2));
            points.push_back(Point(x2, halfSize, z2));
            points.push_back(Point(x2, halfSize, z1));
        }
    }

    // Bottom face
    for(int i = 0; i < divisions; ++i) {
        for(int j = 0; j < divisions; ++j) {
            float x1 = -halfSize + i * step;
            float z1 = -halfSize + j * step;
            float x2 = x1 + step;
            float z2 = z1 + step;

            points.push_back(Point(x1, -halfSize, z1));
            points.push_back(Point(x2, -halfSize, z1));
            points.push_back(Point(x1, -halfSize, z2));

            points.push_back(Point(x1, -halfSize, z2));
            points.push_back(Point(x2, -halfSize, z1));
            points.push_back(Point(x2, -halfSize, z2));
        }
    }

    return points;
}

bool generateCube(float length, int divisions, const char* filepath) {
    std::vector<Point> triangles = cubeTriangles(length, divisions);

    if (triangles.empty()) {
        std::cerr << "Error: Empty vector of triangles.\n";
        return false;
    }

    saveToFile(triangles, filepath);

    return true;
}
