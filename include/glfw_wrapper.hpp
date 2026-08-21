#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
private:
  GLFWwindow *window_;

  Window(GLFWwindow *window) : window_(window) {}

public:
  auto operator*() noexcept -> GLFWwindow *;
  ~Window();

  static auto create(int width, int height, const std::string &name) -> Window;
};

class Program {
private:
  Program() = default;

public:
  ~Program();

  static auto create() -> Program;
  auto run(const std::string &vertex, const std::string &fragment) const
      -> void;
};

auto framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width,
                               int height) -> void;

auto error_callback(int err, const char *msg) noexcept -> void;

auto key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode,
                  int action, [[maybe_unused]] int mods) noexcept -> void;