add_library(
    imgui 
    STATIC 
    ./backends/imgui_impl_glfw.cpp ./backends/imgui_impl_opengl3.cpp ./imgui.cpp 
    ./imgui_draw.cpp ./imgui_tables.cpp ./imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC ./ ./backends ..)