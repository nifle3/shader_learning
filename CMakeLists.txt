cmake_minimum_required(VERSION 4.3)
project(shaders_learning VERSION 0.0.1 LANGUAGES C CXX)
add_executable(shaders_learning)

find_package(OpenGL REQUIRED)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glad)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/imgui)

target_link_libraries(shaders_learning PRIVATE
  glfw
  glad
  glm
  OpenGL::GL
)

target_compile_options(shaders_learning PRIVATE 
  -Wall 
  -Wextra 
  -Wnon-virtual-dtor 
  -Wcast-align 
  -Wconversion 
  -Werror 
  -Wpedantic
  $<$<CONFIG:Debug>:-fsanitize=address,undefined>
  $<$<CONFIG:Debug>:-g>
  $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)
target_link_options(shaders_learning PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

target_include_directories(shaders_learning PRIVATE include)

target_sources(shaders_learning PRIVATE
  src/file_utils.cc
  src/gl_wrapper.cc
  src/glfw_wrapper.cc
  src/main.cc
)

file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
