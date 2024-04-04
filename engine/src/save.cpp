#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "save.hpp"

// int i = 0;

// void saveXmlToFile(rapidxml::xml_document<> &doc, const char *filename) {
//     std::ofstream file(filename);
//     if (file.is_open()) {
//         file << doc;
//         file.close();
//         std::cout << "XML saved successfully to " << filename << std::endl;
//     } else {
//         std::cerr << "Unable to open file " << filename << " for writing!" <<
//         std::endl;
//     }
// }

void getWindowSizeAndCamera(std::string filename, float scale) {
  float windowWidth = glutGet(GLUT_WINDOW_WIDTH);
  float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

  GLfloat modelview[16];
  GLfloat projection[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
  glGetFloatv(GL_PROJECTION_MATRIX, projection);

  Point position(-modelview[12] * (1 / scale), -modelview[13] * (1 / scale),
                 -modelview[14] * (1 / scale));
  Point lookAt(modelview[8] * (1 / scale), modelview[9] * (1 / scale),
               modelview[10] * (1 / scale));
  Point up(modelview[4] * (1 / scale), modelview[5] * (1 / scale),
           modelview[6] * (1 / scale));

  std::ifstream file(filename);

  // check if the file was opened successfully
  if (!file.is_open()) {
    std::cerr << "Error opening the file!" << std::endl;
    exit(1);
  }

  // read the XML file content into a string
  std::string xmlContent((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
  file.close();

  // parse the XML string using RapidXML
  rapidxml::xml_document<> doc;
  doc.parse<0>(&xmlContent[0]);

  rapidxml::xml_node<>* root = doc.first_node("world");

  // Modify the window width and height attributes
  rapidxml::xml_node<>* windowNode = root->first_node("window");
  if (windowNode) {
    windowNode->first_attribute("width")->value(
        std::to_string(windowWidth).c_str());
    windowNode->first_attribute("height")->value(
        std::to_string(windowHeight).c_str());
  }

  rapidxml::xml_node<>* cameraNode = root->first_node("camera");
  if (cameraNode) {
    // Position
    rapidxml::xml_node<>* positionNode = cameraNode->first_node("position");
    if (positionNode) {
      positionNode->first_attribute("x")->value(
          std::to_string(position.x).c_str());
      positionNode->first_attribute("y")->value(
          std::to_string(position.y).c_str());
      positionNode->first_attribute("z")->value(
          std::to_string(position.z).c_str());
    }
    // LookAt
    rapidxml::xml_node<>* lookAtNode = cameraNode->first_node("lookAt");
    if (lookAtNode) {
      lookAtNode->first_attribute("x")->value(std::to_string(lookAt.x).c_str());
      lookAtNode->first_attribute("y")->value(std::to_string(lookAt.y).c_str());
      lookAtNode->first_attribute("z")->value(std::to_string(lookAt.z).c_str());
    }
    // Up
    rapidxml::xml_node<>* upNode = cameraNode->first_node("up");
    if (upNode) {
      upNode->first_attribute("x")->value(std::to_string(up.x).c_str());
      upNode->first_attribute("y")->value(std::to_string(up.y).c_str());
      upNode->first_attribute("z")->value(std::to_string(up.z).c_str());
    }
  }

  const char* filepath = "../scenes/save/latest.xml";
  // saveXmlToFile(doc, filepath);
}
