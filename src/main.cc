#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <glad/glad.h>
#include <iostream>

auto do_main_loop() noexcept -> int {
  if (!glfwInit()) {
    std::cerr << "GLFW init failed\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  auto window =
      glfwCreateWindow(1280, 720, "GLFW + Modern C++", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  auto red = 1.0f;
  auto blue = 4.0f;
  auto green = 6.0f;

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    auto r = std::div(red, 255);
    auto g = std::div(green, 255);
    auto b = std::div(blue, 255);

    glClearColor(r.rem / 255.0f, g.rem / 255.0f, b.rem / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
    red++;
    blue++;
    green++;
  }

  glfwDestroyWindow(window);
  return 0;
}

int main() {
  auto status_code = do_main_loop();
  glfwTerminate();
  return status_code;
}
