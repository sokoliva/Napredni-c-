#pragma once
#include <cassert>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <tuple>
#include <algorithm>

using namespace std;


// Rasuta tablica
template <typename Key, typename Val, typename Hash = hash<Key>,
		  typename EqualTo = equal_to<Key>>
class HashMap
{
public:
	using value_type = pair<const Key, Val>;
	const static int DEFAULT_BUCKET_SIZE=16;

public:
	//konstruktori
	//1.konstruktor
	HashMap(){ 
		m_bucket_size=DEFAULT_BUCKET_SIZE;
		m_data=new hash_entry[m_bucket_size];
		m_no_elements=0;
	}
	HashMap(int size){ 
		m_bucket_size=size;
		m_data=new hash_entry[m_bucket_size];
		m_no_elements=0;
		for(int i=0; i<m_bucket_size;i++){
			m_data[i].get_flag()=empty;
		}
	}
	//destruktor
	~HashMap(){delete [] m_data;}
	//2. konstruktor inicijalizacijska lista
	HashMap(initializer_list<value_type> l){
		m_bucket_size=2*l.size()+1;
		m_data=new hash_entry[m_bucket_size];
		m_no_elements=0;
		for(int i=0; i<m_bucket_size;i++){
			m_data[i].get_flag()=empty;
		}
		for(auto it=l.begin(); it!=l.end(); it++){
			int h=hash((*it).first) % m_bucket_size;
			int trazimo_mjesto=1;
			while(trazimo_mjesto){
				if(m_data[h].get_flag()==empty){
					m_data[h].get_key()=(*it).first;
					m_data[h].get_val()=(*it).second;
					m_data[h].get_flag()=full;
					trazimo_mjesto=0;}
				else h=(h+1)%m_bucket_size;}
			m_no_elements++;
		}
	}
	//3. konstruktor
	template <class Iterator>
	HashMap(Iterator it1, Iterator it2){
		if(it1==it2) m_bucket_size=0;
		else m_bucket_size=2*distance(it1, it2)+1;
		m_no_elements=distance(it1, it2);
		m_data=new hash_entry[m_bucket_size];
		for(int i=0; i<m_bucket_size;i++){
			m_data[i].get_flag()=empty;
		}
		while(it1!=it2){
			int h=hash((*it1).first) % m_bucket_size;
			int trazimo_mjesto=1;
			while(trazimo_mjesto){
				if(m_data[h].get_flag()==empty){
					m_data[h].get_key()=(*it1).first;
					m_data[h].get_val()=(*it1).second;
					m_data[h].get_flag()=full;
					trazimo_mjesto=0;}
				else if (equal_to(m_data[h].get_key(),(*it1).first ))
				{
					trazimo_mjesto=0;
					m_no_elements--;
				}
				else h=(h+1)%m_bucket_size;}
			
			it1++;
		}
	}
	//cctor
	HashMap(const HashMap &H){
		m_no_elements=H.m_no_elements;
		m_bucket_size=H.m_bucket_size;
		m_data=new hash_entry[m_bucket_size];
		m_data=H.m_data;
	}
	HashMap( HashMap &&H){
		m_no_elements=H.m_no_elements;
		m_bucket_size=H.m_bucket_size;
		m_data=new hash_entry[m_bucket_size];
		m_data=H.m_data;
		H.m_no_elements=0;
		H.m_bucket_size=0;
		delete [] H.m_data;

	}
    //operator pridruzivanja-dovoljan je za oba (rvalue reference i lvalue reference)
	HashMap& operator=(HashMap H) {
		swap(*this, H);
		return *this;
	}
	
	// Zastavice.
    enum Flag : char{ empty, full, deleted };

    // Tip za pretinac.
	struct hash_entry
	{ 
	  public:
	  	Key & get_key(){return m_key;}
		Val & get_val(){return m_val;}
		Flag & get_flag(){return m_status;}
		Key  get_key()const{return m_key;}
		Val  get_val()const{return m_val;}
		Flag  get_flag()const{return m_status;}
		bool is_full()const{
			if(m_status==full) return true;
			else return false;
		}


		// javne metode strukture -- vaš kod
	  private:
		Key m_key;
		Val m_val;
		Flag m_status;
	};

	// Javne metode  -- vaš kod
	size_t size(){return m_no_elements;}
	size_t bucket_size(){return m_bucket_size;}
	hash_entry * data(){return m_data;}
	void clear(){
		m_bucket_size=0;
		m_no_elements=0;
	}
	int erase(Key key){
		if(!find(key)) return 0;
		else{
			int trazimo=0;
			int h=hash(key) % m_bucket_size;
			while(trazimo++<m_bucket_size){
				if(equal_to(m_data[h].get_key(),key)){
					m_data[h].get_flag()=deleted;
					m_no_elements--;
					return 1;
				}
				else h=(h+1)%m_bucket_size;}

		}
	}
	bool is_empty(){
		if(m_no_elements==0) return true;
		else return false;}
	optional<Val> find(Key key){
		int trazimo=0;
		int h=hash(key) % m_bucket_size;
		while(trazimo++<m_bucket_size){
			if((equal_to(m_data[h].get_key(),key)) && (m_data[h].get_flag()==full)) return m_data[h].get_val();
			else h=(h+1)%m_bucket_size;}
		return nullopt;
	}
	Val& operator[](Key key) {
		if(find(key)){
			int trazimo=0;
			int h=hash(key) % m_bucket_size;
			while(trazimo++<m_bucket_size){
				if(equal_to(m_data[h].get_key(),key)) return m_data[h].get_val();
				else h=(h+1)%m_bucket_size;}
		}
		else{
			if(m_no_elements==m_bucket_size) resize();
			//trazimo mjesto za ubaciti novi kljuc
			int h=hash(key) % m_bucket_size;
			while(1){
				if(m_data[h].get_flag()!=full){
					m_data[h].get_key()=key;
					m_data[h].get_flag()=full;
					m_no_elements++;
					return m_data[h].get_val();
					}
				h=(h+1)%m_bucket_size;}}}
	Val& operator[](Key key)const{
		if(find(key)){
			int trazimo=0;
			int h=hash(key) % m_bucket_size;
			while(trazimo++<m_bucket_size){
				if((equal_to(m_data[h].get_key(),key)) && (m_data[h].get_flag()==full)) return m_data[h].get_val();
				else h=(h+1)%m_bucket_size;}
		}
		}
	void resize(){
		size_t t=m_bucket_size;
		const auto * m_data1=m_data;
		m_bucket_size=2*m_bucket_size;
        auto m_data_1=new hash_entry[m_bucket_size]; 
		for(size_t i=0; i<m_bucket_size;i++){
            m_data_1[i].get_flag()=empty;
		}
		for(size_t i=0; i<t; i++ ){
				int h=hash(m_data1[i].get_key()) % m_bucket_size;
				int trazimo_mjesto=1;
				while(trazimo_mjesto){
                    if(m_data_1[h].get_flag()!=full){
                        m_data_1[h].get_key()=m_data1[i].get_key();
                        m_data_1[h].get_val()=m_data1[i].get_val();
                        m_data_1[h].get_flag()=full;
                        trazimo_mjesto=0;
                    }
                    else
                        h=(h+1)%m_bucket_size;
			    }
		    }
        delete [] m_data;  
        m_data = m_data_1;
	    }
	    
	
	Flag insert(value_type novi){
		Flag flag;
		if(find(novi.first)){
			return flag;
		}
		if(m_no_elements==m_bucket_size) resize();
		int h=hash((novi).first) % m_bucket_size;
		int trazimo_mjesto=1;
		while(trazimo_mjesto){
				if(m_data[h].get_flag()!=full){
					m_data[h].get_key()=(novi).first;
					m_data[h].get_val()=(novi).second;
					m_data[h].get_flag()=full;
					trazimo_mjesto=0;}
				else h=(h+1)%m_bucket_size;}
		m_no_elements++;
		flag=full;
		return flag;
	}
private:
    // Privatne metode i podaci -- vaš kod
    
	size_t m_bucket_size;  // broj pretinaca
	size_t m_no_elements;  // broj elemenata u spremniku
	hash_entry * m_data;   // polje pretinaca
	

	Hash hash;             // hash funkcija
	EqualTo equal_to;      // funkcijski objekt uspoređivanja
	//swap
	friend void swap(HashMap &H1, HashMap&H2){
		using std::swap;
		swap(H1.m_bucket_size, H2.m_bucket_size);
		swap(H1.m_no_elements,H2.m_no_elements);
		swap(H1.m_data,H2.m_data);
	}
};
