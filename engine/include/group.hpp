#ifndef GROUP_HPP
#define GROUP_HPP

#include <array>  // Include for std::array
#include <string>
#include <vector>

#include "curves.hpp"
#include "model.hpp"
#include "utils.hpp"

class Group {
 public:
  std::vector<Model> models;
  std::vector<Group> subgroups;
  std::vector<Point> points;
  std::array<std::array<float, 4>, 4> arr = {
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};

  Rotations rotations;
  Translates translates;

  Group();
  Group(std::vector<Model> models, std::vector<Group> subgroups,
        std::vector<Point> points, std::array<std::array<float, 4>, 4> arr,
        Rotations rotations,
        Translates translates);  // Updated constructor

  void translate(float x, float y, float z);

  void scale(float x, float y, float z);

  void rotate(float angle, float x, float y, float z);

  void drawGroup();
  // std::string toString();
};

#endif  // GROUP_HPP
