add_executable(utest utest.cpp ../include/vector.h)
target_link_libraries(utest  gtest_main)

add_test(NAME utest COMMAND utest)
