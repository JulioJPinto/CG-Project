#include "controller.hpp"
#include "input.hpp"

glm::vec3 spherical_to_cartesian(glm::vec3  vec) {
    const float p = vec.x;
    const float theta = vec.y;
    const float phi = vec.z;

    return glm::vec3 {
        std::sin(theta) * std::sin(phi) * p,
        std::cos(phi) * p,
        std::sin(phi) * p * std::cos(theta)
    };
}

glm::vec3  cartesian_to_spherical(glm::vec3  vec) {
    const float x = vec.x;
    const float y = vec.y;
    const float z = vec.z;

    const float abs = std::sqrt(x * x + y * y + z * z);
    return glm::vec3 {abs, std::atan2(x, z), std::acos(y / abs)};
}

void CameraController::update(float delta_time) {
    const glm::vec3 right =
        glm::normalize(glm::cross(m_camera.forward, m_camera.up));

    // Update speed
    m_speed = Input::is_down(Keyboard::LShift) ? sprint_speed : normal_speed;

    // Update camera position
    if (Input::is_down(Keyboard::W)) {
        m_camera.position += m_camera.forward * m_speed * delta_time;
    }
    if (Input::is_down(Keyboard::S)) {
        m_camera.position -= m_camera.forward * m_speed * delta_time;
    }
    if (Input::is_down(Keyboard::D)) {
        m_camera.position += right * m_speed * delta_time;
    }
    if (Input::is_down(Keyboard::A)) {
        m_camera.position -= right * m_speed * delta_time;
    }

    //Update camera direction with Keyboard
    if (Input::is_down(Keyboard::Up)) {
        glm::vec3 spherical_forward = cartesian_to_spherical(m_camera.forward);
        spherical_forward.z += delta_time * m_sensitivity;
        m_camera.forward = spherical_to_cartesian(spherical_forward);
    }

    if (Input::is_down(Keyboard::Down)) {
        glm::vec3 spherical_forward = cartesian_to_spherical(m_camera.forward);
        spherical_forward.z -= delta_time * m_sensitivity;
        m_camera.forward = spherical_to_cartesian(spherical_forward);
    }

    if (Input::is_down(Keyboard::Right)) {
        glm::vec3 spherical_forward = cartesian_to_spherical(m_camera.forward);
        spherical_forward.y += delta_time * m_sensitivity;
        m_camera.forward = spherical_to_cartesian(spherical_forward);
    }

    if (Input::is_down(Keyboard::Left)) {
        glm::vec3 spherical_forward = cartesian_to_spherical(m_camera.forward);
        spherical_forward.y -= delta_time * m_sensitivity;
        m_camera.forward = spherical_to_cartesian(spherical_forward);
    }



    // Update camera direction
    if (Input::is_down(Mouse::Right)) {
        glm::vec3 spherical_forward = cartesian_to_spherical(m_camera.forward);
        glm::vec2 mouse_delta = Input::mouse_delta() * delta_time * m_sensitivity;
        spherical_forward.y -= mouse_delta.x;
        spherical_forward.z += mouse_delta.y;
        m_camera.forward = spherical_to_cartesian(spherical_forward);
    }
    
}