#include <iostream>
#include <string>

#include "../include/shapes/cube.hpp"
#include "../include/shapes/plane.hpp"
#include "../include/shapes/cone.hpp"


void generateFigure(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Insufficient arguments\n";
    return;
  }

  char* figureType = argv[argc - 1];
  std::string figureName = argv[1];

  if (figureName == "sphere" && argc == 6) {
    // Generate Sphere
    std::cout << "Generating Sphere\n";
  } else if (figureName == "box" && argc == 5) {
    // Generate Box
    std::cout << "Generating Box\n";
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);

    generateCube(length, divisions, figureType);
  } else if (figureName == "plane" && argc == 5) {
    // Generate Plane
    std::cout << "Generating Plane\n";  // Added newline here
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);

    generatePlane(length, divisions,
                  figureType);  // Assuming saveToFile is available
  } else if (figureName == "cone" && argc == 7) {
    // Generate Cone
    std::cout << "Generating Cone\n";
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);
    int stacks = std::stoi(argv[5]);

    generateCone(radius,height,slices,stacks, figureType);

  } else {
    std::cerr << "Invalid arguments\n";
  }
}

int main(int argc, char* argv[]) {
  generateFigure(argc, argv);
  return 0;
}
