cmake_minimum_required(VERSION 3.15)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

file(GLOB_RECURSE SRC_FILES *.cpp *.h *.inl)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(Pathfinding ${SRC_FILES})

# ImGUI
set(IMGUI_DIR "C:/DevProjects/imgui-master")
target_include_directories(Pathfinding PRIVATE ${IMGUI_DIR})

# SFML
target_link_libraries(Pathfinding sfml-graphics)

