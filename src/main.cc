#include "glfw_wrapper.hpp"
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

struct TextShaders {
  std::string vertex;
  std::string fragment;
};

struct CompiledShaders {
  GLuint vertex;
  GLuint fragment;
};

template <int type>
  requires(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER)
auto compile_shader(const std::string &text_shader) -> GLuint {
  const auto shader = glCreateShader(type);
  const auto c_str_text_shader = text_shader.c_str();
  glShaderSource(shader, 1, &c_str_text_shader, NULL);
  glCompileShader(shader);

  return shader;
}

auto compile_shaders(const TextShaders &text_shaders) -> CompiledShaders {
  const auto compiled_fragment_shader =
      compile_shader<GL_FRAGMENT_SHADER>(text_shaders.fragment);
  const auto compiled_vertex_shader =
      compile_shader<GL_VERTEX_SHADER>(text_shaders.vertex);

  return {compiled_vertex_shader, compiled_fragment_shader};
}

auto setup_shader_program(const CompiledShaders &compiled_shaders) -> GLuint {
  const auto program = glCreateProgram();
  glAttachShader(program, compiled_shaders.vertex);
  glAttachShader(program, compiled_shaders.fragment);
  return program;
}

auto get_shader_from_file(const fs::path &path) -> std::string {
  std::ifstream file(path);
  if (!file) {
    throw std::format("Cannot open {} file", path.string());
  }

  std::ostringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

auto get_shaders() -> TextShaders {
  const fs::path base = "./";
  const auto shader_path = base / "shaders";
  if (!fs::exists(shader_path)) {
    throw std::string("shaders folder is not exists");
  }

  const auto vertex_shader_path = shader_path / "basic.vert";
  const auto fragment_shader_path = shader_path / "basic.frag";

  if (!fs::exists(vertex_shader_path)) {
    throw std::format("vertex shader is not exists with path {}",
                      vertex_shader_path.string());
  }

  if (!fs::exists(fragment_shader_path)) {
    throw std::format("fragment shader is not exists with path {}",
                      fragment_shader_path.string());
  }

  const auto vertex_shader = get_shader_from_file(vertex_shader_path);
  const auto fragment_shader = get_shader_from_file(fragment_shader_path);

  return {std::move(vertex_shader), std::move(fragment_shader)};
}

auto main() -> int {
  auto status_code = 0;
  try {
    auto program = create_glfwprogram();
    const auto shader = get_shaders();
    const auto compiled_shaders = compile_shaders(shader);
    const auto _ = setup_shader_program(compiled_shaders);
    program.main_loop();
  } catch (int err_status_code) {
    status_code = err_status_code;
  } catch (const std::string &err) {
    std::cerr << std::format("error: {}", err) << std::endl;
    status_code = 1;
  } catch (...) {
    std::cerr << "Unexpected error";
    status_code = 1;
  }

  return status_code;
}
