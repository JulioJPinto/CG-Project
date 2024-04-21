#include <GL/glew.h>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>

#include "../../common/include/utils.hpp"
#include "draw.hpp"
#include "model.hpp"
#include "parse.hpp"

void drawbyPoints(std::vector<Point> points) {
  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 1.0f, 1.0f);
  for (size_t i = 0; i < points.size(); i += 3) {
    // Draw each triangle
    glVertex3f(points[i].x, points[i].y, points[i].z);
    glVertex3f(points[i + 1].x, points[i + 1].y, points[i + 1].z);
    glVertex3f(points[i + 2].x, points[i + 2].y, points[i + 2].z);
  }
  glEnd();
}

void drawbyVBO(std::vector<Point> points) {
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Point), &points[0],
               GL_STATIC_DRAW);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glColor3f(1.0f, 1.0f, 1.0f);
  glDrawArrays(GL_TRIANGLES, 0, points.size());

  glDisableClientState(GL_VERTEX_ARRAY);
}

void drawGroups(const Group &group) {
  const std::vector<Point>& points = group.points;

  glPushMatrix();
  GLfloat matrix[16] = {
      group.arr[0][0], group.arr[1][0], group.arr[2][0], group.arr[3][0],
      group.arr[0][1], group.arr[1][1], group.arr[2][1], group.arr[3][1],
      group.arr[0][2], group.arr[1][2], group.arr[2][2], group.arr[3][2],
      group.arr[0][3], group.arr[1][3], group.arr[2][3], group.arr[3][3]};

  glMultMatrixf(matrix);

  for (Model model : group.models) {
    model.drawModel();
  }

  for(const Group& sub : group.subgroups) {
    drawGroups(sub);
  }

  // lobo
  glPopMatrix();
}
