add_executable(utest utest.cpp)
set_target_properties(
    utest
    PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )

