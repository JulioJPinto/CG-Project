#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.hpp"
#include "frustsum.hpp"

/*
{
    Frustum     frustum;
    const float halfVSide = zFar * tanf(fovY * .5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = zFar * front;

    frustum.nearFace = { position + near * front, front };
    frustum.farFace = { position + frontMultFar, -front };
    frustum.rightFace = { position,
                            glm::cross(frontMultFar - cam.Right * halfHSide, cam.Up) };
    frustum.leftFace = { position,
                            glm::cross(cam.Up,frontMultFar + cam.Right * halfHSide) };
    frustum.topFace = { position,
                            glm::cross(cam.Right, frontMultFar - cam.Up * halfVSide) };
    frustum.bottomFace = { position,
                            glm::cross(frontMultFar + cam.Up * halfVSide, cam.Right) };

    return frustum;
}
*/


Frustsum::Frustsum(const Camera& cam, const Window& window) {
    float aspect = (float)window.width / (float)window.height;

    glm::vec3 front = glm::normalize(cam.lookAt - cam.position);

    const float halfVSide = cam.far * tanf(cam.fov * 0.5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = cam.far * front;

    glm::vec3 nearNormal = front;
    float nearDistance = glm::dot(nearNormal, cam.position + cam.near * front);

    glm::vec3 farNormal = -front;
    float farDistance = glm::dot(farNormal, cam.position + frontMultFar);

    glm::vec3 rightNormal = glm::normalize(glm::cross(frontMultFar - cam.right * halfHSide, cam.real_up));
    float rightDistance = glm::dot(rightNormal, cam.position);

    glm::vec3 leftNormal = glm::normalize(glm::cross(cam.up, frontMultFar + cam.right * halfHSide));
    float leftDistance = glm::dot(leftNormal, cam.position);

    glm::vec3 topNormal = glm::normalize(glm::cross(cam.right, frontMultFar - cam.up * halfVSide));
    float topDistance = glm::dot(topNormal, cam.position);

    glm::vec3 bottomNormal = glm::normalize(glm::cross(frontMultFar + cam.real_up * halfVSide, cam.right));
    float bottomDistance = glm::dot(bottomNormal, cam.position);

    nearFace = { nearNormal, nearDistance };
    farFace = { farNormal, farDistance };
    rightFace = { rightNormal, rightDistance };
    leftFace = { leftNormal, leftDistance };
    topFace = { topNormal, topDistance };
    bottomFace = { bottomNormal, bottomDistance };

    this->printFrustsum();
}


BoundingSphere::BoundingSphere(std::vector<Vertex> points) {
    glm::vec3 max = {-INFINITY, -INFINITY, -INFINITY};

    for (const Vertex& point : points) {

        if (point.position.x > max.x) {
            max.x = point.position.x;
        }

        if (point.position.y > max.y) {
            max.y = point.position.y;
        }

        if (point.position.z > max.z) {
            max.z = point.position.z;
        }
    }

    center = glm::vec3(0.0f);
    radius = glm::distance(center, max);

}

bool BoundingSphere::isInsideFrustsum(const Frustsum& frustsum, glm::mat4 transformations) const {

    glm::vec3 center = glm::vec3(transformations * glm::vec4(this->center, 1.0f));
    float radius = this->radius * glm::length(glm::vec3(transformations[0])) / 2;


    return frustsum.nearFace.distanceToPoint(center) > -radius &&
           frustsum.farFace.distanceToPoint(center) > -radius &&
           frustsum.rightFace.distanceToPoint(center) > -radius &&
           frustsum.leftFace.distanceToPoint(center) > -radius &&
           frustsum.topFace.distanceToPoint(center) > -radius &&
           frustsum.bottomFace.distanceToPoint(center) > -radius;
}
    

