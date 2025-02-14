#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void process_input(GLFWwindow* window);

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
      glfwCreateWindow(width, height, "Hello World", NULL, NULL);
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


  glfwSetKeyCallback(window, key_callback);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Render here
    //glClear(GL_COLOR_BUFFER_BIT);

    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    process_input(window);

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  printf("key: %s\n", glfwGetKeyName(key, scancode));
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    printf("key E");
  }
}

void process_input(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    printf("press r\n");
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  }
}
