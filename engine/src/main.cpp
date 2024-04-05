#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include "draw.hpp"
#include "parse.hpp"
#include "save.hpp"

std::string filename;

float cameraAngle = 0.0f;
float cameraAngleY = 0.0f;

float zoom = 1.0f;
int axis = 1;

Configuration c;
std::vector<Point> points;

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

Point calculateNewPosition(Point position) {
    // Apply rotation transformations
    float newX = position.x * cos(cameraAngleY) * cos(cameraAngle) + position.y * (cos(cameraAngle) * sin(cameraAngle) + sin(cameraAngle) * sin(cameraAngleY) * cos(cameraAngle)) + position.z * (sin(cameraAngle) * sin(cameraAngle) - cos(cameraAngle) * sin(cameraAngleY) * cos(cameraAngle));
    float newY = -position.x * cos(cameraAngleY) * sin(cameraAngle) + position.y * (cos(cameraAngle) * cos(cameraAngle) - sin(cameraAngle) * sin(cameraAngleY) * sin(cameraAngle)) + position.z * (sin(cameraAngle) * cos(cameraAngle) + cos(cameraAngle) * sin(cameraAngleY) * sin(cameraAngle));
    float newZ = position.x * sin(cameraAngleY) + position.y * (-sin(cameraAngle) * cos(cameraAngleY)) + position.z * (cos(cameraAngle) * cos(cameraAngleY));

    float inverse = 1 / zoom;

    return Point(newX * inverse, newY * inverse, newZ * inverse);
}

void saveCurrent() {
  Point newPos = calculateNewPosition(c.camera.position);
  Window w(glutGet(GLUT_WINDOW_WIDTH) ,glutGet(GLUT_WINDOW_HEIGHT));

  std::cout << w.toString();
  
  getWindowSizeAndCamera(filename,newPos, w);
}

void renderScene(void) {
  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // set camera
  glLoadIdentity();
  // gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
  gluLookAt(c.camera.position.x , c.camera.position.y, c.camera.position.z,
            c.camera.lookAt.x, c.camera.lookAt.y, c.camera.lookAt.z,
            c.camera.up.x, c.camera.up.y, c.camera.up.z);

  glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);
  glRotatef(cameraAngle, 1.0f, 0.0f, 1.0f);
  glScalef(zoom, zoom, zoom);

  // put drawing instructions here
  drawAxis();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  drawGroups(c.group);

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
    std::vector<Point> file_points = parseFile(filename);
    points.insert(points.end(), file_points.begin(), file_points.end());
  }
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Invalid Arguments\n";
    std::cout << "Usage: ./engine <file_path>\n";
    return 1;
  }

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
  glutKeyboardFunc(processNormalKeys);

  // some OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // enter GLUT�s main cycle
  glutMainLoop();

  return 1;
}