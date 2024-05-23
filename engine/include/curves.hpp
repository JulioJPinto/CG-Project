#ifndef CURVES_HPP
#define CURVES_HPP

#include <array>  // Include for std::array
#include <string>
#include <vector>

#include "model.hpp"
#include "utils.hpp"


enum Transformations {TIMEROTATION, TIMETRANSLATE, STATIC};


class TimeRotations {
 public:
  float time;
  float x;
  float y;
  float z;

  TimeRotations();
  TimeRotations(float time, float x, float y, float z);

  void applyTimeRotation(float elapsed_time);
};

class TimeTranslations {
 public:
  float time;
  bool align;
  std::vector<Point> curvePoints;
  Point y_axis;

  TimeTranslations();
  TimeTranslations(float time, bool align, std::vector<Point> curve);

  void applyTimeTranslations(float elapsed_time);

  void renderCatmullRomCurve();

  std::pair<Point, Point> getLocation(float elapsed_time);

  std::array<float, 16> rotationMatrix(Point x, Point y, Point z);
};


  glm::mat4 Scalematrix(float x, float y, float z);
  glm::mat4 Rotationmatrix(float angle, float x, float y, float z);
  glm::mat4 Translatematrix(float x, float y, float z);


#endif  // CURVES_HPP