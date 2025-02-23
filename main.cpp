#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

void process_input(GLFWwindow *window);

const char *vertex_shader = "#version 330 core\n"
                            "in vec3 vp;"
                            "void main() {"
                            "  gl_Position = vec4( vp, 1.0 );"
                            "}";

const char *fragment_shader = "#version 330 core\n"
                              "out vec4 frag_colour;"
                              "void main() {"
                              "  frag_colour = vec4( 0.5, 0.0, 0.5, 1.0 );"
                              "}";

int main() {
  if (!glfwInit()) {
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int width = 800;
  int height = 600;

  printf("window width %i\n", width);
  printf("window height %i\n", height);

  GLFWwindow *window =
      glfwCreateWindow(width, height, "learn-opengl", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1;
  }

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  float points[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
  //float points[] = {-0.5, 0.5, 0.0f, 0.5f, -0.5, 0.0f, 0.5, -0.5, 0.0f, -0.5f, -0.5f, 0.0f};

  unsigned int vbo = 0; // vertex buffer object
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) * sizeof(float), points, GL_STATIC_DRAW);

  unsigned int vao = 0; // vertex array object
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, fs);
  glAttachShader(shader_program, vs);
  glLinkProgram(shader_program);

  glfwSetKeyCallback(window, key_callback);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    process_input(window);

    // Put the shader program, and the VAO, in focus in OpenGL's state machine.
    glUseProgram(shader_program);
    glBindVertexArray(vao);

    // Draw points 0-3 from the currently bound VAO with current in-use shader.
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
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
