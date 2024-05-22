#ifndef FRUSTSUM_CPP
#define FRUSTSUM_CPP

#include <math.h>

#include <glm/glm.hpp>

#include "model.hpp"
#include "Camera.hpp"


struct Plane {
    
    float distance = 0.f;
    glm::vec3 normal = { 0.f, 1.f, 0.f };

    Plane() = default;
    Plane(const Plane& other) = default;
    Plane(const glm::vec3& normal, float distance) : normal(normal), distance(distance) {}

    float distanceToPoint(const glm::vec3& point) const {
        return glm::dot(normal, point) + distance;
    }


};

struct Frustsum {
    Plane nearFace;
    Plane farFace;
    Plane rightFace;
    Plane leftFace;
    Plane topFace;
    Plane bottomFace;

    Frustsum() = default;
    Frustsum(const Frustsum& other) = default;
    Frustsum(const Plane& nearFace, const Plane& farFace, const Plane& rightFace, const Plane& leftFace, const Plane& topFace, const Plane& bottomFace)
        : nearFace(nearFace), farFace(farFace), rightFace(rightFace), leftFace(leftFace), topFace(topFace), bottomFace(bottomFace) {}

    Frustsum createFrustumFromCamera(const Camera& cam);

    bool isInsideFrustsum(const Model& model);
};


#endif // FRUSTSUM_CPP