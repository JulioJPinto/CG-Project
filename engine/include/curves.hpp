#ifndef CURVES_HPP
#define CURVES_HPP

#include <array>  // Include for std::array
#include <string>
#include <vector>

#include "model.hpp"
#include "utils.hpp"

enum TimeTransform { ROTATION, TRANSLATE };

class Rotations {
 public:
  float time;
  float x;
  float y;
  float z;

  Rotations();
  Rotations(float time, float x, float y, float z);

  void ApplyRotation(float elapsed);
};

class Translates {
 public:
  float time;
  bool align;
  std::vector<Point> curvePoints;
  Point y_axis;

  Translates();
  Translates(float time, bool align, std::vector<Point> curve);

  void ApplyTranslate(float elapsed);

  void renderCatmullRomCurve();

  std::pair<Point, Point> getLocation(float elapsed);

  std::array<float, 16> rotationMatrix(Point x, Point y, Point z);
};

#endif  // CURVES_HPP