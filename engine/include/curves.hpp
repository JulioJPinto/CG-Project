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

  void applyRotation(float elapsed_time);
};

class Translations {
 public:
  float time;
  bool align;
  std::vector<Point> curvePoints;
  Point y_axis;

  Translations();
  Translations(float time, bool align, std::vector<Point> curve);

  void applyTranslations(float elapsed_time);

  void renderCatmullRomCurve();

  std::pair<Point, Point> getLocation(float elapsed_time);

  std::array<float, 16> rotationMatrix(Point x, Point y, Point z);
};

#endif  // CURVES_HPP