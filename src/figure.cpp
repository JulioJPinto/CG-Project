#include "figure.hpp"

#include <fstream>

Figure::Figure() { points = std::vector<Point>(); }

void Figure::exportFile(std::string filename) {
  std::ofstream file(filename);
  file << "Test\n";
  file.close();
}