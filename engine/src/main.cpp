
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
#include <chrono>

#include "Configuration.hpp"
#include "curves.hpp"
#include "menuimgui.hpp"
#include "parse.hpp"
#include "input.hpp"
#include "controller.hpp"

std::string filename;
bool simple = false;

bool axis = true;
bool wireframe = false;
bool normals = false;
bool culling = false;
bool lighting = false;
float speed_factor = 1.0f;

int timebase;
float frames;

Configuration c;
Camera camera;

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

  ImGui_ImplGLUT_ReshapeFunc(w, h);
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
    if (c.lights.size() != 0) {
      glEnable(GL_LIGHTING);
    }
  }
}

void setupConfig(char* arg) {
  filename.assign(arg);

  if (filename.substr(filename.size() - 4) == ".xml") {
    c = parseConfig(filename);
  } else if (filename.substr(filename.size() - 3) == ".3d") {
    c = parseConfig3D(filename);   
  } else  if (filename.substr(filename.size() - 4) == ".obj") {
    c = parseConfigObj(filename);
  } else {
    std::cout << "Invalid file format\n";
    exit(1);
  }

  camera = c.camera;

}

void setupModels(Group& group) {
  for (Model& model : group.models) {
    model.initModel();
  }
  for (Group& g : group.subgroups) {
    setupModels(g);
  }
}

void hotReload() {
  setupConfig((char*) filename.c_str());
  setupModels(c.group);
  lighting = setupLights(c.lights);
}

void resetCamera() {
  camera = c.camera;
  speed_factor = 1.0f;
}

void renderMenu() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    {
      ImGui::Begin("Infos", NULL, ImGuiWindowFlags_AlwaysAutoResize);

      ImGui::Text("FPS: %.1f (%.3f  ms/frame)", io.Framerate, 1000.f / io.Framerate);
      ImGui::Text("Camera Position: (%f, %f, %f)", camera.position.x, camera.position.y, camera.position.z);
      ImGui::Text("Camera LookAt: (%f, %f, %f)", camera.lookAt.x, camera.lookAt.y, camera.lookAt.z);
      ImGui::Text("Fov: %d Ratio: %.1f Near: %f Far: %f", c.camera.fov, static_cast<float>(glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)), c.camera.near, c.camera.far);
      ImGui::Text("XML File: %s", filename.c_str());

      ImGui::End();
    }
    {
      ImGui::Begin("Options", NULL, ImGuiWindowFlags_AlwaysAutoResize);  

      ImGui::Checkbox("Axis", &axis);
      ImGui::SameLine();
      ImGui::Checkbox("Wireframe", &wireframe);
      ImGui::SameLine();
      ImGui::Checkbox("Frustsum", &culling);
      ImGui::Checkbox("Normals", &normals);
      ImGui::SameLine();
      ImGui::Checkbox("Lighting", &lighting);
      
      
      ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 2.0f);
      ImGui::Button("Reset", ImVec2(50, 20));
      if (ImGui::IsItemClicked()) {
        resetCamera();
      }
      ImGui::SameLine();
      ImGui::Button("Hot Reload", ImVec2(100, 20));
      if (ImGui::IsItemClicked()) {
        hotReload();
      }
      ImGui::End();
    }
    ImGui::Render();
    glViewport(0, 0, (GLsizei) io.DisplaySize.x, (GLsizei) io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void fillMode() {
  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

inline float compute_delta_time() {
    static auto begin = std::chrono::high_resolution_clock::now();
    const auto end = std::chrono::high_resolution_clock::now();
    const auto delta_millis =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
            .count();
    begin = end;
    return delta_millis / 1000.f;
}

void update() {
  Input::process_input();
  static CameraController cameraController(camera);
  float delta_time = compute_delta_time();
  cameraController.update(delta_time);
}

void renderScene(void) {
  update();
  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // set camera
  glLoadIdentity();
  glm::vec3 lookat = camera.position + camera.forward;
  gluLookAt(camera.position.x, camera.position.y, camera.position.z,
            lookat.x , lookat.y, lookat.z,
            camera.up.x, camera.up.y, camera.up.z);

  Frustsum frustsum = Frustsum(camera, glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), culling);

  fillMode();
  drawAxis();

  if (lighting) {
    drawLights(c.lights);
  }

  c.group.drawGroup(lighting, frustsum, normals, speed_factor);

  // Start the Dear ImGui frame
  renderMenu();

  // End of frame
  glutSwapBuffers();
  glutPostRedisplay();

}

void mode(int agrc, char** agrv) {
  for (int i = 2; i < agrc; i++) {
    if (strcmp(agrv[i], "-s") == 0) {
      simple = true;
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

  // put GLUT�s init here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(c.window.width, c.window.height);
  glutCreateWindow("CG@DI");

  // put GLEW�s init here
  glewInit();
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  setupMenu();

  // put callback registry here
  glutDisplayFunc(renderScene);
  glutReshapeFunc(reshape);

  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutKeyboardFunc(&Input::on_key_down);
  glutKeyboardUpFunc(&Input::on_key_up);
  glutSpecialFunc(&Input::on_special_key_down);
  glutSpecialUpFunc(&Input::on_special_key_up);
  glutMouseFunc(&Input::on_mouse_button);
  glutMotionFunc(&Input::on_mouse_motion);
  glutPassiveMotionFunc(&Input::on_mouse_motion);

  // some OpenGL settings
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);
  lighting = setupLights(c.lights);
  setupModels(c.group);

  // enter GLUT�s main cycle
  glutMainLoop();
  shutDownMenu();


  return 1;
}