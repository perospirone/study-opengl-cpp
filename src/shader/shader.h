#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
  unsigned int ID;

  // Constructor declaration
  Shader(const char *vertexPath, const char *fragmentPath);

  // Public interface
  void use() const;

  // Uniform setters
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
  // Private helper function
  void checkCompileErrors(unsigned int shader, const std::string &type) const;
};
