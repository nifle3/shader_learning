#include <format>
#include <iostream>

#include "glfw_wrapper.hpp"

#include <GLFW/glfw3.h>
#include <memory>

auto delete_glfw_window(GLFWwindow *window) -> void {
  if (window != nullptr) {
    glfwDestroyWindow(window);
  }
}

auto error_callback(int err, const char *msg) noexcept -> void {
  std::cerr << std::format("error code {}\nmessage {}", err, msg) << std::endl;
}

auto key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode,
                  int action, [[maybe_unused]] int mods) noexcept -> void {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

auto create_glfwprogram() -> GLFWProgram {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    throw -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  auto window = std::unique_ptr<GLFWwindow, decltype(&delete_glfw_window)>(
      glfwCreateWindow(1280, 720, "GLFW + Modern C++", nullptr, nullptr),
      delete_glfw_window);

  if (!window.get()) {
    throw -1;
  }

  glfwSetKeyCallback(window.get(), key_callback);
  glfwMakeContextCurrent(window.get());

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    throw -1;
  }

  glfwSwapInterval(1);
  return GLFWProgram(std::move(window));
}

auto GLFWProgram::main_loop() -> void {
  while (!glfwWindowShouldClose(this->window.get())) {
    glClearColor(1, 1, 1, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(this->window.get());
    glfwPollEvents();
  }
}
