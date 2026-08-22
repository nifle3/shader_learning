#include <spdlog/spdlog.h>
#include <string_view>

#include "gl_wrapper.hpp"

GLShader::~GLShader() {
  if (this->object != 0) {
    spdlog::info("Delete shader {}", this->object);
    glDeleteShader(this->object);
    this->object = 0;
  }
}

GLProgram::~GLProgram() {
  if (this->object != 0) {
    spdlog::info("Delete program {}", this->object);
    glDeleteProgram(this->object);
    this->object = 0;
  }
}

auto GLProgram::create(const std::string &vertex, const std::string &fragment)
    -> GLProgram {
  const auto vertex_shader =
      GLShader::compile_shader_from_text<GL_VERTEX_SHADER>(vertex);

  const auto fragment_shader =
      GLShader::compile_shader_from_text<GL_FRAGMENT_SHADER>(fragment);

  const auto program = glCreateProgram();
  glAttachShader(program, *fragment_shader);
  glAttachShader(program, *vertex_shader);
  glLinkProgram(program);

  int success{1};
  char err[512] = {};

  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, err);
    throw std::string(err);
  }

  spdlog::info("Program created");
  return GLProgram(program);
}

auto GLProgram::use() const -> void {
  glUseProgram(this->object);
}

auto GLProgram::set_bool(const std::string& name, bool value) const -> void {
  glUniform1i(glGetUniformLocation(this->object, name.c_str()), static_cast<int>(value)); 
}

auto GLProgram::set_int(const std::string& name, int value) const -> void {
  glUniform1i(glGetUniformLocation(this->object, name.c_str()), value); 
}


auto GLProgram::set_float(const std::string& name, float value) const -> void {
  glUniform1f(glGetUniformLocation(this->object, name.c_str()), value); 
}


auto GLVBO::create() -> GLVBO {
  GLuint vbo;
  glGenBuffers(1, &vbo);
  return GLVBO(vbo);
}

GLVBO::~GLVBO() {
  if (this->object != 0) {
    spdlog::info("delete vbo {}", this->object);
    glDeleteBuffers(1, &this->object);
    this->object = 0;
  }
}

auto GLVAO::create() -> GLVAO {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  return GLVAO(vao);
}

GLVAO::~GLVAO() {
  if (this->object != 0) {
    spdlog::info("delete vao {}", this->object);
    glDeleteVertexArrays(1, &this->object);
  }
}

auto GLEBO::create() -> GLEBO {
  GLuint ebo;
  glGenBuffers(1, &ebo);
  return GLEBO(ebo);
}

GLEBO::~GLEBO() {
  if (this->object != 0) {
    spdlog::info("delete ebo {}", this->object);
    glDeleteBuffers(1, &this->object);
    this->object = 0;
  }
}
