#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

#include "draw.hpp"
#include "utils.hpp"


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

