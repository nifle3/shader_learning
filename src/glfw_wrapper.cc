#include "glfw_wrapper.hpp"

#include <format>
#include <tuple>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#include "gl_wrapper.hpp"

Window::~Window() {
  if (this->window_) {
    glfwDestroyWindow(this->window_);
  }
}

auto Window::operator*() noexcept -> GLFWwindow * { return this->window_; }

auto Window::create(int width, int height, const std::string &name) -> Window {
  const auto window =
      glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

  if (window == nullptr) {
    throw "Cannot create window";
  }

  return Window(window);
}

auto Window::get_fbsize_hw() const -> std::tuple<int, int> {
  int width, heigth;
  glfwGetFramebufferSize(this->window_, &width, &heigth);
  return std::make_tuple(width, heigth);
}

Program::~Program() { glfwTerminate(); }

auto Program::create() -> Program {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    throw -1;
  }

  return Program();
}

auto Program::run(const std::string &vertex, const std::string &fragment) const
    -> void {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, GLFW_TRUE);

  auto window = Window::create(1280, 720, "Opengl learning");

  glfwSetKeyCallback(*window, key_callback);
  glfwMakeContextCurrent(*window);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    throw "Failed to initialize GLAD";
  }

  const auto [fbheigth, fbwidth] = window.get_fbsize_hw();
  glViewport(0, 0, fbheigth, fbwidth);
  glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(*window)) {
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(*window);
    glfwPollEvents();
  }
}

auto framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width,
                               int height) -> void {
  glViewport(0, 0, width, height);
  spdlog::debug("Change viewport");
}

auto error_callback(int err, const char *msg) noexcept -> void {
  spdlog::error("error code {}\nmessage {}", err, msg);
}

auto key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode,
                  int action, [[maybe_unused]] int mods) noexcept -> void {
  static auto is_wireframe = false;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    return;
  }

  if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    glPolygonMode(GL_FRONT_AND_BACK, is_wireframe ? GL_FILL : GL_LINE);
    is_wireframe = !is_wireframe;
    return;
  }
}
