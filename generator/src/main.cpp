#include <iostream>
#include <string>

#include "shapes/cone.hpp"
#include "shapes/cube.hpp"
#include "shapes/cylinder.hpp"
#include "shapes/patches.hpp"
#include "shapes/plane.hpp"
#include "shapes/sphere.hpp"
#include "shapes/torus.hpp"

void generateFigure(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Insufficient arguments\n";
    return;
  }

  bool advanced = true;
  int figureArgs = argc;
  char* fileName;
  if (argv[argc - 1][1] == 's') {
    fileName = argv[argc - 2];
    advanced = false;
    figureArgs -= 1;
  } else {
    fileName = argv[argc - 1];
  }

  std::string figureName = argv[1];

  if (figureName == "sphere" && figureArgs == 6) {
    // Generate Sphere
    std::cout << "Generating Sphere\n";
    float radius = std::stof(argv[2]);
    int slices = std::stoi(argv[3]);
    int stacks = std::stoi(argv[4]);

    generateSphere(radius, slices, stacks, fileName, advanced);
  } else if (figureName == "box" && figureArgs == 5) {
    // Generate Box
    std::cout << "Generating Box\n";
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);

    generateCube(length, divisions, fileName, advanced);
  } else if (figureName == "plane" && figureArgs == 5) {
    // Generate Plane
    std::cout << "Generating Plane\n";  // Added newline here
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);

    generatePlane(length, divisions, fileName,
                  advanced);  // Assuming saveToFile is available
  } else if (figureName == "cone" && figureArgs == 7) {
    // Generate Cone
    std::cout << "Generating Cone\n";
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);
    int stacks = std::stoi(argv[5]);

    generateCone(radius, height, slices, stacks, fileName);

  } else if (figureName == "torus" && figureArgs == 7) {
    // Generate Torus
    std::cout << "Generating Torus\n";
    float innerRadius = std::stof(argv[2]);
    float outerRadius = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);
    int stacks = std::stoi(argv[5]);

    generateTorus(innerRadius, outerRadius, slices, stacks, fileName, advanced);
  } else if (figureName == "cylinder" && figureArgs == 6) {
    // Generate Cylinder
    std::cout << "Generating Cylinder\n";
    float radius = std::stof(argv[2]);
    float height = std::stof(argv[3]);
    int slices = std::stoi(argv[4]);

    generateCylinder(radius, height, slices, fileName);
  } else if (figureName == "patch" && figureArgs == 5) {
    // Generate Patch
    std::cout << "Generating Patch\n";
    char* bezier_patch = argv[2];
    int tessellation = std::stoi(argv[3]);
    std::cout << "Tessellation: " << tessellation << std::endl;
    std::cout << "Bezier patch: " << bezier_patch << std::endl;
    generatePatch(bezier_patch, tessellation, fileName);

  } else {
    std::cerr << "Invalid arguments\n";
  }
}

int main(int argc, char* argv[]) {
  generateFigure(argc, argv);
  return 0;
}
