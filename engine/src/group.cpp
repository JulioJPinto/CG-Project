#include "group.hpp"

#include <math.h>

#include <cstring>  // for memcpy
#include <iostream>
#include <string>

Group::Group() {
  this->models = std::vector<std::string>();
  this->subgroups = std::vector<Group>();
}

Group::Group(std::vector<std::string> models, std::vector<Group> subgroups,
             double arr[4][4]) {
  this->models = models;
  this->subgroups = subgroups;
  memcpy(this->arr, arr, sizeof(this->arr));
}

void Group::translate(double x, double y, double z) {
  double translationMatrix[4][4] = {
      {1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}};

  double result[4][4] = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result[i][j] += this->arr[i][k] * translationMatrix[k][j];
      }
    }
  }

  memcpy(this->arr, result, sizeof(this->arr));
}

void Group::scale(double x, double y, double z) {
  double scaleMatrix[4][4] = {
      {x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}};

  double result[4][4] = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result[i][j] += this->arr[i][k] * scaleMatrix[k][j];
      }
    }
  }

  memcpy(this->arr, result, sizeof(this->arr));
}

void Group::rotate(double angle, double x, double y, double z) {
  float rad = angle * M_PI / 180;
  double rotateMatrix[4][4] = {
      {x * x + (1 - x * x) * cos(rad), x * y * (1 - cos(rad)) - z * sin(rad),
       x * z * (1 - cos(rad)) + y * sin(rad), 0},
      {y * x * (1 - cos(rad)) + z * sin(rad), y * y + (1 - y * y) * cos(rad),
       y * z * (1 - cos(rad)) - x * sin(rad), 0},
      {x * z * (1 - cos(rad)) - y * sin(rad),
       y * z * (1 - cos(rad)) + x * sin(rad), z * z + (1 - z * z) * cos(rad),
       0},
      {0, 0, 0, 1}};

  double result[4][4] = {
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result[i][j] += this->arr[i][k] * rotateMatrix[k][j];
      }
    }
  }

  memcpy(this->arr, result, sizeof(this->arr));
}
