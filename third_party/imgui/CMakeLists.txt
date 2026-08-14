add_library(
    imgui 
    STATIC
    ./backends/imgui_impl_glfw.cpp ./backends/imgui_impl_opengl3.cpp ./imgui.cpp 
    ./imgui_draw.cpp ./imgui_tables.cpp ./imgui_widgets.cpp ./imgui_demo.cpp
)

target_include_directories(imgui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

target_link_libraries(imgui
    PRIVATE
        glfw
)