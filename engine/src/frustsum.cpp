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

Plane::Plane(const glm::vec3& normal, glm::vec3 point) {
    this->normal = glm::normalize(normal);
    this->point = point;
    float d = -normal.x * point.x - normal.y * point.y - normal.z * point.z;   

    this->abcd = glm::vec4(this->normal, d);
}


Frustsum::Frustsum(const Camera& cam, const Window& window,const bool& on) {
    this->on = on;
    if(!on) {
        return;
    }
    float aspect = static_cast<float>(window.width) / static_cast<float>(window.height);

    glm::vec3 front = glm::normalize(cam.lookAt - cam.position);

    // Ensure FOV is treated as a floating-point number
    float fovRadians = glm::radians(static_cast<float>(cam.fov));

    const float halfVSide = cam.far * tanf(fovRadians * 0.5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = cam.far * front;

    // Near and far planes
    glm::vec3 nearNormal = front;
    glm::vec3 nearPoint = cam.position + cam.near * front;

    glm::vec3 farNormal = -front;
    glm::vec3 farPoint = cam.position + frontMultFar;

    // Right and left planes
    glm::vec3 rightNormal = glm::normalize(glm::cross(frontMultFar - cam.right * halfHSide, cam.up));
    glm::vec3 rightPoint = cam.position;

    glm::vec3 leftNormal = glm::normalize(glm::cross(cam.up, frontMultFar + cam.right * halfHSide));
    glm::vec3 leftPoint = cam.position;

    // Top and bottom planes
    glm::vec3 topNormal = glm::normalize(glm::cross(cam.right, frontMultFar - cam.up * halfVSide));
    glm::vec3 topPoint = cam.position;
    
    glm::vec3 bottomNormal = glm::normalize(glm::cross(frontMultFar + cam.up * halfVSide, cam.right));
    glm::vec3 bottomPoint = cam.position;

    nearFace = { nearNormal, nearPoint };
    farFace = { farNormal, farPoint };
    rightFace = { rightNormal, rightPoint };
    leftFace = { leftNormal, leftPoint };
    topFace = { topNormal, topPoint };
    bottomFace = { bottomNormal, bottomPoint };
}



BoundingSphere::BoundingSphere(std::vector<Vertex> points) {
    // Initialize min and max points
    glm::vec3 min = {INFINITY, INFINITY, INFINITY};
    glm::vec3 max = {-INFINITY, -INFINITY, -INFINITY};

    // Sum to calculate the center
    glm::vec3 sum = {0.0f, 0.0f, 0.0f};

    for (const Vertex& point : points) {
        // Update min and max
        if (point.position.x < min.x) {
            min.x = point.position.x;
        }
        if (point.position.y < min.y) {
            min.y = point.position.y;
        }
        if (point.position.z < min.z) {
            min.z = point.position.z;
        }

        if (point.position.x > max.x) {
            max.x = point.position.x;
        }
        if (point.position.y > max.y) {
            max.y = point.position.y;
        }
        if (point.position.z > max.z) {
            max.z = point.position.z;
        }

        glm::vec3 pointPosition = {point.position.x, point.position.y, point.position.z};
        // Sum up the positions
        sum += pointPosition;
    }

    // Calculate the center as the average of all points
    center = sum / static_cast<float>(points.size());
    std::cout << "Center: " << center.x << ", " << center.y << ", " << center.z << std::endl;

    // Calculate the radius as the distance from the center to the farthest point (max)
    radius = glm::distance(center, max);
}


bool BoundingSphere::isInsideFrustsum(const Frustsum& frustsum, glm::mat4 transformations) const {

    if(!frustsum.on) {
        return true;
    }

    glm::vec3 center = glm::vec3(transformations * glm::vec4(this->center, 1.0f));
    float radius = this->radius * glm::length(glm::vec3(transformations[0])) / 2;

    return frustsum.nearFace.distanceToPoint(center) > -radius &&
           frustsum.farFace.distanceToPoint(center) > -radius &&
           frustsum.rightFace.distanceToPoint(center) > -radius &&
           frustsum.leftFace.distanceToPoint(center) > -radius &&
           frustsum.topFace.distanceToPoint(center) > -radius &&
           frustsum.bottomFace.distanceToPoint(center) > -radius;
}
    

