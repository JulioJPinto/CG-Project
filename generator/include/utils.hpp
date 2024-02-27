#ifndef SOLAR_SYSTEM_UTILS_HPP
#define SOLAR_SYSTEM_UTILS_HPP

#include <string>
#include <sstream>

// Define Point struct
typedef struct Point {
    float x;
    float y;
    float z;

    // Constructor
    Point(float x_val = 0.0f, float y_val = 0.0f, float z_val = 0.0f)
            : x(x_val), y(y_val), z(z_val) {}
} Point;

// Function to convert Point to string
std::string pointToString(const Point& point);

#endif //SOLAR_SYSTEM_UTILS_HPP
