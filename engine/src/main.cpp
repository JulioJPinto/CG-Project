
#include <GL/glew.h>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
#include "parse.hpp"
#include "save.hpp"

std::string filename;

float cameraAngle = 0.0f;
float cameraAngleY = 0.0f;

float zoom = 1.0f;
int axis = 1;

int timebase;
float frames;

Configuration c;

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

Point rotatePoint(Point point) {
  float x = point.x;
  float y = point.y;
  float z = point.z;

  float r = sqrt(x * x + y * y + z * z);

  float alfa = atan2(y, x);
  float beta = acos(z / r);

  // Convert angles from degrees to radians
  float angle = (cameraAngle + alfa) * M_PI / 180.0;
  float angleY = (cameraAngleY + beta) * M_PI / 180.0;

  // Rotation matrices
  std::vector<std::vector<double>> rotZ = {
      {1, 0, 0}, {0, cos(angle), -sin(angle)}, {0, sin(angle), cos(angle)}};

  std::vector<std::vector<double>> rotY = {
      {cos(angleY), 0, sin(angleY)}, {0, 1, 0}, {-sin(angleY), 0, cos(angleY)}};

  std::vector<std::vector<double>> rotX = {
      {cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};

  double newX = rotX[0][0] * x + rotX[0][1] * y + rotX[0][2] * z;
  double newY = rotX[1][0] * x + rotX[1][1] * y + rotX[1][2] * z;
  double newZ = rotX[2][0] * x + rotX[2][1] * y + rotX[2][2] * z;

  x = newX;
  y = newY;
  z = newZ;

  newX = rotY[0][0] * x + rotY[0][1] * y + rotY[0][2] * z;
  newY = rotY[1][0] * x + rotY[1][1] * y + rotY[1][2] * z;
  newZ = rotY[2][0] * x + rotY[2][1] * y + rotY[2][2] * z;

  x = newX;
  y = newY;
  z = newZ;

  newX = (rotZ[0][0] * x + rotZ[0][1] * y + rotZ[0][2] * z);
  newY = (rotZ[1][0] * x + rotZ[1][1] * y + rotZ[1][2] * z);
  newZ = (rotZ[2][0] * x + rotZ[2][1] * y + rotZ[2][2] * z);

  return Point(newZ, newY, newX);
}

void saveCurrent() {
  Point newPos = c.camera.position;
  if (cameraAngle != 0 || cameraAngleY != 0) {
    newPos = rotatePoint(c.camera.position);
  }
  Window w(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

  getWindowSizeAndCamera(filename, newPos.multiply(1 / zoom), w);
}

void frameCounter() {
  static int frame = 0;
  static float time = 0;
  static float fps = 0;

  frame++;
  time = glutGet(GLUT_ELAPSED_TIME);
  if (time - timebase > 1000) {
    fps = frame * 1000.0 / (time - timebase);
    timebase = time;
    frame = 0;
  }

  static int i = 0;
  i++;
  // print fps
  if (i % 100 == 0) {
    std::cout << "FPS: " << std::to_string(fps) << std::endl;
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
  glRotatef(cameraAngle, 1.0f, 0.0f, 1.0f);
  glScalef(zoom, zoom, zoom);

  // put drawing instructions here
  drawAxis();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  c.group.drawGroup();

  frameCounter();

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
    default:
      break;
  }
  glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
  float value = zoom * 0.1;
  switch (key) {
    case 'a':
      if (axis) {
        axis = 0;
      } else {
        axis = 1;
      }
      break;
    case 'r':
      cameraAngle = 0;
      cameraAngleY = 0;
      zoom = 1.0f;
      break;
    case 'o':
      zoom -= value;
      break;
    case 'i':
      zoom += value;
      break;
    case 's':
      std::cout << "Saving Current Settings to file";
      saveCurrent();
      break;
    default:
      break;
  }
}

void setupConfig(char* arg) {
  filename.assign(arg);

  if (filename.substr(filename.size() - 4) == ".xml") {
    c = parseConfig(filename);
  } else {
    c = parseConfig("../scenes/default.xml");
  }
}

void flaghandles(int argc, char** argv) {
  for (int i = 2; i < argc; i++) {
    if (!(argv[i] == "-vsync-off")) {
      putenv("vblank_mode=0");
    }
  }
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Invalid Arguments\n";
    std::cout << "Usage: ./engine <file_path> [flags]\n";
    return 1;
  }

  setupConfig(argv[1]);
  flaghandles(argc, argv);

  // put GLUT�s init here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(c.window.width, c.window.height);
  glutCreateWindow("CG@DI");

  glewInit();
  glEnableClientState(GL_VERTEX_ARRAY);

  // put callback registry here
  glutIdleFunc(renderScene);
  glutDisplayFunc(renderScene);
  glutReshapeFunc(reshape);

  glutSpecialFunc(processSpecialKeys);
  glutKeyboardFunc(processNormalKeys);

  // some OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // enter GLUT�s main cycle
  glutMainLoop();

  return 1;
}