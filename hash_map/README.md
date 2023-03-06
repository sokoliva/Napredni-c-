**Zadatak**. Kreirati rječnik na bazi rasute tablice. Elementi rječnika 
su parovi ključ-vrijednost. Ključ je tipa `Key`, a vrijednost tipa `Val`
(parametri predloška). Rasuta tablica je bazirana na otvornom adresiranju 
i linearnom haširanju. To znači da kada dolazi do kolizije (pretinac za element
koji ubacujemo je već zauzet) element se ubacuje u prvi sljedeći prazni pretinac.
Svaki pretinac sadrži ključ i vrijednost (i zastavicu, vidi implemenataciju).
Spremnik ne dozvoljava duplikate i ignorira pokušaj višestrukog ubacivanja istog elementa. 

Rječnik ima tri konstruktora: 

- Prvi konstruktor uzima broj pretinaca i konstruira prazan rječnik 
  sa zadanim brojem pretinaca. Broj pretinaca se ne mora zadati (dodijeljeni konstruktor)
  i tada se koristi dodijeljena vrijednost. Klasa eksportira tu vrijednost kroz 
  konstantnu varijablu DEFAULT_BUCKET_SIZE.
- Drugi konstruktor uzima inicijalizacijsku listu. Ako lista ima n elemenata
  konstruira se rječnik s 2n+1 pretinaca. Elementi iz liste kopiraju se u rječnik.
- Treći konstruktor uzima raspon elemenata (parova ključ-vrijednost) uzimajući dva 
  iteratora (begin i end). Ako je raspon prazan kreira se prazan rječnik s dodijeljenim 
  brojem pretinaca. Ako raspon ima n elemenata konstruira se rječnik s 2n+1 pretinaca. 
  Elementi iz raspona se kopiraju u rječnik.

Metode rječnika:

- `empty()` vraća `true` ako je spremnik parazan, inače `false`.
- `size()` vraća broj elemenata u spremniku.
- `bucket_size()` vraća broj pretinaca.
- `clear()` isprazni čitav spremnik.
- `find(key)` za dani ključ nalazi vrijednost pridruženu ključu u spremniku. Povratna 
   vrijednost je tipa `std::optional<Val>`. Ako ključ nije u spremniku vraćeni
    `optional` je prazan; ako jeste onda `optional` sadrži vrijednost pridruženu 
    ključu. 
- `insert(pair<const Key, Val>)` Spremnik ne dozvoljava duplikate i stoga vraća 
   zastavicu koja je jednaka   `true` ako je element ubačen, a `false` ako je element 
   već prisutan u spremniku.   Ako je spremnik pun zove se privatna metoda `resize()` 
   prije ubacivanja elementa.  
- `erase(key)` Briše element s danim ključem iz spremnika. Vraća broj obrisanih 
  elemenata (0 ili 1). 
- `operator[key]`  Ponaša se kao standardni operator dohvata u `map`spremniku. 
  Vraća referencu na vrijednost pridruženu ključu ako je ključ u spremniku. Ako ključ
  nije u spremniku ubacuje ga s _dodijeljenom_ vrijednošću i vraća referencu na nju. 
  Zove metodu `resize()`ako je potrebno.
- `resize()` Privatna metoda koja podvostručuje broj pretinaca. Ona mora izvršiti 
  ponovno haširanje kako bi prisutne elemente ubacija u novi spremnik. 

**Implementacijski detalji**. 

- Svaki pretinac sadrži ključ, vrijednost i zastavicu. Pretinac je implementiran kao 
  ugnježdena struktura `hash_entry`. 
  Zastavica je enumeracija (`Flag`) koja ima vrijednosti prazan, pun i izbrisan. Prilikom 
  traženja elementa moramo razlikovati prazne pretince od onih u kojima je element 
  izbrisan.
- Indeksi su tipa `size_t`. 
- Pretince držati u dinamički alociranom polju. Alokacija se obavlja s `new/delete`. (Ne koristiti STL spremnike.)
- Spremnik može biti pun (broj elemenata = broj pretinaca) i metode `find()`, `erase()`
  operiraju normalno na punom spremniku. Isto vrijedi i za operator dohvata  (`[]`)
  ako ne ubacuje novi element u spremnik. Tek kada treba ubaciti novi element 
  operator `[]` će zvati metodu `resize()`.  Treda napomenuti da to nije tipično ponašanje 
  za neuređene spremnike već je ovdje zadano samo radi pune određenosti ponašanja spremnika. 

**Kontrola kopiranja**

- Potrebno je implementirati potpunu kontrolu kopiranja.
- Za operatore pridruživanja primijeniti `copy & swap` idiom.
- Pomoću `valgrind` alata provjeriti da nema curenja memorije.

**Napomen**. U `main` funkciji napraviti svoje dodatne testove. Funkcija ne smije ostati 
prazna. U direktoriju `test` su testovi koji moraju proći.
