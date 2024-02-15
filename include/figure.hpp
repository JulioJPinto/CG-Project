#pragma once
#include <string>
#include <tuple>
#include <vector>

typedef std::vector<std::tuple<std::string, std::string>> Point;

class Figure {
 public:
  Figure();
  void exportFile(std::string filename);

 private:
  std::vector<Point> points;
};