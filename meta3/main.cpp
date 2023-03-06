#include "meta2.h"
#include <cassert>  
#include <iostream>
#include <vector>
#include <map>   
#include <list> 


// 5. , 7.
class X{};


int main(){
	 // Vaši testovi dolaze ovdje
    static_assert(!(std::is_same_v<ConstToVolatile_t<int const>, int>)); //
    static_assert(!(std::is_same_v<ConstToVolatile_t<int>, char>)); //

    static_assert(IsEvenArray_v<int[]> == true); 
    static_assert(IsEvenArray_v<double[0]> == false); 
    static_assert(IsEvenArray<std::string[5]>::value == false);

    std::array<long double, 4> a{1, 2, 3, 4};
    std::array<int, 4> b{5, 6, 7, 8};
    auto c = a*b;
    assert(c[0] == 5);
    assert(c[1] == 12);
    assert(c[2] == 21);
    assert(c[3] == 32);
    static_assert(std::is_same_v<std::decay_t<decltype(c[0])>, long double>);

    static_assert( !IsBaseOf<X,int>::value );

    static_assert(not Has_x<X>::value);

    static_assert(not Container<int>);
    static_assert(not Container<double *>);
    static_assert(not Container<char>);
    static_assert(Container<std::string>);

    struct PointA{
		int x;
		long y;
	} pt1{2,3};

	struct PointL{
		char x;
		float y;
		char const * name;
	} pt2{'c',3, "ime"};
	
	struct PointS{
		long double x;
		bool y;
		std::string name;
	} pt3{2,0, "ime"};

    static_assert(GeneralPoint<PointA>); 
    static_assert(GeneralPoint<PointS>); 
    static_assert(not LabeledPoint<PointA>); 
    static_assert(LabeledPoint<PointL>);

    static_assert(Two<int, double, int, int, double>);
    static_assert(Two<int, double>); 
    static_assert(not Two<std::string, float, int, std::string, float>);
    int x=1;
    assert(fun(3) == 1); 
    assert(fun(3.0) == 1); 
    assert(fun(x) == 1); 
    assert(fun() == 0); 
    assert(fun(1.2, 2.5 , 3) == 3); 
    assert(fun(x, x , 3) == 3); 
    assert(fun(x, 2.8 , 3.1, 6, 10, 12.1) == 6); 

    return 0;
}
