cmake_minimum_required(VERSION 3.5)

project(LangtonSAnt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LangtonSAnt main.cpp)
target_include_directories(LangtonSAnt PUBLIC include)

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

#target_link_libraries(LangtonSAnt PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(LangtonSAnt sfml-audio sfml-graphics sfml-window sfml-system ImGui-SFML::ImGui-SFML)
