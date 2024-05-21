
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
#include "curves.hpp"
#include "menuimgui.hpp"
#include "parse.hpp"

std::string filename;

float cameraAngle = 0.0f;
float cameraAngleY = 0.0f;

float zoom = 1.0f;
int axis = 1;
int wireframe = 1;
bool isDragging = false;
int lastMouseX, lastMouseY;

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
    glDisable(GL_LIGHTING);
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
    if(c.lights.size() != 0) {
      glEnable(GL_LIGHTING);
    }
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
  if (i % 100 == 0) {
    std::cout << "FPS: " << std::to_string(fps) << std::endl;
  }
}

void renderScene(void) {
  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // set camera
  glLoadIdentity();
  gluLookAt(c.camera.position.x, c.camera.position.y, c.camera.position.z,
            c.camera.lookAt.x, c.camera.lookAt.y, c.camera.lookAt.z,
            c.camera.up.x, c.camera.up.y, c.camera.up.z);

  glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);
  glRotatef(cameraAngle, 1.0f, 0.0f, 1.0f);
  glScalef(zoom, zoom, zoom);

  drawAxis();

  bool lights = c.lights.size() != 0;
  if (lights) {
    drawLights(c.lights);
  }

  c.group.drawGroup(lights);

  frameCounter();

  // End of frame
  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      isDragging = true;
      lastMouseX = x;
      lastMouseY = y;
    } else if (state == GLUT_UP) {
      isDragging = false;
    }
  }
}

void motion(int x, int y) {
  if (isDragging) {
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    cameraAngleY += dx * 0.1f;
    cameraAngle += dy * 0.1f;

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
  }
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
    case 'c':
      if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireframe = 0;
      } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        wireframe = 1;
      }
    default:
      break;
  }
}

void setupConfig(char* arg) {
  filename.assign(arg);

  if (filename.substr(filename.size() - 4) == ".xml") {
    printf("XML\n");
    c = parseConfig(filename);
  } else {
    std::cout << "Invalid file format\n";
    exit(1);
  }
}

void setupModels(Group& group) {
  for (Model& model : group.models) {
    model.initModel();
  }
  for (Group& g : group.subgroups) {
    setupModels(g);
  }
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Invalid Arguments\n";
    std::cout << "Usage: ./engine <file_path> [flags]\n";
    return 1;
  }

  setupConfig(argv[1]);

  // put GLUT�s init here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(c.window.width, c.window.height);
  glutCreateWindow("CG@DI");

  // setupMenu();
  glewInit();
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  // put callback registry here
  glutIdleFunc(renderScene);
  glutDisplayFunc(renderScene);
  glutReshapeFunc(reshape);

  glutSpecialFunc(processSpecialKeys);
  glutKeyboardFunc(processNormalKeys);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  // some OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  setupLights(c.lights);
  setupModels(c.group);

  // enter GLUT�s main cycle
  glutMainLoop();

  return 1;
}