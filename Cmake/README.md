**Zadatak**.

Zadan je repozitorij s izvornim kodom. Potrebno je konstruirati 
sustav za izgradnju. 

U repozitoriju se nalaze dva poddirektorija : `src` i `test`. 
U `src` direktoriju treba kreirati program (neka se zove `main` jer je
izvorna datoteka `main.cpp`) i povezati ga s bibliotekama **Eigen3** i 
**OpenMP**. U `test` imamo Googletest testove u kojima testiramo Eigen 
biblioteku i stoga ih treba povezati s **googletest** bibliotekom. 

**Napomena**. Biblioteke tražiti sa `find_package()`. OpenMP eksportira
`OpenMP::OpenMP_CXX` cilj (_target_), dok `Eigen3` eksportira 
`Eigen3::Eigen` cilj,  koje treba koristiti u link naredbama.

