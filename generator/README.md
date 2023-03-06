**Zadatak**.   Potrebno je napraviti generator brojeva `wallis()` 
koji generira brojeve po sljedećem pravilu:

```
I_0 = pi/2, I_1=1, I_n = ((n-1)/n)*I_{n-2}, n=2,3,...
```

Radi se o rekurziji za računanje integrala od 0 do pi/2 funkcije 
sin^n(x). 

Generator `wallis()` generira beskonačan niz brojeva i može se koristiti u 
range-for petlji. Pored toga treba ga učiniti pogodnim za kompoziciju s 
pogledima na raspone. Glavni program vam je zadan.
