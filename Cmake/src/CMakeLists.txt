find_package (Eigen3 3.3 REQUIRED)
find_package (OpenMP REQUIRED)

add_executable(main main.cpp)

target_link_libraries (main Eigen3::Eigen)
target_link_libraries (main OpenMP::OpenMP_CXX)

set_target_properties(main
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )
