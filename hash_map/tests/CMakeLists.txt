add_executable(utest utest.cpp ../hash_map.h)
target_link_libraries(utest  gtest_main)

add_test(NAME utest COMMAND utest)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET utest PROPERTY CXX_STANDARD 17)
endif()
