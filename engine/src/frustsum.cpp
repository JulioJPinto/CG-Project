#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "frustsum.hpp"

Frustsum::Frustsum(const Camera& cam) {
    glm::vec3 lookAt;
    glm::vec3 position;
    glm::vec3 up;

    lookAt.x = cam.lookAt.x;
    lookAt.y = cam.lookAt.y;
    lookAt.z = cam.lookAt.z;

    position.x = cam.position.x;
    position.y = cam.position.y;
    position.z = cam.position.z;

    up.x = cam.up.x;
    up.y = cam.up.y;
    up.z = cam.up.z;

    glm::vec3 zAxis = glm::normalize(lookAt - position);
    glm::vec3 xAxis = glm::normalize(glm::cross(up, zAxis));
    glm::vec3 yAxis = glm::normalize(glm::cross(zAxis, xAxis));

    // near plane
    glm::vec3 nearCenter = position + zAxis * cam.near;
    glm::vec3 nearNormal = -zAxis;
    nearFace = Plane(nearNormal, -glm::dot(nearNormal, nearCenter));
    
    // far plane
    glm::vec3 farCenter = position + zAxis * cam.far;
    glm::vec3 farNormal = zAxis;
    farFace = Plane(farNormal, -glm::dot(farNormal, farCenter));

    // right plane
    glm::vec3 rightCenter = nearCenter + xAxis * cam.near * glm::tan(cam.fov / 2.f);
    glm::vec3 rightNormal = glm::normalize(glm::cross(yAxis, rightCenter - position));
    rightFace = Plane(rightNormal, -glm::dot(rightNormal, rightCenter));

    // left plane
    glm::vec3 leftCenter = nearCenter - xAxis * cam.near * glm::tan(cam.fov / 2.f);
    glm::vec3 leftNormal = -glm::normalize(glm::cross(yAxis, leftCenter - position));
    leftFace = Plane(leftNormal, -glm::dot(leftNormal, leftCenter));

    // top plane
    glm::vec3 topCenter = nearCenter + yAxis * cam.near * glm::tan(cam.fov / 2.f);
    glm::vec3 topNormal = glm::normalize(glm::cross(xAxis, topCenter - position));
    topFace = Plane(topNormal, -glm::dot(topNormal, topCenter));

    // bottom plane
    glm::vec3 bottomCenter = nearCenter - yAxis * cam.near * glm::tan(cam.fov / 2.f);
    glm::vec3 bottomNormal = -glm::normalize(glm::cross(xAxis, bottomCenter - position));
    bottomFace = Plane(bottomNormal, -glm::dot(bottomNormal, bottomCenter));

}

BoundingSphere::BoundingSphere(std::vector<Point> points) {
    glm::vec3 max = {-INFINITY, -INFINITY, -INFINITY};

    for (const Point& point : points) {

        if (point.x > max.x) max.x = point.x;
        if (point.y > max.y) max.y = point.y;
        if (point.z > max.z) max.z = point.z;
    }

    center = glm::vec3(0.0f);
    radius = glm::distance(center, max);

}

// BoundingSphere::applyTransformations() {

// }

bool BoundingSphere::isInsideFrustsum(const Frustsum& frustsum) const {

    return frustsum.nearFace.distanceToPoint(center) > -radius &&
           frustsum.farFace.distanceToPoint(center) > -radius &&
           frustsum.rightFace.distanceToPoint(center) > -radius &&
           frustsum.leftFace.distanceToPoint(center) > -radius &&
           frustsum.topFace.distanceToPoint(center) > -radius &&
           frustsum.bottomFace.distanceToPoint(center) > -radius;
}
    



