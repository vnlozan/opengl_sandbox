#pragma once

#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// An abstract camera class that processes input and calculates the corresponding Euler Angles,
// Vectors and Matrices for use in OpenGL
class Camera {
public:
    // Defines several possible options for camera movement. 
    // Used as abstraction to stay away from window-system specific input methods
    enum class Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
    static const float YAW;
    static const float PITCH;
    static const float SPEED;
    static const float SENSITIVITY;
    static const float ZOOM;

    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    // constructor with vectors
    Camera(
        glm::vec3 position = glm::vec3( 0.0f, 0.0f, 0.0f ),
        glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f ),
        float yaw = Camera::YAW,
        float pitch = Camera::PITCH
    );
    // constructor with scalar values
    Camera( float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch );
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
    // processes input received from any keyboard-like input system.
    // Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard( Camera::Movement direction, float deltaTime );
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement( float xoffset, float yoffset, GLboolean constrainPitch = true );
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll( float yoffset );
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};