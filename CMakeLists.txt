cmake_minimum_required(VERSION 3.15)

project(Pathfinding)

add_subdirectory(src)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Pathfinding")
set_property(TARGET Pathfinding PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")