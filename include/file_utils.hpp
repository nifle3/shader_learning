#pragma once

#include <filesystem>
#include <string>
#include <tuple>

namespace fs = std::filesystem;

auto read_file(const fs::path &path) -> std::string;
auto add_path(const fs::path &base, std::string_view filename) -> fs::path;
auto get_shaders() -> std::tuple<std::string, std::string>;
