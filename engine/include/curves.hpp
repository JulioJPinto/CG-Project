#ifndef CURVES_HPP
#define CURVES_HPP

#include <array>  // Include for std::array
#include <string>
#include <vector>

#include "model.hpp"
#include "utils.hpp"


enum Transformations { SCALE, ROTATION, TRANSLATE, TIMEROTATION, TIMETRANSLATE };


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

class Scale {
 public:
  float x;
  float y;
  float z;

  Scale();
  Scale(float x, float y, float z);

  void applyScale();
};

class Translate {
 public:
  float x;
  float y;
  float z;

  Translate();
  Translate(float x, float y, float z);

  void applyTranslation();
};

class Rotation {
 public:
  float angle;
  float x;
  float y;
  float z;

  Rotation();
  Rotation(float angle, float x, float y, float z);

  void applyRotation();
};

  glm::mat4 Scalematrix(float x, float y, float z);
  glm::mat4 Rotationmatrix(float angle, float x, float y, float z);
  glm::mat4 Translatematrix(float x, float y, float z);


#endif  // CURVES_HPP