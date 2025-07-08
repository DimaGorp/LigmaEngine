cmake_minimum_required(VERSION 3.28)

project(LigmaEngine)

#build Framework
include("${CMAKE_SOURCE_DIR}/scripts/BuildCore.cmake")

#build Editor
add_subdirectory(Engine)