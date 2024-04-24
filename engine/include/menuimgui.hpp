#ifndef MENUIMGUI_HPP
#define MENUIMGUI_HPP

extern "C" {
#include <GL/gl.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
}

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "backends/imgui_impl_glut.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void setupMenu();

void shutDownMenu();

void renderMenu();

#endif  // MENUIMGUI_HPP