#include "gl_wrapper.hpp"
#include "glfw_wrapper.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

template <int type>
  requires(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER)
auto compile_shader(const std::string &text_shader) -> GLuint {
  const auto shader = glCreateShader(type);
  const auto c_str_text_shader = text_shader.c_str();
  glShaderSource(shader, 1, &c_str_text_shader, NULL);
  glCompileShader(shader);

  return shader;
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
    auto gl_program = GLProgram::create_program(compiled_shaders);
    program.main_loop(std::move(gl_program));
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
