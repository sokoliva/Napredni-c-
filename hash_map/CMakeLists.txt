# CMakeList.txt : CMake project for hash_map, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

project ("hash_map")
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG   release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Bitno je da je ime direktorija tests!
add_subdirectory(tests)

list(APPEND flags "-Wall")
if(WIN32)
   list(APPEND flags "/permissive-")
else()
   list(APPEND flags "-Wextra" "-pedantic")
endif()

message(STATUS ${flags})

add_executable (hash_map "main.cpp" "hash_map.h")
set_target_properties(hash_map PROPERTIES 
                      CXX_STANDARD 17
                      CXX_STANDARD_EQUIRED ON
                                         )
 
