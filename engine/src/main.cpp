
#include <GL/glew.h>
extern "C" {
#include <GL/gl.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
}

#define _USE_MATH_DEFINES
#include <math.h>

#include "Configuration.hpp"
#include "parse.hpp"
#include "menuimgui.hpp"
#include "curves.hpp"

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

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
  }
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

  //renderMenu();

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

  //setupMenu();

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

  //shutDownMenu();

  return 1;
}