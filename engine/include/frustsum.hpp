#ifndef FRUSTSUM_CPP
#define FRUSTSUM_CPP

#include <math.h>
#include <iostream>
#include <glm/glm.hpp>
#include "Window.hpp"
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

    void printPlane() {
        std::cout << "Distance: " << distance << std::endl;
        std::cout << "Normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;
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
    Frustsum(const Camera& cam, const Window& window);

    void printFrustsum() {
        std::cout << "Near" << std::endl;
        nearFace.printPlane();
        std::cout << "Far" << std::endl;
        farFace.printPlane();
        std::cout << "right" << std::endl;
        rightFace.printPlane();
        std::cout << "left" << std::endl;
        leftFace.printPlane();
        std::cout << "top" << std::endl;
        topFace.printPlane();
        std::cout << "bottom" << std::endl;
        bottomFace.printPlane();
    }

};


struct BoundingSphere {

    glm::vec3 center;
    float radius;

    BoundingSphere() = default;
    BoundingSphere(const BoundingSphere& other) = default;
    BoundingSphere(const glm::vec3& center, float radius) : center(center), radius(radius) {}
    BoundingSphere(std::vector<Vertex> points);

    bool isInsideFrustsum(const Frustsum& frustsum, glm::mat4 transformations) const;

};

#endif // FRUSTSUM_CPP