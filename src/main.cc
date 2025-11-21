#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <format>
#include <glad/glad.h>
#include <iostream>

void error_callback(int err, const char *msg) noexcept {
  std::cerr << std::format("error code {}\nmessage {}", err, msg) << std::endl;
}

void key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode,
                  int action, [[maybe_unused]] int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

auto setup_glfw() noexcept -> int {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  auto window =
      glfwCreateWindow(1280, 720, "GLFW + Modern C++", nullptr, nullptr);
  if (!window) {
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(1, 1, 1, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  return 0;
}

auto main() -> int {
  auto status_code = setup_glfw();
  glfwTerminate();
  return status_code;
}
