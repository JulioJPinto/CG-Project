#include "group.hpp"
#include <cmath> // for M_PI
#include <cstring> // for memcpy
#include <iostream>
#include <string>
#include <array>

#include "../../common/include/utils.hpp"

Group::Group() {
  this->models = std::vector<std::string>();
  this->subgroups = std::vector<Group>();
  this->points = std::vector<Point>();
}

Group::Group(std::vector<std::string> models, std::vector<Group> subgroups,
             std::vector<Point> points, std::array<std::array<double, 4>, 4> arr) {
  this->models = models;
  this->subgroups = subgroups;
  this->points = points;
  this->arr = arr;
}

void Group::translate(double x, double y, double z) {
  std::array<std::array<double, 4>, 4> translationMatrix = {{
      {1, 0, 0, x}, 
      {0, 1, 0, y}, 
      {0, 0, 1, z}, 
      {0, 0, 0, 1}
  }};

  std::array<std::array<double, 4>, 4> result = {{
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}
  }};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result[i][j] += this->arr[i][k] * translationMatrix[k][j];
      }
    }
  }

  this->arr = result;
}

void Group::scale(double x, double y, double z) {
  std::array<std::array<double, 4>, 4> scaleMatrix = {{
      {x, 0, 0, 0}, 
      {0, y, 0, 0}, 
      {0, 0, z, 0}, 
      {0, 0, 0, 1}
  }};

  std::array<std::array<double, 4>, 4> result = {{
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}
  }};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result[i][j] += this->arr[i][k] * scaleMatrix[k][j];
      }
    }
  }

  this->arr = result;
}

void Group::rotate(double angle, double x, double y, double z) {
  float rad = angle * M_PI / 180;
  std::array<std::array<double, 4>, 4> rotateMatrix = {{
      {x * x + (1 - x * x) * cos(rad), x * y * (1 - cos(rad)) - z * sin(rad),
       x * z * (1 - cos(rad)) + y * sin(rad), 0},
      {y * x * (1 - cos(rad)) + z * sin(rad), y * y + (1 - y * y) * cos(rad),
       y * z * (1 - cos(rad)) - x * sin(rad), 0},
      {x * z * (1 - cos(rad)) - y * sin(rad),
       y * z * (1 - cos(rad)) + x * sin(rad), z * z + (1 - z * z) * cos(rad),
       0},
      {0, 0, 0, 1}
  }};

  std::array<std::array<double, 4>, 4> result = {{
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}, 
      {0, 0, 0, 0}
  }};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result[i][j] += this->arr[i][k] * rotateMatrix[k][j];
      }
    }
  }

  this->arr = result;
}
