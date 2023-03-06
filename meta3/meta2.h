#pragma once 

#include <type_traits>
#include <array>
#include <string>
#include <iostream>
#include <concepts>

// 1. Napraviti metafunkciju ConstToVolatile koja u svakom tipu const mijenja u volatile.
//    Dodati i _t alias template.

template <typename T>  // metafunkcija koja vraća tip
struct TypeIdentity{
    using type = T;
};

template <typename T>
struct ConstToVolatile : TypeIdentity<T> {};

template <typename T>
struct ConstToVolatile<T const> : TypeIdentity<T volatile> {};

template <typename T>
using ConstToVolatile_t = typename ConstToVolatile<T>::type;

// 2. Napraviti metafunkciju IsEvenArray<> koja vraća true ako je tip polje
//   (tip T[N]) s parnim brojem elemenata N.

template <bool T>
struct type_{
    static constexpr bool value = T;
};

template <typename T>
struct IsEvenArray : type_<false> {};

template <typename T>
struct IsEvenArray<T[]> : type_<true> {};

template<class T, std::size_t N>
struct IsEvenArray<T[N]> : type_<(N%2 == 0)> {};

template <typename T>
constexpr bool IsEvenArray_v = IsEvenArray<T>::value;

// 3. Definiramo operator množenja (*) po komponentama  polja std::array<T,N> i
//    std::array<S,N> općenito različitih tipova. Definirati povratnu vrijednost operatora std::array<V> 
//    tako da V bude egzaktno tip koji proizvodi množenje objekta tipa T i S.
//    Koristiti std::declval<>.

template <typename T, typename S, typename V = decltype(std::declval<T>()*std::declval<S>()),  std::size_t N>
std::array<V, N> operator*( std::array<T, N> a, std::array<S, N> b ){
    std::array<V, N> c;
    for(int i = 0; i < N; i++){
        c[i] = a[i] * b[i];
    }
    return c;
}

// 4. Potrebno je napisati metafunkciju IsBaseOf<B,D> (u STL-u std::is_base_of<B,D>)
//    koja ispituje je li klasa B javna bazna klasa za D. 
//    Temelj na kojem se bazira razlikovanje je preopterećenje funkcija. Ako imamo
//    pokazivač na klasu D tada je njegova konverzija u pokazivač na baznu klasu 
//    bolja od konverzije u pokazivač na void. Na taj način možemo razlikovati klasu 
//    koja ima odgovarajuću bazu od one koja ju nema.  
//    Iz <type_traits> koristiti samo std::is_class<> te std::true_type i std::false_type. 
//    Ne kopirati rješenje iz cppreference.com (0 bodova)!

namespace details {
    template <typename B>
    std::true_type test(const volatile B*);
    template <typename>
    std::false_type test(const volatile void*);
}

template <typename B, typename D>
struct IsBaseOf{
    static constexpr bool value = std::is_class<B>::value && std::is_class<D>::value && decltype(details::test<B>(static_cast<D*>(nullptr)))::value;
};

// 5. Napisati meta funkciju Has_x<T> koja daje vrijednost true ako i samo ako T ima varijablu 
//   imena x. Napišite predložak funkcije (template <typename T> int xfun(T t)) koji vraća  0 ili 1 
//   ovisno o tome da li tip T ima varijablu članicu x ili nema. 

/* drugo moguće rješenje
template <typename T, typename = int>
struct Has_x : std::false_type { };

template <typename T>
struct Has_x <T, decltype((void) T::x, 0)> : std::true_type { };*/

template <typename T,  typename = decltype(T::x) >
std::true_type Has_xImp(void *);

template <typename T>  // fall back
std::false_type Has_xImp(...);

template <typename T>
using Has_x = decltype(Has_xImp<T>(nullptr));

template <typename T> 
int xfun(T t){ 
    if(Has_x<T>::value) return 1;
    else return 0;
}

// 6. Napisati koncept Container<T> koji predstavlja STL spremnik. 
// Tip zadovoljava koncept Container ako i samo ako:
// 1) Ima tipove value_type, size_type, allocator_type, iterator, const_iterator
// 2) Ima metode size(), begin(), end(), cbegin(), cend().

template <typename T>
concept Container = requires(T a){
   typename T::value_type;
   typename T::size_type; 
   typename T::allocator_type;
   typename T::iterator;
   typename T::const_iterator;
   
   a.size();
   a.begin();
   a.end();
   a.cbegin();
   a.cend();
};

// 7.  Napisati koncept `GeneralPoint<T>` koji predstavlja klasu koja ima javne varijable članice `x` i `y`
//   bilo kojeg numeričkog tipa.  Napisati koncept `LabeledPoint<T>` koji supsumira koncept  `GeneralPoint<T>` i ima dodatnu varijablu 
// članicu imena `name` konveribilnu u `std::string`. Napisati predložak funkcije `print()` koji uzima parametra tipa
//`GeneralPoint<T>`  i ispisuje točku na standardni izlaz  u obliku `(x,y)`. Napisati specijalizaciju tog predloška 
// za tip `LabeledPoint<T>` koji ispisuje točku na standardni izlaz  u obliku `(name : x,y)`.
template <typename T>
concept GeneralPoint= requires(T obj){
    obj.x;
    obj.y;
};

template <typename T>
concept LabeledPoint = GeneralPoint<T> &&
        requires(T obj){
            {obj.name} -> std::convertible_to<std::string>;
};

template <GeneralPoint T>
void print(T const & obj){
    std::cout<<"("<<obj.x<<","<<obj.y<<")"<<"\n";
}

template <LabeledPoint T>
void print(T const & obj){
    std::cout<<"("<<obj.name<<" : "<<obj.x<<","<<obj.y<<")"<<"\n";
}

// 8. Napisati koncept Two<T,S,Args...> koji dozvoljava proizvoljan niz tipova ukoliko se  
// u nizu ponavljaju jedino tipovi T i S. Iskoristite koncept Two da napišete funkciju fun() koja 
// uzima proizvoljan broj argumenata, ali samo ako su njihovi tipovi double ili int. Funkcija vraća
// broj dobivenih argumenata.

template <typename T, typename S, typename ... Args>
concept Two = ((std::same_as<T, Args> || std::same_as<S, Args>) && ...);

template <typename T, typename S, typename ... Args>
requires Two<double , int, Args...>
int fun(T t,S s, Args ... args){
    constexpr std::size_t n = sizeof...(Args) + 2; 
    return n;
}

int fun(){
    return 0;
}

int fun(double t){
    return 1;
}

