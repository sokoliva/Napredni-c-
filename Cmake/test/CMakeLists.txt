add_executable("testEigen" mtest.cpp)
target_link_libraries("testEigen"  gtest_main)

add_test(NAME testEigen COMMAND testEigen)
