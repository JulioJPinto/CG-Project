#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define DIR "../models/"

void saveToFile(
    const std::vector<Point>& points,
    const char* filepath) {  // Changed parameter type to const char*
  
  std::string buf(DIR);
  buf.append(filepath);

  std::ofstream file(buf);

  if (file.is_open()) {
    for (const auto& point : points) {
      file << point.x << " " << point.y << " " << point.z << "\n";
    }
    file.close();
    std::cout << "File saved successfully.\n";
  } else {
    std::cerr << "Unable to open file: " << filepath << std::endl;
  }
}
