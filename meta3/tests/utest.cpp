#include "../meta2.h"

#include <vector>
#include <map>   
#include <list>
#include <cassert>

// Kod za testiranje - NE DIRATI!

// 4.
class B {};
class D : public B {};
class C{};

class E : public B, public C {};

// 5. 
struct XXX{ int x; };
struct YYY{ double x; };
struct ZZZ{ int y; };

// 7.
class X{};


int main(){
    // 1. 
    static_assert(std::is_same_v<ConstToVolatile_t<int const>, int volatile>);
    static_assert(std::is_same_v<ConstToVolatile_t<int>, int>);
    static_assert(std::is_same_v<ConstToVolatile_t<int volatile const>, int volatile>);

    // 2. 
    static_assert(IsEvenArray_v<int> == false);
    static_assert(IsEvenArray_v<int[4]> == true);
    static_assert(IsEvenArray_v<int[3]> == false);
    static_assert(IsEvenArray<float[13]>::value == false);
    static_assert(IsEvenArray<char[16]>::value == true );

    // 3.
    std::array<long double,3> a{4,8,3};
    std::array<float,3> b{1.0f, 2.0f, 3.0f};
    auto c = a*b;
    assert(c[0] == 4);
    assert(c[1] == 16);
    assert(c[2] == 9);
    static_assert(std::is_same_v<std::decay_t<decltype(c[0])>, long double>); 
    
    // 4. 
    static_assert( IsBaseOf<B,D>::value );
    static_assert( !IsBaseOf<B,C>::value );
    static_assert( IsBaseOf<B,B>::value );
    static_assert( !IsBaseOf<int,long>::value );
    static_assert( !IsBaseOf<void,void>::value );
    static_assert( !IsBaseOf<void,B>::value );

    static_assert( IsBaseOf<const B,D>::value );
    static_assert( IsBaseOf<B, volatile D>::value );
    
    static_assert( IsBaseOf<B,E>::value );
    static_assert( IsBaseOf<C,E>::value );

	// 5. 
	static_assert(Has_x<XXX>::value);
	static_assert(Has_x<YYY>::value);
	static_assert(not Has_x<ZZZ>::value);
  
	// 6.
	static_assert(Container<std::vector<int>>);
	static_assert(Container<std::map<char,int>>);
	static_assert(Container<std::list<char*>>);
	static_assert(not Container<std::array<double,7>>);
	static_assert(not Container<X>);

	// 7.
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


	print(pt1);
	print(pt2);
	print(pt3);
	std::cout << "\n";
	
	// 8. 
	assert(fun(3, 4, 3.0) == 3);
	assert(fun(3, 4, 3.0, 5, 7, 9.7) == 6);

    return 0;
}
