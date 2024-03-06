#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include "draw.hpp"
#include "parse.hpp"

#define MODELS "../models/"

float cameraAngle = 0.0f;
float cameraAngleY = 0.0f;
int axis = 1;

Configuration c;
std::vector<std::vector<Point>> vectors;

void reshape(int w, int h) {
  float aspect_ratio = (float)w / (float)h;

  // Set the viewport to the entire window
  glViewport(0, 0, w, h);

  // Set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(c.camera.fov, aspect_ratio, c.camera.near, c.camera.far);

  // Reset the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawAxis(void) {
  if (axis) {
    glBegin(GL_LINES);
    // x-axis (red)
    glColor3f(50.0f, 0.0f, 0.0f);
    glVertex3f(-500.0f, 0.0f, 0.0f);
    glVertex3f(500.0f, 0.0f, 0.0f);
    // y-axis (green)
    glColor3f(0.0f, 50.0f, 0.0f);
    glVertex3f(0.0f, -500.0f, 0.0f);
    glVertex3f(0.0f, 500.0f, 0.0f);
    // z-axis (blue)
    glColor3f(0.0f, 0.0f, 50.0f);
    glVertex3f(0.0f, 0.0f, -500.0f);
    glVertex3f(0.0f, 0.0f, 500.0f);
    glEnd();
  }
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

  glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);
  glRotatef(cameraAngle, 1.0f, 0.0f, 0.0f);
  // put drawing instructions here
  drawAxis();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  for (std::vector<Point> model : vectors) {
    drawTriangles(model);
  }

  // End of frame
  glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {
  switch (key) {
    case GLUT_KEY_LEFT:
      cameraAngle -= 1.0f;
      break;
    case GLUT_KEY_RIGHT:
      cameraAngle += 1.0f;
      break;
    case GLUT_KEY_UP:
      cameraAngleY += 1.0f;
      break;
    case GLUT_KEY_DOWN:
      cameraAngleY -= 1.0f;
      break;
    case GLUT_KEY_F2:
      if (axis) {
        axis = 0;
      } else {
        axis = 1;
      }
      break;
    case GLUT_KEY_F1:
      cameraAngle = 0;
      cameraAngleY = 0;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void setupConfig(char* arg) {
  std::string filename;
  filename.assign(arg);
  c = parseConfig(filename);
  for (std::string file : c.models) {
    std::string dir = MODELS;
    dir.append(file);

    std::vector<Point> points = parseFile(dir);
    if (points.empty()) {
      std::cerr << "File not found";
    }

    vectors.push_back(points);
  }
}

int main(int argc, char** argv) {
  setupConfig(argv[1]);

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