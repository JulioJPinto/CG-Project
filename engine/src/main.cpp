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

Configuration c;

void changeSize(int w, int h) {
  // Prevent a divide by zero, when window is too short
  // (you can�t make a window with zero width).
  if (h == 0) h = 1;

  float ratio = c.window.width * 1.0f / c.window.height;
  // Set the projection matrix as current
  glMatrixMode(GL_PROJECTION);
  // Load the identity matrix
  glLoadIdentity();
  // Set the viewport to be the entire window
  glViewport(0, 0, c.window.width, c.window.height);
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
  gluLookAt(c.camera.position.x, c.camera.position.y, c.camera.position.z,
            c.camera.lookAt.x, c.camera.lookAt.y, c.camera.lookAt.z,
            c.camera.up.x, c.camera.up.y, c.camera.up.z);

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
  for (std::string model : c.models) {
    drawFile(model.data());
  }

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
  filename.assign(argv[1]);
  c = parseConfig(filename);

  // put GLUT�s init here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(c.window.width, c.window.height);
  glutCreateWindow("CG@DI");

  // put callback registry here
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