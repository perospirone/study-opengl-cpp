#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera {
public:
  // Static constants
  static const float YAW;
  static const float PITCH;
  static const float SPEED;
  static const float SENSITIVITY;
  static const float ZOOM;

  // Camera attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  // Euler angles
  float Yaw;
  float Pitch;

  // Camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  // Constructors
  Camera(glm::vec3 position = glm::vec3(0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);

  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  // Public interface
  glm::mat4 GetViewMatrix() const;
  void ProcessKeyboard(Camera_Movement direction, float deltaTime);
  void ProcessMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true);
  void ProcessMouseScroll(float yoffset);

private:
  void updateCameraVectors();
};
