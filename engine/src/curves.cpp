#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <vector>

#include "curves.hpp"
#include "utils.hpp"

std::pair<Point, Point> get_cutmoll_rom_position(std::vector<Point> curve,
                                                 float global_time) {
  static const std::array<std::array<float, 4>, 4> matrix{{
      {-0.5f, +1.5f, -1.5f, +0.5f},
      {+1.0f, -2.5f, +2.0f, -0.5f},
      {-0.5f, +0.0f, +0.5f, +0.0f},
      {+0.0f, +1.0f, +0.0f, +0.0f},
  }};

  auto t = global_time * curve.size();

  auto segment = (int)floor(t);

  t -= segment;

  auto fst_idx = segment + curve.size() - 1;

  auto p1 = curve[(fst_idx + 0) % curve.size()];
  auto p2 = curve[(fst_idx + 1) % curve.size()];
  auto p3 = curve[(fst_idx + 2) % curve.size()];
  auto p4 = curve[(fst_idx + 3) % curve.size()];

  const std::array<std::array<float, 4>, 3> p{{
      {p1.x, p2.x, p3.x, p4.x},
      {p1.y, p2.y, p3.y, p4.y},
      {p1.z, p2.z, p3.z, p4.z},
  }};

  const std::array<float, 4> tv = {t * t * t, t * t, t, 1};
  const std::array<float, 4> tvd = {3 * t * t, 2 * t, 1, 0};

  std::array<float, 3> pv{};
  std::array<float, 3> dv{};

  for (size_t i = 0; i < 3; ++i) {
    std::array<float, 4> a{};

    for (size_t j = 0; j < 4; ++j) {
      for (size_t k = 0; k < 4; ++k) {
        a[j] += p[i][k] * matrix[j][k];
      }
    }

    for (size_t j = 0; j < 4; j++) {
      pv[i] += tv[j] * a[j];
      dv[i] += tvd[j] * a[j];
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

void Rotations::ApplyRotation(float elapsed) {
  if (this->time == 0) {
    return;
  }
  std::cout << this->time << std::endl;
  float angle = 360 * (elapsed / this->time);
  glRotatef(angle, this->x, this->y, this->z);
}

Translates::Translates() {
  this->time = 0;
  this->align = false;
  this->y_axis = Point(0, 1, 0);
}

Translates::Translates(float time, bool align, std::vector<Point> curve) {
  this->time = time;
  this->align = align;
  this->curvePoints = curve;
  this->y_axis = Point(0, 1, 0);
}

std::pair<Point, Point> Translates::getLocation(float elapsed) {
  int point_count = this->curvePoints.size();
  float gt = elapsed / this->time;
  float t = gt * point_count;
  size_t index = std::floor(t);
  t = t - index;
  return get_cutmoll_rom_position(this->curvePoints, t);
}

std::array<float, 16> Translates::rotationMatrix(Point x, Point y, Point z) {
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

void Translates::ApplyTranslate(float elapsed) {
  if (this->time == 0) {
    return;
  }

  this->renderCatmullRomCurve();

  float time = elapsed / this->time;

  auto [pos, dir] = get_cutmoll_rom_position(this->curvePoints, time);

  glTranslatef(pos.x, pos.y, pos.z);

  if (this->align) {
    auto x = dir.normalize();
    auto z = Point(x).cross(this->y_axis).normalize();
    auto y = Point(z).cross(x).normalize();
    glMultMatrixf(rotationMatrix(x, y, z).data());
  }
}

void Translates::renderCatmullRomCurve() {
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
