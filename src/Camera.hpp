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

    // Get position and orientation by reference.
    const glm::vec3& position() const;
    const glm::mat4& orientation() const;

    // Get transformations by reference.
    const glm::mat4& view() const;
    const glm::mat4& projection() const;

    // Move camera.
    void moveForwards();
    void moveBackwards();
    void moveRight();
    void moveLeft();

    // Update View matrix.
    // This method should be called right before rendering.
    void updateView();

    void setPosition(const glm::vec3& pos);

    // Update camera orientation to follow the target.
    void lookAt(const glm::vec3& target);

private:

    // Position and orientation in global coordinates.
    // Orientation is the following matrix, with normalized Ex, Ey and Ez.
    // | .  | .  | .  | 0  |
    // | Ex | Ey | Ez | 0  |
    // | .  | .  | .  | 0  |
    // | 0  | 0  | 0  | 1  |
    glm::vec3 position_;
    glm::mat4 orientation_;

    // Transformations.
    glm::mat4 view_;
    glm::mat4 projection_;

    // Vertical field of view, in radians.
    float fov_y_;
    float speed_;
};

#endif // CAMERA_HPP
