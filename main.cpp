#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdio>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "shader_s.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

void process_input(GLFWwindow *window);

//const char *vertex_shader = "#version 330 core\n"
                            //"layout (location = 0) in vec3 a_pos;"
                            //"layout (location = 1) in vec3 a_color;"
                            //"out vec3 our_color;"
                            //"void main() {"
                            //"  gl_Position = vec4(a_pos, 1.0);"
                            //"  our_color = a_color;"
                            //"}";

//const char *fragment_shader = "#version 330 core\n"
                              //"out vec4 frag_colour;"
                              //"in vec3 our_color;"
                              //"void main() {"
                              //"  frag_colour = vec4(our_color, 1.0);"
                              //"}";

int main() {
  if (!glfwInit()) {
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int window_width = 800;
  int window_height = 600;

  printf("window width %i\n", window_width);
  printf("window height %i\n", window_height);

  GLFWwindow *window =
      glfwCreateWindow(window_width, window_height, "learn-opengl", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1;
  }

  glViewport(0, 0, window_width, window_height);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  //float triangle[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};

  //float square[] = {-0.5f, 0.5f,  0.0f, 0.5f,  0.5f,  0.0f,
                    //0.5f,  -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};


  float triangle[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
  }; // idk why the opengl tutorial put color inside vertices array and no is a other array

  float texCoords[] = {
      0.0f, 0.0f,
      1.0f, 0.0f,
      0.5f, 1.0f
  };

  // texture config
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  int width, height, nrChannels;
  unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0); 


  unsigned int vao1, vbo1;

  glGenVertexArrays(1, &vao1);
  glGenBuffers(1, &vbo1);

  glBindVertexArray(vao1);
  glBindBuffer(GL_ARRAY_BUFFER, vbo1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);

  Shader ourShader("vertex.glsl", "fragment.glsl");

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    process_input(window);
    ourShader.use();

    // render triangle
    glBindVertexArray(vao1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // render square
    //glBindVertexArray(vao2);
    //glDrawArrays(GL_LINE_LOOP, 0, 4); // Use GL_TRIANGLE_FAN for filled square

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  printf("key: %s\n", glfwGetKeyName(key, scancode));
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    printf("key E");
  }
}

void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    printf("press r\n");
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  }
}
