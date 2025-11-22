#pragma once
#include <string>

#include <glad/glad.h>

#include "logs.hpp"

class GLObject {
protected:
  GLuint object;
  GLObject(GLuint id) : object(id) {}

public:
  virtual ~GLObject() = default;

  constexpr auto operator*() const noexcept -> GLuint { return this->object; }
};

class GLShader : public GLObject {
private:
  GLShader(GLuint id) : GLObject(id) {}

public:
  GLShader(const GLShader &other) = delete;
  auto operator=(const GLShader &other) = delete;

  GLShader(GLShader &&other);
  auto operator=(GLShader &&other) noexcept -> GLShader &;

  ~GLShader();

  template <int type>
    requires(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER)
  static auto compile_shader_from_text(const std::string &shader_text)
      -> GLShader {
    const auto shader = glCreateShader(type);
    const auto c_str_text_shader = shader_text.c_str();
    glShaderSource(shader, 1, &c_str_text_shader, nullptr);
    glCompileShader(shader);
    LOG_INFO("shader compiled");
    return GLShader(shader);
  }
};

struct CompiledShaders {
  GLShader vertex;
  GLShader fragment;

  CompiledShaders(GLShader &&v, GLShader &&f) noexcept
      : vertex(std::move(v)), fragment(std::move(f)) {}
};

struct TextShaders {
  std::string vertex;
  std::string fragment;
};

auto compile_shaders(const TextShaders &text_shaders) -> CompiledShaders;

class GLProgram : public GLObject {
private:
  GLProgram(GLuint id) : GLObject(id) {}

public:
  GLProgram(const GLProgram &other) = delete;
  auto operator=(const GLShader &other) = delete;

  GLProgram(GLProgram &&other);
  auto operator=(GLProgram &&other) noexcept -> GLProgram &;

  ~GLProgram();

  static auto create_program(const CompiledShaders &compiled_shaders)
      -> GLProgram {
    const auto program = glCreateProgram();
    glAttachShader(program, *compiled_shaders.vertex);
    glAttachShader(program, *compiled_shaders.fragment);
    LOG_INFO("Program created");
    return GLProgram(program);
  }
};
