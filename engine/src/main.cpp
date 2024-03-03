#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include "draw.hpp"
#include "parse.hpp"

float cameraAngle = 90.0f;
float cameraAngleY = 0.0f;
char* file = "";

void changeSize(int w, int h) {
  // Prevent a divide by zero, when window is too short
  // (you can�t make a window with zero width).
  if (h == 0) h = 1;

  float ratio = w * 1.0f / h;
  // Set the projection matrix as current
  glMatrixMode(GL_PROJECTION);
  // Load the identity matrix
  glLoadIdentity();
  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);
  // Set the perspective
  gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
  // return to the model view matrix mode
  glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set camera
  glLoadIdentity();
  // gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
  gluLookAt(5.0 * sin(cameraAngle), 5.0 * cos(cameraAngleY),
            5.0 * cos(cameraAngle), 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

  // put drawing instructions here
  glBegin(GL_LINES);
  // x-axis (red)
  glColor3f(50.0f, 0.0f, 0.0f);
  glVertex3f(-50.0f, 0.0f, 0.0f);
  glVertex3f(50.0f, 0.0f, 0.0f);
  // y-axis (green)
  glColor3f(0.0f, 50.0f, 0.0f);
  glVertex3f(0.0f, -50.0f, 0.0f);
  glVertex3f(0.0f, 50.0f, 0.0f);
  // z-axis (blue)
  glColor3f(0.0f, 0.0f, 50.0f);
  glVertex3f(0.0f, 0.0f, -50.0f);
  glVertex3f(0.0f, 0.0f, 50.0f);
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  drawFile(file);

  // End of frame
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void processSpecialKeys(int key, int xx, int yy) {
  switch (key) {
    case GLUT_KEY_LEFT:
      cameraAngle -= 0.1f;
      break;
    case GLUT_KEY_RIGHT:
      cameraAngle += 0.1f;
      break;
    case GLUT_KEY_UP:
      cameraAngleY += 0.1f;
      break;
    case GLUT_KEY_DOWN:
      cameraAngleY -= 0.1f;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  std::string filename;
  filename.assign("/home/diogo/LEI/3ano/2sem/CG/CG-Project/engine/test.xml");
  Configuration c = parseConfig(filename);
  printf(c.toString().c_str());

  // put GLUT�s init here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 800);
  glutCreateWindow("CG@DI");

  // put callback registry here
  file = argv[1];
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);
  glutDisplayFunc(renderScene);
  glutReshapeFunc(reshape);

  glutSpecialFunc(processSpecialKeys);

  // some OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // enter GLUT�s main cycle
  glutMainLoop();

  return 1;
}