#include <string>

#include <spdlog/spdlog.h>

#include "file_utils.hpp"
#include "glfw_wrapper.hpp"

auto main() -> int {
  auto status_code = 0;

  try {
    const auto shaders = get_shaders();
    const auto program = Program::create();
    program.run(std::get<0>(shaders), std::get<1>(shaders));
  } catch (const std::exception &exception) {
    spdlog::error("{}", exception.what());
    status_code = 1;
  } catch (int err_status_code) {
    status_code = err_status_code;
  } catch (const std::string &err) {
    spdlog::error("{}", err);
    status_code = 1;
  } catch (...) {
    spdlog::error("Unexpected error");
    status_code = 1;
  }

  return status_code;
}
