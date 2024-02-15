#include <string.h>

#include <iostream>

#include "../include/figure.hpp"
#include "../include/figure_generator.hpp"

inline std::unique_ptr<Figure> generateFigure(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Insufficient arguments\n";
    return 0;
  }

  std::string figureType = argv[argc - 1];

  if (figureType == "sphere.3d" && argc == 6) {
    // Generate Sphere
    std::cout << "Generating Sphere\n";
    return 0;
  } else if (figureType == "box.3d" && argc == 5) {
    // Generate Box
    std::cout << "Generating Box\n";
    return 0;
  } else if (figureType == "plane.3d" && argc == 5) {
    // Generate Plane
    std::cout << "Generating Plane\n";
    return 0;
  } else if (figureType == "cone.3d" && argc == 7) {
    // Generate Cone
    std::cout << "Generating Cone\n";
    return 0;
  } else {
    std::cerr << "Invalid arguments\n";
    return 0;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  std::unique_ptr<Figure> figure = generateFigure(argc, argv);

  return 0;
}