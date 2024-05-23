#include "group.hpp"

#include "utils.hpp"

Group::Group() {
  this->models = {};
  this->subgroups = {};
  this->static_transformations = {};
  this->rotations = {};
  this->translates = {};
  this->order = {};
}

Group::Group(std::vector<Model> models, std::vector<Group> subgroups,
             std::vector<glm::mat4> static_transformations,
             std::vector<TimeRotations> rotations,
             std::vector<TimeTranslations> translates,
             std::vector<Transformations> order) {
  this->models = models;
  this->subgroups = subgroups;
  this->static_transformations = static_transformations;
  this->rotations = rotations;
  this->translates = translates;
  this->order = order;
}


void applyTimeTransformations(std::vector<Transformations> order,
                              std::vector<glm::mat4> static_transformations,
                              std::vector<TimeRotations> rotations,
                              std::vector<TimeTranslations> translates) {
  float elapsed_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  int t = 0;
  int r = 0;
  int s = 0;

  for (Transformations type : order) {
    switch (type) {
      case TIMEROTATION:
        rotations[r].applyTimeRotation(elapsed_time);
        r++;
        break;
      case TIMETRANSLATE:
        translates[t].applyTimeTranslations(elapsed_time);
        t++;
        break;
      case STATIC:
        glMultMatrixf(&static_transformations[s][0][0]);
        s++;
        break;
    }
  }
}

void Group::drawGroup(bool lights) {
  glPushMatrix();

  applyTimeTransformations(this->order, this->static_transformations, this->rotations, this->translates);


  for (Model& model : this->models) {
    if (lights) {
      setupMaterial(model.material);
    }

    model.drawModel();
  }

  for (Group& sub : this->subgroups) {
    sub.drawGroup(lights);
  }

  glPopMatrix();
}
