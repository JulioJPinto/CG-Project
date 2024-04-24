#include "parse.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Configuration parseConfig(std::string filename) {
  // open file in read mode
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

  // access the root node
  rapidxml::xml_node<>* root = doc.first_node("world");

  // window information
  char* width = root->first_node("window")->first_attribute("width")->value();
  char* height = root->first_node("window")->first_attribute("height")->value();

  Window window_info = Window(std::stoi(width), std::stoi(height));

  // camera information
  rapidxml::xml_node<>* camera = root->first_node("camera");

  rapidxml::xml_node<>* position_n = camera->first_node("position");
  Point position = Point(std::stof(position_n->first_attribute("x")->value()),
                         std::stof(position_n->first_attribute("y")->value()),
                         std::stof(position_n->first_attribute("z")->value()));

  rapidxml::xml_node<>* lookAt_n = camera->first_node("lookAt");
  Point lookAt = Point(std::stof(lookAt_n->first_attribute("x")->value()),
                       std::stof(lookAt_n->first_attribute("y")->value()),
                       std::stof(lookAt_n->first_attribute("z")->value()));

  rapidxml::xml_node<>* up_n = camera->first_node("up");
  Point up = Point(std::stof(up_n->first_attribute("x")->value()),
                   std::stof(up_n->first_attribute("y")->value()),
                   std::stof(up_n->first_attribute("z")->value()));

  rapidxml::xml_node<>* projection = camera->first_node("projection");
  int fov = std::stoi(projection->first_attribute("fov")->value());
  float near = std::stof(projection->first_attribute("near")->value());
  float far = std::stof(projection->first_attribute("far")->value());

  Camera camera_info = Camera(position, lookAt, up, fov, near, far);

  // group information
  rapidxml::xml_node<>* group = root->first_node("group");

  // Parse groups recursively
  Group groupInfo = parseGroup(group);

  // Return the configuration object
  return Configuration(window_info, camera_info, groupInfo);
}

// Parse a group node recursively
Group parseGroup(rapidxml::xml_node<>* groupNode) {
  Group group;

  // Parse transform node
  rapidxml::xml_node<>* transformNode = groupNode->first_node("transform");
  if (transformNode) {
    parseTransform(transformNode, group);
  }

  // Parse models node
  rapidxml::xml_node<>* modelsNode = groupNode->first_node("models");
  if (modelsNode) {
    parseModels(modelsNode, group);
  }

  // Parse subgroups node
  rapidxml::xml_node<>* subgroupsNode = groupNode->first_node("group");
  while (subgroupsNode) {
    Group subgroup = parseGroup(subgroupsNode);
    group.subgroups.push_back(subgroup);
    subgroupsNode = subgroupsNode->next_sibling("group");
  }

  return group;
}

// Parse transform node
void parseTransform(rapidxml::xml_node<>* transformNode, Group& group) {
  // Iterate over all transformation nodes
  for (rapidxml::xml_node<>* node = transformNode->first_node(); node;
       node = node->next_sibling()) {
    std::string nodeName = node->name();
    if (nodeName == "scale") {
      float x = std::stof(node->first_attribute("x")->value());
      float y = std::stof(node->first_attribute("y")->value());
      float z = std::stof(node->first_attribute("z")->value());
      group.scale(x, y, z);
    } else if (nodeName == "rotate") {
      if (node->first_attribute("time")) {
        float time = std::stof(node->first_attribute("time")->value());
        float x = std::stof(node->first_attribute("x")->value());
        float y = std::stof(node->first_attribute("y")->value());
        float z = std::stof(node->first_attribute("z")->value());
        group.rotations.time = float(time);
        group.rotations.x = float(x);
        group.rotations.y = float(y);
        group.rotations.z = float(z);

      } else {
        float angle = std::stof(node->first_attribute("angle")->value());
        float x = std::stof(node->first_attribute("x")->value());
        float y = std::stof(node->first_attribute("y")->value());
        float z = std::stof(node->first_attribute("z")->value());
        group.rotate(angle, x, y, z);
      }

    } else if (nodeName == "translate") {
      if (node->first_attribute("time")) {
        float time = std::stof(node->first_attribute("time")->value());

        bool align = true;
        if (node->first_attribute("align")) {
          align =
              std::string(node->first_attribute("align")->value()) == "true";
        }
        std::vector<Point> curvePoints;
        while (node->first_node("point")) {
          rapidxml::xml_node<>* point = node->first_node("point");
          float x = std::stof(point->first_attribute("x")->value());
          float y = std::stof(point->first_attribute("y")->value());
          float z = std::stof(point->first_attribute("z")->value());
          curvePoints.push_back(Point(x, y, z));
          node->remove_node(point);
        }
        group.translates.time = float(time);
        group.translates.align = float(align);
        std::vector<Point> cPoints = curvePoints;
        group.translates.curvePoints = cPoints;
        std::cout << group.translates.time << std::endl;
        std::cout << group.translates.align << std::endl;
        std::cout << group.translates.curvePoints.size() << std::endl;

      } else {
        float x = std::stof(node->first_attribute("x")->value());
        float y = std::stof(node->first_attribute("y")->value());
        float z = std::stof(node->first_attribute("z")->value());
        group.translate(x, y, z);
      }
    }
  }
}

// Parse models node
void parseModels(rapidxml::xml_node<>* modelsNode, Group& group) {
  rapidxml::xml_node<>* modelNode = modelsNode->first_node("model");
  while (modelNode) {
    const std::string& file = modelNode->first_attribute("file")->value();
    const std::vector<Point>& file_points = parseFile(file);
    const Model& model = getModel(file);
    group.points.insert(group.points.end(), file_points.begin(),
                        file_points.end());
    group.models.push_back(model);

    modelNode = modelNode->next_sibling("model");
  }
}
