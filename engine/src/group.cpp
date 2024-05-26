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


glm::mat4 applyTransformations(std::vector<Transformations> order,
                              std::vector<glm::mat4> static_transformations,
                              std::vector<TimeRotations> rotations,
                              std::vector<TimeTranslations> translates,
                              float speed_factor) {
  float elapsed_time = speed_factor * glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  int t = 0;
  int r = 0;
  int s = 0;

  glm::mat4 matrix = glm::mat4(1.0f);

  for (Transformations type : order) {
    switch (type) {
      case TIMEROTATION:
        matrix *= rotations[r].applyTimeRotation(elapsed_time);
        r++;
        break;
      case TIMETRANSLATE:
        matrix *= translates[t].applyTimeTranslations(elapsed_time);
        t++;
        break;
      case STATIC:
        matrix *= static_transformations[s];
        s++;
        break;
    }
  }

  glMultMatrixf(&matrix[0][0]);
  return matrix;
}

void Group::drawGroup(bool lights, const Frustsum& frustsum, bool normals, float speed_factor) {
  glPushMatrix();

  glm::mat4 matrix = applyTransformations(this->order, this->static_transformations, this->rotations, this->translates, speed_factor);

  for (Model& model : this->models) {
    if (lights) {
      setupMaterial(model.material);
    }

    if(model.bounding_sphere.isInsideFrustsum(frustsum, matrix)) {
      model.drawModel();
      if(normals) model.drawNormals();
    }
  }

  for (Group& sub : this->subgroups) {
    sub.drawGroup(lights, frustsum, normals, speed_factor);
  }

  glPopMatrix();
}
