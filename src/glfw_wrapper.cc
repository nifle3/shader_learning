#include "glfw_wrapper.hpp"

#include <format>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "logs.hpp"
#include <gl_wrapper.hpp>

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

  auto window = Window::create(1280, 720, "Opengl learning");

  glfwSetKeyCallback(*window, key_callback);
  glfwMakeContextCurrent(*window);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    throw "Failed to initialize GLAD";
  }

  glViewport(0, 0, 1280, 720);
  glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  auto program = GLProgram::create(vertex, fragment);
  auto VBO = GLVBO::create();
  auto VAO = GLVAO::create();

  glBindVertexArray(*VAO);

  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        static_cast<void *>(0));
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(*window)) {
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(*program);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(*window);
    glfwPollEvents();
  }
}

auto framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width,
                               int height) -> void {
  glViewport(0, 0, width, height);
  LOG_DEBUG("Change viewport");
}

auto error_callback(int err, const char *msg) noexcept -> void {
  LOG_ERROR(std::format("error code {}\nmessage {}", err, msg));
}

auto key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode,
                  int action, [[maybe_unused]] int mods) noexcept -> void {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}
