cmake_minimum_required(VERSION 3.13)
project(Generator LANGUAGES CXX)

if(WIN32)
# Pod MSVC nam treba /std:c++latest što se dobiva s 23
set(CMAKE_CXX_STANDARD 23)
else()
# Linux još ne pozna -std=c++23
set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)
