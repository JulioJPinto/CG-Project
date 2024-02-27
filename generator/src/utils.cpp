#include "utils.hpp"
#include <string>
#include <sstream>

std::string pointToString(Point point) {
    std::ostringstream oss;
    oss << point.x << " " << point.y << " " << point.z << "\n";
    return oss.str();
}
