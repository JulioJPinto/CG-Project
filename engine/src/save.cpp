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

#include "save.hpp" // Assuming this is the header file where Point is defined

void saveXmlToFile(rapidxml::xml_document<> &doc, const char *filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << " for writing!" << std::endl;
        return;
    }

    file << doc;
    file.close();
    std::cout << "XML saved successfully to " << filename << std::endl;
}

void getWindowSizeAndCamera(std::string filename, float scale) {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

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
    } catch (rapidxml::parse_error &e) {
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
        if (rapidxml::xml_attribute<>* widthAttr = windowNode->first_attribute("width"))
            widthAttr->value(std::to_string(windowWidth).c_str());
        if (rapidxml::xml_attribute<>* heightAttr = windowNode->first_attribute("height"))
            heightAttr->value(std::to_string(windowHeight).c_str());
    }

    rapidxml::xml_node<>* cameraNode = root->first_node("camera");
    if (cameraNode) {
        if (rapidxml::xml_node<>* positionNode = cameraNode->first_node("position")) {
            if (rapidxml::xml_attribute<>* xAttr = positionNode->first_attribute("x"))
                xAttr->value(std::to_string(position.x).c_str());
            if (rapidxml::xml_attribute<>* yAttr = positionNode->first_attribute("y"))
                yAttr->value(std::to_string(position.y).c_str());
            if (rapidxml::xml_attribute<>* zAttr = positionNode->first_attribute("z"))
                zAttr->value(std::to_string(position.z).c_str());
        }
        // Similar updates for 'lookAt' and 'up' nodes
    }

    const char* filepath = "latest.xml";
    saveXmlToFile(doc, filepath);
}
