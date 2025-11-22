#include "gl_wrapper.hpp"
#include "logs.hpp"

GLShader::~GLShader() {
  if (this->object != 0) {
    LOG_INFO(std::format("Delete shader {}", this->object));
    glDeleteShader(this->object);
  }
}

GLShader::GLShader(GLShader &&other) : GLObject(other.object) {
  other.object = 0;
}

GLShader &GLShader::operator=(GLShader &&other) noexcept {
  if (this != &other) {
    if (this->object != 0) {
      LOG_INFO(std::format("Delete shader {}", this->object));
      glDeleteShader(this->object);
    }

    this->object = other.object;
    other.object = 0;
  }

  return *this;
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

auto compile_shaders(const TextShaders &text_shaders) -> CompiledShaders {
  auto compiled_fragment_shader =
      GLShader::compile_shader_from_text<GL_FRAGMENT_SHADER>(
          text_shaders.fragment);
  auto compiled_vertex_shader =
      GLShader::compile_shader_from_text<GL_VERTEX_SHADER>(text_shaders.vertex);
  LOG_INFO("shader compiled");
  return CompiledShaders{std::move(compiled_vertex_shader),
                         std::move(compiled_fragment_shader)};
}
