#include "hash_map.h"

#include <iostream>
#include<vector>
using namespace std;

int main()
{ 
    // Vaši testovi dolaze ovdje. 
    vector<pair<string, double>> data;
	data.push_back({ "mladen", 31.2 });
	data.push_back({ "damir", 61.3 });
	data.push_back({ "darko", -19.1 });
	data.push_back({ "mateo", 6.6 });
	data.push_back({ "goran", 10002.22 });
    HashMap<string, double> hm3(data.begin(), data.end());
    hm3.insert({ "B", 32 }); 
	hm3.insert({ "C", 32 }); 
     hm3.insert({ "d", 32 }); 
	 hm3.insert({ "e", 32 });
    hm3.insert({ "f", 32 }); 
	hm3.insert({ "g", 32 });
    cout<<"   ";
    cout<<hm3.bucket_size();
    cout<<" elementi "<<hm3.size();
    hm3.insert({ "hgh", 32 });
    //hm3.resize();
    cout<<" elementi2 "<<hm3.size();
    cout<<hm3.bucket_size();
	return 0;
}
