#include "file_utils.hpp"

#include <format>
#include <fstream>
#include <sstream>
#include <tuple>

auto read_file(const fs::path &path) -> std::string {
  std::ifstream file(path);
  if (!file) {
    throw std::format("Cannot open {} file", path.string());
  }

  std::ostringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

auto add_path(const fs::path &base, std::string_view filename) {
  const auto path = base / filename;
  if (!fs::exists(path)) {
    throw std::format("Path {} is not exists", path.string());
  }

  return path;
}

auto get_shaders() -> std::tuple<std::string, std::string> {
  const fs::path base = "./";
  const auto shader_path = add_path(base, "shaders");
  const auto vertex_shader_path = add_path(shader_path, "basic.vert");
  const auto fragment_shader_path = add_path(shader_path, "basic.frag");

  const auto vertex_shader = read_file(vertex_shader_path);
  const auto fragment_shader = read_file(fragment_shader_path);

  return std::make_tuple(vertex_shader, fragment_shader);
}
