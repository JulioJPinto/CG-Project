#include "utils.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

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
