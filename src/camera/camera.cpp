#include "camera.h"
#include <iostream> // For error reporting if needed

// Initialize static constants
const float Camera::YAW = -90.0f;
const float Camera::PITCH = 0.0f;
const float Camera::SPEED = 2.5f;
const float Camera::SENSITIVITY = 0.1f;
const float Camera::ZOOM = 45.0f;

// Constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
  Position = position;
  WorldUp = up;
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
}

// Constructor with scalars
Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
               float upZ, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
  Position = glm::vec3(posX, posY, posZ);
  WorldUp = glm::vec3(upX, upY, upZ);
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
}

// View matrix calculation
glm::mat4 Camera::GetViewMatrix() const {
  return glm::lookAt(Position, Position + Front, Up);
}

// Keyboard input handling
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = MovementSpeed * deltaTime;

  switch (direction) {
  case FORWARD:
    Position += Front * velocity;
    break;
  case BACKWARD:
    Position -= Front * velocity;
    break;
  case LEFT:
    Position -= Right * velocity;
    break;
  case RIGHT:
    Position += Right * velocity;
    break;
  case UP:
    Position += WorldUp * velocity; // Use WorldUp for vertical movement
    break;
  case DOWN:
    Position -= WorldUp * velocity;
    break;
  }
}

// Mouse movement handling
void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  bool constrainPitch) {
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  if (constrainPitch) {
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
  }

  updateCameraVectors();
}

// Mouse scroll handling
void Camera::ProcessMouseScroll(float yoffset) {
  Zoom -= yoffset;
  if (Zoom < 1.0f)
    Zoom = 1.0f;
  if (Zoom > 45.0f)
    Zoom = 45.0f;
}

// Private helper to update camera vectors
void Camera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  front.y = sin(glm::radians(Pitch));
  front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

  Front = glm::normalize(front);
  Right = glm::normalize(glm::cross(Front, WorldUp));
  Up = glm::normalize(glm::cross(Right, Front));
}
