cmake_minimum_required(VERSION 3.5)

project(LangtonSAnt LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LangtonSAnt main.cpp
    ./ImGui/imgui.cpp
    ./ImGui/imgui_draw.cpp
    ./ImGui/imgui_impl_glfw.cpp
    ./ImGui/imgui_impl_opengl2.cpp
    ./ImGui/imgui_tables.cpp
    ./ImGui/imgui_widgets.cpp
    ./ImGui-SFML/imgui-SFML.cpp)

target_include_directories(LangtonSAnt PUBLIC ./ImGui)
target_include_directories(LangtonSAnt PUBLIC ./ImGui-SFML)
target_include_directories(LangtonSAnt PUBLIC include)

find_package(glfw3 CONFIG REQUIRED)
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)
#find_package(imgui CONFIG REQUIRED)
#find_package(ImGui-SFML CONFIG REQUIRED)

#target_link_libraries(LangtonSAnt sfml-audio sfml-graphics sfml-window sfml-system ImGui-SFML::ImGui-SFML)
target_link_libraries(LangtonSAnt sfml-audio sfml-graphics sfml-window sfml-system glfw opengl32)
