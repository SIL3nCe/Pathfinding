cmake_minimum_required(VERSION 3.15)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
#set(SFML_DIR "C:/DevProjects/SFML-2.5.1/lib/cmake/SFML")
set(SFML_DIR "C:/Perso/SFML-2.5.1/lib/cmake/SFML")

file(GLOB_RECURSE SRC_FILES *.cpp *.h *.inl)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(Pathfinding ${SRC_FILES})

set(ImGui-SFML_DIR "C:/Program Files (x86)/imgui_sfml/lib/cmake/ImGui-SFML")
find_package(ImGui-SFML REQUIRED)
target_link_libraries(Pathfinding PRIVATE ImGui-SFML::ImGui-SFML)

target_include_directories(Pathfinding PRIVATE "Algos" "View" "View/Algos")
