cmake_minimum_required(VERSION 3.4)
project(path-finder CXX)

add_executable(path-finder
  src/main.cpp
  src/arguments.cpp
  src/arguments.hpp
  src/result.hpp
  src/error.hpp
  src/error.cpp
  src/log.hpp)
target_include_directories(path-finder PRIVATE src)
target_compile_definitions(path-finder PRIVATE -D_CRT_SECURE_NO_WARNINGS)
set_target_properties(path-finder PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS ON
  LINKER_LANGUAGE CXX)
