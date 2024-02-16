#include <string.h>
#include <iostream>
#include "figure.hpp"
#include "figure_generator.hpp" // Include the figure_generator header

inline std::unique_ptr<Figure> generateFigure(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Insufficient arguments\n";
    return nullptr;
  }

  std::string figureType = argv[argc - 1];
  std::string figureName = argv[1];

  if (figureName == "sphere" && figureType == "sphere.3d" && argc == 6) {
    // Generate Sphere
    std::cout << "Generating Sphere\n";
    return nullptr;
  } else if (figureName == "box" && figureType == "box.3d" && argc == 5) {
    // Generate Box
    std::cout << "Generating Box\n";
    return nullptr;
  } else if (figureName == "plane" && figureType == "plane.3d" && argc == 5) {
    // Generate Plane
    std::cout << "Generating Plane\n"; // Added newline here
    float length = std::stof(argv[2]);
    int divisions = std::stoi(argv[3]);
    // generatePlane(length, divisions);
    return nullptr;
  } else if (figureName == "cone" && figureType == "cone.3d" && argc == 7) {
    // Generate Cone
    std::cout << "Generating Cone\n";
    return nullptr;
  } else {
    std::cerr << "Invalid arguments\n";
    return nullptr;
  }
}

int main(int argc, char* argv[]) {
  std::unique_ptr<Figure> figure = generateFigure(argc, argv);
  return 0;
}
