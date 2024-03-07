#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

#include "../../common/include/utils.hpp"
#include "draw.hpp"

#define MODELS "../models/"

void drawTriangles(const std::vector<Point>& points) {
  glBegin(GL_TRIANGLES);
  for (size_t i = 0; i < points.size(); i += 3) {
    // Draw each triangle
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(points[i].x, points[i].y, points[i].z);
    glVertex3f(points[i + 1].x, points[i + 1].y, points[i + 1].z);
    glVertex3f(points[i + 2].x, points[i + 2].y, points[i + 2].z);
  }
  glEnd();
}

void drawFile(char* filename) {
  std::string dir = MODELS;
  dir.append(filename);

  std::vector<Point> points = parseFile(dir);
  if (points.empty()) {
    // File not found or empty, handle this case
    return;
  }
  drawTriangles(points);
}
