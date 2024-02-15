#pragma once
#include <memory>
#include "figure.hpp"

std::unique_ptr<Figure> generatePlane(float length, int divisions);
std::unique_ptr<Figure> generateBox(float dimension, int divisions);
std::unique_ptr<Figure> generateSphere(float radius, int slices, int stacks);
std::unique_ptr<Figure> generateCone(float radius, float height, int slices, int stacks);
