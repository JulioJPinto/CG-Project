#pragma once

#include <glm/glm.hpp>
#include "Camera.hpp"

class CameraController {
public:
    // Ctor
    CameraController(Camera& camera)
        : m_camera{camera} {
        // This is temporary while the conversion from CameraData to Camera type
        // is still not in place.
        m_camera.forward = glm::normalize(m_camera.forward - m_camera.position);
    }
    // Copy
    CameraController(const CameraController&) = delete;
    CameraController& operator=(const CameraController&) = delete;
    // Move
    CameraController(CameraController&&) = delete;
    CameraController& operator=(CameraController&&) = delete;
    // Dtor
    ~CameraController() = default;

    void update(float delta_time);

private:
    static constexpr float normal_speed = 5.f;
    static constexpr float sprint_speed = 10.f;
    // FIXME: Change ref to something else
    Camera& m_camera;
    float m_speed = normal_speed;
    float m_sensitivity = 0.2f;
};

glm::vec3 spherical2Cartesian(float theta, float phi, float r);

glm::vec3 cartesian2Spherical(glm::vec3 cartesian);