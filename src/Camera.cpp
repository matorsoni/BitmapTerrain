#include "Camera.hpp"

#include <glm/glm.hpp>   // for glm::radians, glm::normalize, glm::cross...
#include <glm/gtc/matrix_transform.hpp>   // for glm::perspective

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::radians;
using glm::cross;
using glm::normalize;

Camera::Camera(int window_width, int window_height):
    position_(vec3(-10.0f, 4.0f, 0.0f)),
    orientation_(mat4(1.0f)),
    view_(mat4(1.0f)),
    projection_(mat4(1.0f)),
    pitch_(-30.0f),
    yaw_(0.0f),
    fov_y_(radians(45.0f)),
    speed_(0.1f)
{
    assert(window_width > 0);
    assert(window_height > 0);

    // Define perspective constants.
    const float near_plane = 0.1f;
    const float far_plane = 100.0f;
    const float screen_aspect_ratio = static_cast<float>(window_width) / window_height;

    // Build perspective projection matrix.
    projection_ = glm::perspective(fov_y_, screen_aspect_ratio, near_plane, far_plane);
}

const vec3& Camera::position() const
{
    return position_;
}

const mat4& Camera::view()
{
    _updateView();
    return view_;
}

const mat4& Camera::projection() const
{
    return projection_;
}

void Camera::moveForwards()
{
    position_ -= speed_ * vec3(orientation_[2]);
}

void Camera::moveBackwards()
{
    position_ += speed_ * vec3(orientation_[2]);
}

void Camera::moveRight()
{
    position_ += speed_ * vec3(orientation_[0]);
}

void Camera::moveLeft()
{
    position_ -= speed_ * vec3(orientation_[0]);
}

void Camera::turn(float deltaPitch, float deltaYaw)
{
    static constexpr float lower_bound = -85.0f;
    static constexpr float upper_bound = 85.0f;

    pitch_ += deltaPitch;
    yaw_ += deltaYaw;

    if (pitch_ > upper_bound)
        pitch_ = upper_bound;
    else if (pitch_ < lower_bound)
        pitch_ = lower_bound;

    _updateOrientation();
}

void Camera::_updateOrientation()
{
    // Define camera's look direction.
    float x = cosf(radians(pitch_)) * sinf(radians(yaw_));
    float y = sinf(radians(pitch_));
    float z = cosf(radians(pitch_)) * cosf(radians(yaw_));
    vec3 look(x, y, z);

    // Construct camera's orthonormal frame.
    vec3 cam_x = normalize(cross(look, UP));
    vec3 cam_y = cross(cam_x, look);
    vec3 cam_z = -look;

    // Update orientation matrix.
    orientation_[0] = vec4(cam_x, 0.0f);
    orientation_[1] = vec4(cam_y, 0.0f);
    orientation_[2] = vec4(cam_z, 0.0f);
    assert(orientation_[3] == vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void Camera::_updateView()
{
    // View matrix is the inverse of:
    // | .  | .  | .  | .  | -1          | .  | Ex | .  | 0  |     | 1  | 0  | 0  | .  |
    // | Ex | Ey | Ez | P  |      =      | .  | Ey | .  | 0  |  *  | 0  | 1  | 0  | -P |
    // | .  | .  | .  | .  |             | .  | Ez | .  | 0  |     | 0  | 0  | 1  | .  |
    // | 0  | 0  | 0  | 1  |             | 0  | 0  | 0  | 1  |     | 0  | 0  | 0  | 1  |
    // P being the camera's position vector.
    // Ex, Ey and Ex being the X, Y, Z unit vectors of the camera's orthonormal frame.

    // Inverse translation matrix.
    mat4 inv_translation = mat4(1.0f);
    inv_translation[3] = vec4(-position_, 1.0f);

    // Update view.
    view_ = glm::transpose(orientation_) * inv_translation;
}
