**Zadatak**. U ovom zadatku treba napisati niz metafunkcija i koncepata. 
Testovi se moraju kompilirati i izvršavati (u debug načinu).  U funkciju 
`main()` dolaze vaši testovi i ona ne smije biti prazna. 

-   Napraviti metafunkciju `ConstToVolatile<T>` koja u svakom konstantnom tipu `T` mijenja `const` u `volatile`.
    Tip koji nema `const` ostavlja na miru. 
    Dodati i `_t` alias template.  Ne koristiti metafunkcije iz zaglavlja `<type_traits>`.
-  Napisati metafunkciju `IsEvenArray` koja vraća `true` ako je tip polje (tip T[N]) s parnim
   brojem elemenata `N`, a inače vraća `false`. Dodati i predložak varijable `_v`. 
   Ne koristiti metafunkcije iz zaglavlja `<type_traits>`.
-  Definirati operator množenja (`*`) po komponentama  polja `std::array<T,N>` i
    `std::array<S,N>` općenito različitih tipova `S` i `T`. Definirati povratnu vrijednost operatora 
   kao `std::array<V>` tako da `V` bude egzaktno tip koji proizvodi množenje objekta tipa `T` i `S`.
   Iz   zaglavlja `<type_traits>`  koristiti samo `std::declval<>()`.
-  Potrebno je napisati metafunkciju `IsBaseOf<B,D>` (u STL-u `std::is_base_of<B,D>`)
   koja ispituje je li klasa `B` **javna bazna** klasa za `D`. 
   Temelj na kojem se bazira razlikovanje je preopterećenje funkcija. Ako imamo
   pokazivač na klasu `D` tada je njegova konverzija u pokazivač na baznu klasu 
   bolja od konverzije u pokazivač na `void`. Na taj način možemo razlikovati klasu 
   koja ima odgovarajuću bazu od one koja ju nema.  
   Iz `<type_traits>` koristiti samo `std::is_class<>` te `std::true_type` i `std::false_type`. 
   Ne kopirati rješenje iz cppreference.com (0 bodova) koje funkcionira i s privatnom bazom i 
   s ambivalentnom bazom!
-  Napisati meta funkciju `Has_x<T>` koja daje vrijednost true ako i samo ako `T` ima varijablu 
   imena `x`. Napišite predložak funkcije (`template <typename T> int xfun(T t)`) koji vraća  0 ili 1 
   ovisno o tome da li tip `T` ima varijablu članicu `x` ili nema.
-   Napisati koncept `Container<T>` koji predstavlja STL spremnik. 
   Tip `T` zadovoljava koncept `Container<T>`  ako i samo ako:
(1) Ima tipove `value_type`, `size_type`, `allocator_type`, `iterator` i  `const_iterator`.
(2) Ima metode `size()`, `begin()`, `end()`, `cbegin()` i `cend()`.
-  Napisati koncept `GeneralPoint<T>` koji predstavlja klasu koja ima javne varijable članice `x` i `y`
   bilo kojeg numeričkog tipa. 
   Napisati koncept `LabeledPoint<T>` koji supsumira koncept  `GeneralPoint<T>` i ima dodatnu varijablu 
   članicu imena `name` konveribilnu u `std::string`. Napisati predložak funkcije `print()` koji uzima parametra tipa
  `GeneralPoint<T>`  i ispisuje točku na standardni izlaz  u obliku `(x,y)`. Napisati specijalizaciju tog predloška 
   za tip `LabeledPoint<T>` koji ispisuje točku na standardni izlaz  u obliku `(name : x,y)`.
-  Napisati koncept `Two<T,S,Args...>` koji dozvoljava proizvoljan niz tipova ukoliko se  
   u nizu ponavljaju jedino tipovi `T` i `S`. Iskoristite koncept `Two<>` da napišete funkciju `fun()` koja 
   uzima proizvoljan broj argumenata, ali samo ako su njihovi tipovi `double` ili `int`. Funkcija vraća
   broj dobivenih argumenata. 

Svi testovi u `tests` direktoriju moraju proći. Datoteku  `tests/utest.cpp` ne dirati. Vlastite testove pisati u 
`main()` funkciji koja ne smije ostati prazna. 
