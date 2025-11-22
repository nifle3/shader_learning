#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <memory>

#include "gl_wrapper.hpp"

auto delete_glfw_window(GLFWwindow *window) -> void;
auto error_callback(int err, const char *msg) noexcept -> void;
auto key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode,
                  int action, [[maybe_unused]] int mods) noexcept -> void;

class GLFWProgram {
private:
  std::unique_ptr<GLFWwindow, decltype(&delete_glfw_window)> window;

public:
  GLFWProgram(
      std::unique_ptr<GLFWwindow, decltype(&delete_glfw_window)> &&window)
      : window(std::move(window)) {}

  ~GLFWProgram() { glfwTerminate(); }
  auto main_loop(GLProgram &&program) -> void;
};

auto create_glfwprogram() -> GLFWProgram;
