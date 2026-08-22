#pragma once

#include <string>

#include <glad/glad.h>
#include <spdlog/spdlog.h>

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

  auto operator=(GLShader &&other) = delete;
  GLShader(GLShader &&other) = delete;

  ~GLShader();

  template <int type>
    requires(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER)
  static auto compile_shader_from_text(const std::string &shader_text)
      -> GLShader {
    const auto shader = glCreateShader(type);
    const auto c_str_text_shader = shader_text.c_str();
    glShaderSource(shader, 1, &c_str_text_shader, nullptr);
    glCompileShader(shader);

    char err[512] = {};
    int success{1};

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, NULL, err);
      throw std::string(err);
    }

    spdlog::info("shader {} compiled", shader);
    return GLShader(shader);
  }
};

class GLProgram : public GLObject {
private:
  GLProgram(GLuint id) : GLObject(id) {}

public:
  GLProgram(const GLProgram &other) = delete;
  auto operator=(const GLShader &other) = delete;

  GLProgram(GLProgram &&other);
  auto operator=(GLProgram &&other) noexcept -> GLProgram &;

  ~GLProgram();

  static auto create(const std::string &vert, const std::string &fragment)
      -> GLProgram;
};

class GLVBO : public GLObject {
private:
  GLVBO(GLuint id) : GLObject(id) {}

public:
  ~GLVBO();
  static auto create() -> GLVBO;
};

class GLVAO : public GLObject {
private:
  GLVAO(GLuint id) : GLObject(id) {}

public:
  ~GLVAO();
  static auto create() -> GLVAO;
};

class GLEBO : public GLObject {
private:
  GLEBO(GLuint id) : GLObject(id) {}

public:
  ~GLEBO();
  static auto create() -> GLEBO;
};
