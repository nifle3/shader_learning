#include <format>

#include "gl_wrapper.hpp"
#include "logs.hpp"

GLShader::~GLShader() {
  if (this->object != 0) {
    LOG_INFO(std::format("Delete shader {}", this->object));
    glDeleteShader(this->object);
  }
}

GLProgram::~GLProgram() {
  if (this->object != 0) {
    LOG_INFO(std::format("Delete program {}", this->object));
    glDeleteProgram(this->object);
  }
}

GLProgram::GLProgram(GLProgram &&other) : GLObject(other.object) {
  other.object = 0;
}

GLProgram &GLProgram::operator=(GLProgram &&other) noexcept {
  if (this != &other) {
    if (this->object != 0) {
      LOG_INFO(std::format("Delete program {}", this->object));
      glDeleteShader(this->object);
    }

    this->object = other.object;
    other.object = 0;
  }

  return *this;
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

  LOG_INFO("Program created");
  return GLProgram(program);
}

GLVBO::~GLVBO() {
  if (this->object != 0) {
    LOG_INFO(std::format("delete vbo {}", this->object));
    glDeleteBuffers(1, &this->object);
  }
}

auto GLVBO::create() -> GLVBO {
  GLuint vbo;
  glGenBuffers(1, &vbo);
  return GLVBO(vbo);
}

auto GLVAO::create() -> GLVAO {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  return GLVAO(vao);
}

GLVAO::~GLVAO() {
  if (this->object != 0) {
    LOG_INFO(std::format("delete vao {}", this->object));
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
    LOG_INFO(std::format("delete ebo {}", this->object));
    glDeleteBuffers(1, &this->object);
  }
}
