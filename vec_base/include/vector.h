#pragma once

// Koristiti ili #pragma once ili osigurače oblika #ifndef ... #define ... #endif
// ali ne miješati u istom projektu jedno i drugo. 
using namespace std;

/* Klasa koja implementira dinamički alocirani vektor.
 */
template <typename T> 
class Vec{
    int broj;
    T * ptr;
    public:
        //default konstruktor:
        Vec(){ 
            ptr = new T; 
            broj = 0;};
        //konstruktor koji uzima broj elemenata:
        Vec(int br){
            ptr = new T; 
            broj=br;}
        //destruktor:
        ~Vec(){if(ptr) delete [] ptr;}
        //copy kontruktor:
        Vec(const Vec& v){
            broj = 0;
            ptr = new T 
            T * t = ptr;
            T * pocetak = v.ptr;
            if(v.broj) broj=v.broj;
            T * end_ptr = &v.ptr[broj - 1];
            while(pocetak <= end_ptr){
                *t = *pocetak;
                pocetak++;
                t++;}
            
            }
        //konstruktor inicijalizacijskom listom:
        Vec(initializer_list<T> l) {
            broj=0;
            ptr = new T;
            size_t counter = 0;
            for (auto it = l.begin(); it != l.end(); ++it){
                ptr[counter++] = *it;
                broj++;
            }

        }
        //operator pridruzivanja kopiranjem:
        Vec& operator=(const Vec& v){
            if(&v==this) return *this;
            if(ptr) delete[] ptr;
            broj=0;
            if(v.broj) broj=v.broj;
            ptr = new T;  
            T * t = ptr;
            T * pocetak = v.ptr;
            T * end_ptr = &v.ptr[broj - 1];
            while(pocetak <= end_ptr){  
                *t = *pocetak;
                pocetak++;
                t++;}
             return *this;
        }
        //operator usporedivanja:
        bool operator==(const Vec& v){
            if(&v==this) return true;
            if(ptr==v.ptr) return true;
            if(broj==v.broj){
               size_t t=0;
               for(int i=0; i<broj; i++){
                    if(ptr[t]!=v.ptr[t++]) return false;}
               return true;
            }
            else return false;
            
        }
        //operator indeksiranja:
       T operator[](size_t i){ 
            if(i>=broj){
                cout<<"nema broja na otm indexu";
                exit(0);
            }
            return ptr[i];}
        
        //size() metoda:
        int size(){
            return broj;
        }
        void clear(){broj=0;}
        void resize(int n){broj=n;}
        //range for
        T* begin(){return ptr;}
        T*  end(){return ptr+broj;}

	
};
