**Zadatak**. U ovom zadatku vježbamo pisanje testova dok su svi elementi jezika koji se 
u zadatku koriste poznati od ranije. 

Porebno je implementirati predložak klase `Vec<T>` koja predstavlja dinamički 
alocirani vektor s elementima proizvoljnog tipa `T`. 
Klasa pamti pokazivač na dinamički alociranu memoriju i broj elemenata 
vektora. Memorija se alocira s `new` i dealocira sa `delete`. Tip indeksa je `std::size_t`.

Cijela klasa je u datoteci zaglavlja `vector.h` i testovi trebaju samo uključiti tu 
datoteku. 

Zahtjevi na klasu su sljedeći:

1. Klasa mora imati dodijeljeni (_default_) konstruktor i konstruktor koji uzima broj elemenata.  
1. Klasa ima konstruktor inicijalizacijskom listom: Na primjer, `Vec<char> vec{'a','b'};`.
1. Klasa ima konstruktor kopije kopiranjem i operator pridruživanja kopiranjem.
1. Klasa ima destruktor.
1. Klasa  ima operatore indeksiranja i metodu `size()`.
1. Klasa dozvoljava upotrebu _range-for_ petlje.
1. Klasa ima metode `clear()` i `resize(n)`. Metoda `resize()` mora sačuvati vrijednosti elemenata
koji ostaju u vektoru (i kod povećanja i kod smanjenja veličine vektora).
1. Klasa ima operator `==`. 

Napisati testove koji testiraju sljedeće elemente predloška klase `Vec<T>` za sve parametre `T` 
iz skupa {`int`, `float`, `double`, `long double`}:

1. Konstruktore.
1. Konstruktor kopije kopiranjem. 
1. Operator pridruživanja.
1. Operatore indeksiranja.
1. Metodu `clear()`.
1. Metodu `resize(n)`.
1. Testirati _range-for_ petlju. 
1. Operator uspoređivanja.  

Svaki pojedini test mora biti u zasebnom makrou i mora imati deskriptivno ime. 
U ispisu testa se mora vidjeti da su svi navedeni elementi testirani. 
