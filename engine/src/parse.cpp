#include "parse.hpp"

#include "read.hpp"

Configuration parseConfig(std::string filename) {
  // open file in read mode
  std::ifstream file(filename);

  // check if the file was opened successfully
  if (!file.is_open()) {
    std::cerr << "Error opening the file!" << std::endl;
    exit(1);
  }

  printf("Parsing file: %s\n", filename.c_str());

  // read the XML file content into a string
  std::string xmlContent((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
  file.close();

  // parse the XML string using RapidXML
  rapidxml::xml_document<> doc;
  doc.parse<0>(&xmlContent[0]);

  printf("Parsing XML\n");
  // access the root node
  rapidxml::xml_node<>* root = doc.first_node("world");

  printf("Parsing window\n");
  // window information
  char* width = root->first_node("window")->first_attribute("width")->value();
  char* height = root->first_node("window")->first_attribute("height")->value();

  Window window_info = Window(std::stoi(width), std::stoi(height));

  printf("Parsing camera\n");
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

  // light information
  printf("Parsing lights\n");
  std::vector<Light> list_lights;
  rapidxml::xml_node<>* lights = root->first_node("lights");
  if (lights) {
    for (rapidxml::xml_node<>* light = lights->first_node("light");
         light && list_lights.size() < 8;
         light = light->next_sibling("light")) {
      switch (light->first_attribute("type")->value()[0]) {
        case 'p': {
          float x = std::stof(light->first_attribute("posX")->value());
          float y = std::stof(light->first_attribute("posY")->value());
          float z = std::stof(light->first_attribute("posZ")->value());
          Light l = createPointLight(glm::vec4(x, y, z, 1));
          list_lights.push_back(l);
        } break;
        case 'd': {
          float x = std::stof(light->first_attribute("dirX")->value());
          float y = std::stof(light->first_attribute("dirY")->value());
          float z = std::stof(light->first_attribute("dirZ")->value());
          Light l = createDirectionLight(glm::vec4(x, y, z, 1));
          list_lights.push_back(l);
        } break;
        case 's': {
          float x = std::stof(light->first_attribute("posX")->value());
          float y = std::stof(light->first_attribute("posY")->value());
          float z = std::stof(light->first_attribute("posZ")->value());
          float dx = std::stof(light->first_attribute("dirX")->value());
          float dy = std::stof(light->first_attribute("dirY")->value());
          float dz = std::stof(light->first_attribute("dirZ")->value());
          float cutoff = std::stof(light->first_attribute("cutoff")->value());
          Light l = createSpotLight(glm::vec4(x, y, z, 1),
                                    glm::vec4(dx, dy, dz, 1), cutoff);
          list_lights.push_back(l);
        } break;
        default:
          break;
      }
    }
  }

  std::cout << "Parsing group" << std::endl;
  // group information
  rapidxml::xml_node<>* group = root->first_node("group");

  // Parse groups recursively
  Group groupInfo = parseGroup(group);

  // Return the configuration object
  return Configuration(window_info, camera_info, groupInfo, list_lights);
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
        Rotations r = Rotations(float(time), float(x), float(y), float(z));
        group.rotations.push_back(r);
        group.order.push_back(ROTATION);

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
        Translations t = Translations(float(time), align, curvePoints);
        group.translates.push_back(t);
        group.order.push_back(TRANSLATE);

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
    Model model = readFile(file.data());
    if (model.id == -1) {
      std::cerr << "Error reading model file: " << file << std::endl;
      return;
    }
    rapidxml::xml_node<>* color = modelNode->first_node("color");
    /*
      <color>
        <diffuse R="200" G="200" B="200" />
        <ambient R="50" G="50" B="50" />
        <specular R="0" G="0" B="0" />
        <emissive R="0" G="0" B="0" />
        <shininess value="0" />
      </color>
    */
    //Set the vector for diffuse, ambient, specular and emissive based on the above example
    glm::vec4 diffuse_vec = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
    glm::vec4 ambient_vec = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    glm::vec4 specular_vec = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 emission_vec = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    float shininess_val = 0.0f;

    if (color) {

      rapidxml::xml_node<>* diffuse = color->first_node("diffuse");
      if(diffuse) {
        diffuse_vec = glm::vec4(
        std::stof(diffuse->first_attribute("R")->value()) / 255.0f,
        std::stof(diffuse->first_attribute("G")->value()) / 255.0f,
        std::stof(diffuse->first_attribute("B")->value()) / 255.0f, 1.0f);
      } 
      
      rapidxml::xml_node<>* ambient = color->first_node("ambient");
      if (ambient) {
        ambient_vec = glm::vec4(
        std::stof(ambient->first_attribute("R")->value()) / 255.0f,
        std::stof(ambient->first_attribute("G")->value()) / 255.0f,
        std::stof(ambient->first_attribute("B")->value()) / 255.0f, 1.0f);
      }

      rapidxml::xml_node<>* specular = color->first_node("specular");
      if (specular) {
        specular_vec = glm::vec4(
        std::stof(specular->first_attribute("R")->value()) / 255.0f,
        std::stof(specular->first_attribute("G")->value()) / 255.0f,
        std::stof(specular->first_attribute("B")->value()) / 255.0f, 1.0f);
      }

      rapidxml::xml_node<>* emissive = color->first_node("emissive");
      if (emissive) {
        emission_vec = glm::vec4(
        std::stof(emissive->first_attribute("R")->value()) / 255.0f,
        std::stof(emissive->first_attribute("G")->value()) / 255.0f,
        std::stof(emissive->first_attribute("B")->value()) / 255.0f, 1.0f);
      }

      rapidxml::xml_node<>* shininess = color->first_node("shininess");
      if (shininess) {
        shininess_val = std::stof(shininess->first_attribute("value")->value());
      }
    } 

    Material material = createMaterial(ambient_vec, diffuse_vec, specular_vec, emission_vec, shininess_val);
    model.material = material;

    group.models.push_back(model);
    modelNode = modelNode->next_sibling("model");
  }
}
