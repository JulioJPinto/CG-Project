#include "Configuration.cpp"
#include "Camera.cpp"
#include "Window.cpp"

#include <iostream>
#include <fstream>

#include "utils.hpp"

#include "../../lib/rapidxml-1.13/rapidxml.hpp"

Configuration parseConfig(char* filename) {
    // open file in read mode
    std::fstream file;
    file.open(filename, std::ios::in);

    // check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        exit(1);
    }

    // read the XML file content into a string
    std::string xmlContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // parse the XML string using RapidXML
    rapidxml::xml_document<> doc;
    doc.parse<0>(&xmlContent[0]);

    // access the root node
    rapidxml::xml_node<>* root = doc.first_node("world");
    
    // window information
    char* width = root->first_node("window")->first_attribute("width")->value();
    char* height = root->first_node("window")->first_attribute("height")->value();

    Window window_info = Window(std::stof(width), std::stof(height));

    // camera information
    rapidxml::xml_node<>* camera = root->first_node("camera");

    rapidxml::xml_node<>* position = camera->first_node("position");
    Point position = Point(
        std::stof(position->first_attribute("x")->value()),
        std::stof(position->first_attribute("y")->value()),
        std::stof(position->first_attribute("z")->value())
    );

    rapidxml::xml_node<>* lookAt = camera->first_node("lookAt");
    Point lookAt = Point(
        std::stof(lookAt->first_attribute("x")->value()),
        std::stof(lookAt->first_attribute("y")->value()),
        std::stof(lookAt->first_attribute("z")->value())
    );

    rapidxml::xml_node<>* up = camera->first_node("up");
    Point up = Point(
        std::stof(up->first_attribute("x")->value()),
        std::stof(up->first_attribute("y")->value()),
        std::stof(up->first_attribute("z")->value())
    );

    rapidxml::xml_node<>* projection = camera->first_node("projection");
    int fov = std::stoi(projection->first_attribute("fov")->value());
    float near = std::stof(projection->first_attribute("near")->value());
    float far = std::stof(projection->first_attribute("far")->value());

    Camera camera_info = Camera(position, lookAt, up, fov, near, far);

    // models
    std::vector<char*> models_info;
    rapidxml::xml_node<>* models = root->first_node("group")->first_node("models");
    for (rapidxml::xml_node<>* model = models->first_node("model"); model; model = model->next_sibling("model")) {
        models_info.push_back(model->first_attribute("file")->value());
    }

    return Configuration(window_info, camera_info, models_info);
}
