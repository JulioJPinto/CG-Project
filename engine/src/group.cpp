#include "group.hpp"

#include "utils.hpp"

Group::Group() {
  this->models = {};
  this->subgroups = {};
  this->transformations = glm::mat4(1.0f);
  this->rotations = {};
  this->translates = {};
  this->order = {};
}

Group::Group(std::vector<Model> models, std::vector<Group> subgroups,
             glm::mat4 transformations, std::vector<Rotations> rotations,
             std::vector<Translations> translates,
             std::vector<TimeTransform> order) {
  this->models = models;
  this->subgroups = subgroups;
  this->transformations = transformations;
  this->rotations = rotations;
  this->translates = translates;
  this->order = order;
}

void Group::translate(float x, float y, float z) {
  glm::mat4 matrix = glm::mat4(1.0f);
  matrix = glm::translate(matrix, glm::vec3(x, y, z));

  this->transformations = this->transformations * matrix;
}

void Group::scale(float x, float y, float z) {
  glm::mat4 matrix = glm::mat4(1.0f);
  matrix = glm::scale(matrix, glm::vec3(x, y, z));

  this->transformations = this->transformations * matrix;
}

void Group::rotate(float angle, float x, float y, float z) {
  glm::mat4 matrix = glm::mat4(1.0f);
  matrix = glm::rotate(matrix, angle, glm::vec3(x, y, z));

  this->transformations = this->transformations * matrix;
}

void applyTimeTransformations(std::vector<TimeTransform> order,
                              std::vector<Rotations> rotations,
                              std::vector<Translations> translates) {
  float elapsed_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  int t = 0;
  int r = 0;
  for (TimeTransform type : order) {
    switch (type) {
      case ROTATION:
        rotations[r].applyRotation(elapsed_time);
        r++;
        break;
      case TRANSLATE:
        translates[t].applyTranslations(elapsed_time);
        t++;
        break;
    }
  }
}

void Group::drawGroup() {
  glPushMatrix();

  applyTimeTransformations(this->order, this->rotations, this->translates);

  float matrixArray[16];
  int index = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      matrixArray[index++] = this->transformations[i][j];
    }
  }

  glMultMatrixf(matrixArray);

  for (Model& model : this->models) {
    model.drawModel();
  }

  for (Group& sub : this->subgroups) {
    sub.drawGroup();
  }

  glPopMatrix();
}
