#include "gtest/gtest.h"
#include <eigen3/Eigen/Dense>

TEST(Konstrukcija, zbrajanje){
    using Eigen::MatrixXd;

    MatrixXd mat1(2,2), mat2(2,2);
    mat1(0,0) = 1; mat1(0,1) = 0; mat1(1,0) = 1; mat1(1,1) = 1;
    mat2(0,0) = 1; mat2(0,1) = 1; mat2(1,0) = 0; mat2(1,1) = 1;

    MatrixXd mat3 = mat1+mat2;
    ASSERT_DOUBLE_EQ(mat3(0,0), mat1(0,0)+mat2(0,0));
}
