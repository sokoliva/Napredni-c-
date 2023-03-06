#include "gtest/gtest.h"
#include "../include/vector.h"

// Vaši testovi dolaze ovdje.
//testiranje default konstruktora
TEST(VEKTORI, konstruktorD) {
    Vec<int> vec;
    ASSERT_EQ(vec.size(), 0);
}
//testiranje konstruktora koji uzima broj elemenata
TEST(VEKTORI, konstruktorB) {
    Vec<int> vec(3);
    ASSERT_EQ(vec.size(), 3);
}
//testiranje copy konstruktora
TEST(VEKTORI, konstruktorC) {
    Vec<int> vec1={1,2,3,4};
    Vec<int> vec2(vec1);
    EXPECT_EQ(vec2[3], 4);
    EXPECT_EQ(vec2.size(), 4);
}
//testiranje konstruktora inicijalizacijskom listom
TEST(VEKTORI, konstruktorI) {
    Vec<int> vec={1,2,3,4};
    EXPECT_EQ(vec[1], 2);
}

//testiranje operatora pridruzivanja kopiranjem
TEST(VEKTORI, operatorP) {
    Vec<int> vec1={1,2,3,4};
    Vec<int> vec2=vec1;
    EXPECT_TRUE(vec1==vec2);
}
//operator usporedivanja
TEST(VEKTORI,operatorU){
    Vec<int> vec1={1,2,3,4};
    Vec<int> vec2={1,2,3,4};
    EXPECT_TRUE(vec1==vec2);
}
//operator indeksiranja
TEST(VEKTORI,operatorI){
    Vec<int> vec={7,9,3};
    EXPECT_EQ(vec[0],7);
    EXPECT_EQ(vec[1],9);
    EXPECT_EQ(vec[2],3);
}
//range for
TEST(VEKTORI, range){
    Vec<int> vec={2,23,6,48};
    int sum=0;
    for(auto& element: vec){
        sum+=element;}
    EXPECT_EQ(sum, 79);}

TEST(VEKTORI, clear){
    Vec<float> vec(20);
    vec.clear();
    EXPECT_EQ(vec.size(),0);
}

TEST(VEKTORI, resize){
    Vec<float> vec(20);
    vec.resize(6);
    EXPECT_EQ(vec.size(),6);
}
