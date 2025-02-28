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

  float triangle[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};

  float square[] = {-0.5f, 0.5f,  0.0f, 0.5f,  0.5f,  0.0f,
                    0.5f,  -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};

  unsigned int vao1, vbo1;

  glGenVertexArrays(1, &vao1);
  glGenBuffers(1, &vbo1);

  glBindVertexArray(vao1);
  glBindBuffer(GL_ARRAY_BUFFER, vbo1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glBindVertexArray(0);

  unsigned int vao2, vbo2;
  glGenVertexArrays(1, &vao2);
  glGenBuffers(1, &vbo2);

  glBindVertexArray(vao2);
  glBindBuffer(GL_ARRAY_BUFFER, vbo2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glBindVertexArray(0);

  unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);

  unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vs);
  glAttachShader(shader_program, fs);
  glLinkProgram(shader_program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    process_input(window);
    glUseProgram(shader_program);

    // Render Triangle
    glBindVertexArray(vao1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Render Square
    glBindVertexArray(vao2);
    glDrawArrays(GL_LINE_LOOP, 0, 4); // Use GL_TRIANGLE_FAN for filled square

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
