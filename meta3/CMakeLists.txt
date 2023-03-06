cmake_minimum_required(VERSION 3.13)
project(meta2)
add_subdirectory(tests)

add_executable(meta main.cpp meta2.h)


set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)

set_target_properties(
    meta
    PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )

