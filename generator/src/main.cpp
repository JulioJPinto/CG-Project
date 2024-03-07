#include <iostream>
#include <string>

#include "../include/shapes/cone.hpp"
#include "../include/shapes/cube.hpp"
#include "../include/shapes/cylinder.hpp"
#include "../include/shapes/plane.hpp"
#include "../include/shapes/sphere.hpp"
#include "../include/shapes/torus.hpp"

void generateFigure(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Insufficient arguments\n";
    return;
  }

  char* fileName = argv[argc - 1];
  std::string figureName = argv[1];

  if (figureName == "sphere" && argc == 6) {
    // Generate Sphere
    std::cout << "Generating Sphere\n";
    float radius = std::stof(argv[2]);
    int slices = std::stoi(argv[3]);
    int stacks = std::stoi(argv[4]);

    generateSphere(radius, slices, stacks, fileName);
  } else if (figureName == "box" && argc == 5) {
    // Generate Box
    std::cout << "Generating Box\n";
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);

    generateCube(length, divisions, fileName);
  } else if (figureName == "plane" && argc == 5) {
    // Generate Plane
    std::cout << "Generating Plane\n";  // Added newline here
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);

    generatePlane(length, divisions,
                  fileName);  // Assuming saveToFile is available
  } else if (figureName == "cone" && argc == 7) {
    // Generate Cone
    std::cout << "Generating Cone\n";
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);
    int stacks = std::stoi(argv[5]);

    generateCone(radius, height, slices, stacks, fileName);

  } else if (figureName == "torus" && argc == 7) {
    // Generate Torus
    std::cout << "Generating Torus\n";
    float innerRadius = std::stof(argv[2]);
    float outerRadius = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);
    int stacks = std::stoi(argv[5]);

    generateTorus(innerRadius, outerRadius, slices, stacks, fileName);
  } else if (figureName == "cylinder" && argc == 6) {
    // Generate Cylinder
    std::cout << "Generating Cylinder\n";
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);

    generateCylinder(radius, height, slices, fileName);
  } else {
    std::cerr << "Invalid arguments\n";
  }
}

int main(int argc, char* argv[]) {
  generateFigure(argc, argv);
  return 0;
}
