#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <vector>
#include <array> // Include for std::array

#include "../../common/include/utils.hpp"

class Group {
 public:
  std::vector<std::string> models;
  std::vector<Group> subgroups;
  std::vector<Point> points;
  std::array<std::array<double, 4>, 4> arr = 
  {{
    {1, 0, 0, 0}, 
    {0, 1, 0, 0}, 
    {0, 0, 1, 0}, 
    {0, 0, 0, 1}
  }};

  Group();
  Group(std::vector<std::string> models, std::vector<Group> subgroups,
        std::vector<Point> points, std::array<std::array<double, 4>, 4> arr); // Updated constructor

  void translate(double x, double y, double z);

  void scale(double x, double y, double z);

  void rotate(double angle, double x, double y, double z);
  // std::string toString();
};

#endif  // GROUP_HPP
