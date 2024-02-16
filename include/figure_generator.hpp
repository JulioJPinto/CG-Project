#pragma once
#include <memory>

#include "figure.hpp"

/**
 * @brief Generates a plane
 * 
 * @param length the length of the plane
 * @param divisions the number of divisions
 * 
 * @return the generated plane
*/
std::unique_ptr<Figure> generatePlane(float length, int divisions);

/**
 * @brief Generates a box
 * 
 * @param dimension the dimension of the box
 * @param divisions the number of divisions
 * 
 * @return the generated box
*/
std::unique_ptr<Figure> generateBox(float dimension, int divisions);

/**
 * @brief Generates a sphere
 * 
 * @param radius the radius of the sphere
 * @param slices the number of slices
 * @param stacks the number of stacks
 * 
 * @return the generated sphere
*/
std::unique_ptr<Figure> generateSphere(float radius, int slices, int stacks);

/**
 * @brief Generates a cone
 * 
 * @param radius the radius of the cone
 * @param height the height of the cone
 * @param slices the number of slices
 * @param stacks the number of stacks
 * 
 * @return the generated cone
*/
std::unique_ptr<Figure> generateCone(float radius, float height, int slices,
                                     int stacks);
