#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <vector>

#include "curves.hpp"
#include "utils.hpp"

static const std::array<std::array<float, 4>, 4> catmoll_rom_matrix{{
    {-0.5f, +1.5f, -1.5f, +0.5f},
    {+1.0f, -2.5f, +2.0f, -0.5f},
    {-0.5f, +0.0f, +0.5f, +0.0f},
    {+0.0f, +1.0f, +0.0f, +0.0f},
}};

std::pair<Point, Point> catmollRomPosition(std::vector<Point> curve,
                                           float global_time) {
  const std::array<std::array<float, 4>, 4> matrix = catmoll_rom_matrix;

  float t = global_time * curve.size();
  float segment = (int)floor(t);
  t -= segment;

  int first = segment + curve.size() - 1;
  Point p1 = curve[(first + 0) % curve.size()];
  Point p2 = curve[(first + 1) % curve.size()];
  Point p3 = curve[(first + 2) % curve.size()];
  Point p4 = curve[(first + 3) % curve.size()];

  const std::array<std::array<float, 4>, 3> p{{
      {p1.x, p2.x, p3.x, p4.x},
      {p1.y, p2.y, p3.y, p4.y},
      {p1.z, p2.z, p3.z, p4.z},
  }};

  const std::array<float, 4> timeP = {t * t * t, t * t, t,
                                      1};  // time matrix for point
  const std::array<float, 4> timeDP = {3 * t * t, 2 * t, 1,
                                       0};  // time matrix for derivate

  std::array<float, 3> pv{};  // Point
  std::array<float, 3> dv{};  // Derivative

  for (size_t i = 0; i < 3; ++i) {
    std::array<float, 4> a{};

    for (size_t j = 0; j < 4; ++j) {
      for (size_t k = 0; k < 4; ++k) {
        a[j] += p[i][k] * matrix[j][k];
      }
    }

    for (size_t j = 0; j < 4; j++) {
      pv[i] += timeP[j] * a[j];
      dv[i] += timeDP[j] * a[j];
    }
  }

  return {
      Point(pv[0], pv[1], pv[2]),
      Point(dv[0], dv[1], dv[2]),
  };
}

Rotations::Rotations() {
  this->time = 0;
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

Rotations::Rotations(float time, float x, float y, float z) {
  this->time = time;
  this->x = x;
  this->y = y;
  this->z = z;
}

void Rotations::applyRotation(float elapsed_time) {
  if (this->time == 0) {
    return;
  }
  float angle = 360 * (elapsed_time / this->time);
  glRotatef(angle, this->x, this->y, this->z);
}

Translations::Translations() {
  this->time = 0;
  this->align = false;
  this->y_axis = Point(0, 1, 0);
}

Translations::Translations(float time, bool align, std::vector<Point> curve) {
  this->time = time;
  this->align = align;
  this->curvePoints = curve;
  this->y_axis = Point(0, 1, 0);
}

std::pair<Point, Point> Translations::getLocation(float elapsed_time) {
  int point_count = this->curvePoints.size();
  float gt = elapsed_time / this->time;
  float t = gt * point_count;
  size_t index = std::floor(t);
  t = t - index;
  return catmollRomPosition(this->curvePoints, t);
}

std::array<float, 16> Translations::rotationMatrix(Point x, Point y, Point z) {
  return std::array<float, 16>{{
      x.x,
      x.y,
      x.z,
      0,
      y.x,
      y.y,
      y.z,
      0,
      z.x,
      z.y,
      z.z,
      0,
      0,
      0,
      0,
      1,
  }};
}

void Translations::applyTranslations(float elapsed_time) {
  if (this->time == 0) {
    return;
  }

  // this->renderCatmullRomCurve();

  float time = elapsed_time / this->time;

  std::pair<Point, Point> position_dir =
      catmollRomPosition(this->curvePoints, time);
  Point pos = position_dir.first;
  Point dir = position_dir.second;

  glTranslatef(pos.x, pos.y, pos.z);

  if (this->align) {
    Point x = dir.normalize();
    Point z = Point(x).cross(this->y_axis).normalize();
    Point y = Point(z).cross(x).normalize();
    glMultMatrixf(rotationMatrix(x, y, z).data());
  }
}

void Translations::renderCatmullRomCurve() {
  // draw curve using line segments with GL_LINE_LOOP
  float gt = 0.0;
  const float NUM_STEPS = 100;
  const float gt_step = this->time / NUM_STEPS;
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < NUM_STEPS; i++) {
    auto pos_deriv = this->getLocation(gt);
    Point pos = std::get<0>(pos_deriv);
    glVertex3f(pos.x, pos.y, pos.z);
    gt += gt_step;
  }
  glEnd();
}
