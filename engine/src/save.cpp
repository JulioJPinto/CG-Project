#include "save.hpp"

void savetoFile(std::string original_scene, const Camera& cam) {
    std::ifstream file(original_scene);
    std::string xmlContent((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    file.close();

    rapidxml::xml_document<> doc;
    doc.parse<0>(&xmlContent[0]);

    rapidxml::xml_node<>* root = doc.first_node("world");
    rapidxml::xml_node<>* camera = root->first_node("camera");
    rapidxml::xml_node<>* position_n = camera->first_node("position");
    rapidxml::xml_node<>* lookat_n = camera->first_node("lookAt");

    auto set_or_update_attribute = [&doc](rapidxml::xml_node<>* node, const char* attr_name, float value) {
        rapidxml::xml_attribute<>* attr = node->first_attribute(attr_name);
        if (!attr) {
            char* attr_value = doc.allocate_string(std::to_string(value).c_str());
            attr = doc.allocate_attribute(attr_name, attr_value);
            node->append_attribute(attr);
        } else {
            attr->value(doc.allocate_string(std::to_string(value).c_str()));
        }
    };

    set_or_update_attribute(position_n, "x", cam.position.x);
    set_or_update_attribute(position_n, "y", cam.position.y);
    set_or_update_attribute(position_n, "z", cam.position.z);

    glm::vec3 lookat = cam.position + cam.forward;

    set_or_update_attribute(lookat_n, "x", lookat.x);
    set_or_update_attribute(lookat_n, "y", lookat.y);
    set_or_update_attribute(lookat_n, "z", lookat.z);

    std::ofstream out_file("scenes/last_scene.xml");
    
    out_file << doc;
    out_file.close();
}