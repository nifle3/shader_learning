cmake_minimum_required(VERSION 3.23)
project(shaders_learning VERSION 0.0.1 LANGUAGES C CXX)
add_executable(shaders_learning)

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

add_library(glad STATIC third_party/glad/src/glad.c)
target_include_directories(glad PUBLIC third_party/glad/include)
if(UNIX AND NOT APPLE)
  target_link_libraries(glad PRIVATE dl)
endif()

find_package(OpenGL REQUIRED)

target_link_libraries(shaders_learning PRIVATE
  glfw
  glad
  OpenGL::GL
)

target_compile_options(shaders_learning PRIVATE 
  -Wall 
  -Wextra 
  -Wnon-virtual-dtor 
  -Wcast-align 
  -Wold-style-cast 
  -Wconversion 
  -Wsign-conversion 
  -Werror 
  -Wpedantic
  $<$<CONFIG:Debug>:-fsanitize=address,undefined>
  $<$<CONFIG:Debug>:-g>
  $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)
target_link_options(shaders_learning PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)
target_sources(shaders_learning PRIVATE
  src/main.cc
)
