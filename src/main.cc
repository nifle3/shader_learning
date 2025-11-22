#include <string>

#include "file_utils.hpp"
#include "glfw_wrapper.hpp"
#include "logs.hpp"

auto main() -> int {
  auto status_code = 0;
  try {
    const auto shaders = get_shaders(); // vertex fragment
    const auto program = Program::create();
    program.run(std::get<0>(shaders), std::get<1>(shaders));
  } catch (int err_status_code) {
    status_code = err_status_code;
  } catch (const std::string &err) {
    LOG_ERROR(err);
    status_code = 1;
  } catch (...) {
    LOG_ERROR("Unexpected error");
    status_code = 1;
  }
  return status_code;
}
