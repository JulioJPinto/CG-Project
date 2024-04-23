#ifndef MENUIMGUI_HPP
#define MENUIMGUI_HPP

#include <GL/glut.h>

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