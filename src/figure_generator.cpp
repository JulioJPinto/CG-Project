#include "figure_generator.hpp"
#include <iostream>

// This is a placeholder for the actual implementation of the functions

std::unique_ptr<Figure> generatePlane(float length, int divisions){
    std::cout << "Generating Plane\n";
    return std::make_unique<Figure>();
}

std::unique_ptr<Figure> generateBox(float dimension, int divisions){
    std::cout << "Generating Box\n";
    return std::make_unique<Figure>();
}

std::unique_ptr<Figure> generateSphere(float radius, int slices, int stacks){
    std::cout << "Generating Sphere\n";
    return std::make_unique<Figure>();
}

std::unique_ptr<Figure> generateCone(float radius, float height, int slices, int stacks){
    std::cout << "Generating Cone\n";
    return std::make_unique<Figure>();
}

