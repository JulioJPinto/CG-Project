#include <iostream>
#include <string>
#include "../include/shapes/plane.hpp"

void generateFigure(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Insufficient arguments\n";
        return;
    }

    std::string figureType = argv[argc - 1];
    std::string figureName = argv[1];

    if (figureName == "sphere" && figureType == "sphere.3d" && argc == 6) {
        // Generate Sphere
        std::cout << "Generating Sphere\n";
    } else if (figureName == "box" && figureType == "box.3d" && argc == 5) {
        // Generate Box
        std::cout << "Generating Box\n";
    } else if (figureName == "plane" && figureType == "plane.3d" && argc == 5) {
        // Generate Plane
        std::cout << "Generating Plane\n";  // Added newline here
        float length = std::stof(argv[2]);
        int divisions = std::stoi(argv[3]);

        generatePlane(length, divisions, argv[4]); // Assuming saveToFile is available
    } else if (figureName == "cone" && figureType == "cone.3d" && argc == 7) {
        // Generate Cone
        std::cout << "Generating Cone\n";
    } else {
        std::cerr << "Invalid arguments\n";
    }
}

int main(int argc, char* argv[]) {
    generateFigure(argc, argv);
    return 0;
}
