#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <vector>

#include "../../common/include/utils.hpp"

class Group {
 public:
  std::vector<std::string> models;
  std::vector<Group> subgroups;
  std::vector<Point> points;
  double arr[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

  Group();
  Group(std::vector<std::string> models, std::vector<Group> subgroups, std::vector<Point> points,
        double arr[4][4]);

  void translate(double x, double y, double z);

  void scale(double x, double y, double z);

  void rotate(double angle, double x, double y, double z);
  // std::string toString();
};

#endif  // GROUP_HPP
