#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:

    // Global camera up direction: Y axis.
    static constexpr glm::vec3 UP{0.0f, 1.0f, 0.0f};

    Camera(int window_width, int window_height);

    // Getter methods.
    const glm::vec3& position() const;
    const glm::mat4& view();
    const glm::mat4& projection() const;

    // Move camera.
    void moveForwards();
    void moveBackwards();
    void moveRight();
    void moveLeft();

    // Turn camera by input angles.
    void turn(float deltaPitch, float deltaYaw);

private:

    // Update camera orientation from pitch and yaw.
    void _updateOrientation();
    // Update View matrix from camera's orientation and position.
    void _updateView();

    // Position and orientation in global coordinates.
    // Orientation is the following matrix, with orthonormal Ex, Ey and Ez.
    // | .  | .  | .  | 0  |
    // | Ex | Ey | Ez | 0  |
    // | .  | .  | .  | 0  |
    // | 0  | 0  | 0  | 1  |
    glm::vec3 position_;
    glm::mat4 orientation_;

    // Transformations.
    glm::mat4 view_;
    glm::mat4 projection_;

    // Pitch = Camera "up and down" angle, in degrees.
    // Yaw   = Camera "left and right" angle, in degrees.
    float pitch_;
    float yaw_;

    // Vertical field of view, in radians.
    float fov_y_;
    float speed_;
};

#endif // CAMERA_HPP
