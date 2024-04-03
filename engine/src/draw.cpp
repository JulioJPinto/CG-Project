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
#include "parse.hpp"

void drawGroups(const Group &group) {
  std::vector<Point> points = group.points;

  glPushMatrix();
  GLfloat matrix[16] = {
      group.arr[0][0], group.arr[1][0], group.arr[2][0], group.arr[3][0],
      group.arr[0][1], group.arr[1][1], group.arr[2][1], group.arr[3][1],
      group.arr[0][2], group.arr[1][2], group.arr[2][2], group.arr[3][2],
      group.arr[0][3], group.arr[1][3], group.arr[2][3], group.arr[3][3]};

  glMultMatrixf(matrix);

  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 1.0f, 1.0f);
  for (size_t i = 0; i < points.size(); i += 3) {
    // Draw each triangle
    glVertex3f(points[i].x, points[i].y, points[i].z);
    glVertex3f(points[i + 1].x, points[i + 1].y, points[i + 1].z);
    glVertex3f(points[i + 2].x, points[i + 2].y, points[i + 2].z);
  }
  glEnd();

  for (size_t i = 0; i < group.subgroups.size(); i++) {
    drawGroups(group.subgroups[i]);
  }

  // lobo
  glPopMatrix();
}
