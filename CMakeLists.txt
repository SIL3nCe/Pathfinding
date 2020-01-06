cmake_minimum_required(VERSION 3.15)

project(Pathfinding)

add_subdirectory(src)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Pathfinding")