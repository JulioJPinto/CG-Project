#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "save.hpp"  // Assuming this is the header file where Point is defined

void saveXmlToFile(rapidxml::xml_document<>& doc, const char* filename) {
  print(std::cout, doc, 0);

  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Unable to open file " << filename << " for writing!"
              << std::endl;
    return;
  }

  file << doc;
  file.close();
  std::cout << "XML saved successfully to " << filename << std::endl;
}

void getWindowSizeAndCamera(std::string filename, Point point, Window w) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening the file!" << std::endl;
    return;
  }

  std::string xmlContent((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
  file.close();

  rapidxml::xml_document<> doc;
  try {
    doc.parse<0>(&xmlContent[0]);
  } catch (rapidxml::parse_error& e) {
    std::cerr << "XML parse error: " << e.what() << std::endl;
    return;
  }

  rapidxml::xml_node<>* root = doc.first_node("world");
  if (!root) {
    std::cerr << "Invalid XML format: 'world' node not found." << std::endl;
    return;
  }

  rapidxml::xml_node<>* windowNode = root->first_node("window");
  if (windowNode) {
    rapidxml::xml_attribute<>* widthAttr = windowNode->first_attribute("width");
    if (widthAttr)
      widthAttr->value(doc.allocate_string(std::to_string(w.width).data()));

    rapidxml::xml_attribute<>* heightAttr =
        windowNode->first_attribute("height");
    if (heightAttr)
      heightAttr->value(doc.allocate_string(std::to_string(w.height).data()));
  }

  // Accessing camera node
  rapidxml::xml_node<>* cameraNode = root->first_node("camera");
  if (cameraNode) {
    rapidxml::xml_node<>* positionNode = cameraNode->first_node("position");
    if (positionNode) {
      rapidxml::xml_attribute<>* xAttr = positionNode->first_attribute("x");
      if (xAttr)
        xAttr->value(doc.allocate_string(std::to_string(point.x).data()));

      rapidxml::xml_attribute<>* yAttr = positionNode->first_attribute("y");
      if (yAttr)
        yAttr->value(doc.allocate_string(std::to_string(point.y).data()));

      rapidxml::xml_attribute<>* zAttr = positionNode->first_attribute("z");
      if (zAttr)
        zAttr->value(doc.allocate_string(std::to_string(point.z).data()));
      ;
    }
    // Similar updates for 'lookAt' and 'up' nodes in the future
  }

  // Print camera node after modification
  rapidxml::print(std::cout, *cameraNode, 0);

  const char* filepath = "../scenes/save/latest.xml";
  saveXmlToFile(doc, filepath);
}
