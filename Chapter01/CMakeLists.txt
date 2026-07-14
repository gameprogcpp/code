cmake_minimum_required(VERSION 3.16)
project(Chapter01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

add_executable(Chapter01
  Main.cpp
  Game.cpp
)

# Book sources use #include "SDL/SDL.h" (vendored layout under External/SDL).
target_include_directories(Chapter01 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/../External/SDL/include"
)

target_link_libraries(Chapter01 PRIVATE PkgConfig::SDL2)
