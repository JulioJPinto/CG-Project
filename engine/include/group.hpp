#ifndef GROUP_HPP
#define GROUP_HPP

#include <array>  // Include for std::array
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

#include "curves.hpp"
#include "model.hpp"
#include "utils.hpp"

class Group {
 public:
  std::vector<Model> models;
  std::vector<Group> subgroups;
  glm::mat4 transformations = glm::mat4(1.0f);
  

  std::vector<Rotations> rotations;
  std::vector<Translations> translates;
  std::vector<TimeTransform> order;

  Group();
  Group(std::vector<Model> models, std::vector<Group> subgroups,
        glm::mat4 transformations, std::vector<Rotations> rotations,
        std::vector<Translations> translates,
        std::vector<TimeTransform> order);  // Updated constructor

  void translate(float x, float y, float z);

  void scale(float x, float y, float z);

  void rotate(float angle, float x, float y, float z);

  void drawGroup(bool lights);
};

#endif  // GROUP_HPP
