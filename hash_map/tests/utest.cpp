#include "gtest/gtest.h"
#include "../hash_map.h"
#include <string>
#include <vector>

// konstruktor 1, empty, size
TEST(HashMap, konstruktor1) { 
	HashMap<std::string, int> hm(5);
	EXPECT_TRUE(hm.is_empty());
	EXPECT_EQ(hm.size(), 0);
	EXPECT_EQ(hm.bucket_size(), 5);
}
TEST(HashMap, konstruktor1a) { 
	HashMap<std::string, int> hm;
	EXPECT_TRUE(hm.is_empty());
	EXPECT_EQ(hm.size(), 0);
	auto defsize = HashMap<std::string, int>::DEFAULT_BUCKET_SIZE;
	EXPECT_EQ(hm.bucket_size(), defsize);
}

// Konstruktor s inicijalizacijskom listom, insert
TEST(HashMap, konstruktor2) {
	HashMap<std::string, int> hm{ {"AASD",17}, {"LOI", 78} };
	EXPECT_EQ(hm.bucket_size(), 2*2+1); // 2*n+1 gdje je n broj elemenata u listi
	EXPECT_EQ(hm.size(), 2);
	EXPECT_FALSE(hm.is_empty());
	EXPECT_EQ(hm["AASD"], 17);
	EXPECT_EQ(hm["LOI"], 78);
	auto rez = hm.insert({ "VAL", -11 }); // 3
	rez = hm.insert({ "MladenJ", 55 });   // 4
	rez = hm.insert({ "VVVVVV", -100 });  // 5. element 
	rez = hm.insert({ "VVVVVV", -200 });  // ponovljeni element 
	EXPECT_EQ(hm.size(), 5);
}

TEST(HashMap, konstruktor3) {
	std::vector<std::pair<std::string, double>> data;
	data.push_back({ "mladen", 31.2 });
	data.push_back({ "damir", 61.3 });
	data.push_back({ "darko", -19.1 });
	data.push_back({ "mateo", 6.6 });
	data.push_back({ "goran", 10002.22 });
	data.push_back({ "mladen", 31.3 }); // ponavljanje

	HashMap<std::string, double> hm3(data.begin(), data.end());
	EXPECT_EQ(hm3.size(), 5);
	EXPECT_TRUE(hm3.find("mladen"));
	EXPECT_TRUE(hm3.find("damir"));
	EXPECT_TRUE(hm3.find("darko"));
	EXPECT_TRUE(hm3.find("mateo"));
	EXPECT_TRUE(hm3.find("goran"));

	int no_erased = hm3.erase("mladen");
	EXPECT_EQ(no_erased, 1);
	EXPECT_EQ(hm3.size(), 4);
	no_erased = hm3.erase("den");
	EXPECT_EQ(no_erased, 0);
	EXPECT_EQ(hm3.size(), 4);
	hm3.insert({ "eduard", 313 });

	EXPECT_FALSE(hm3.find("mladen"));
	EXPECT_TRUE(hm3.find("darko"));

	hm3["zebra"] = 0;
	EXPECT_EQ(hm3.size(), 6);
	hm3["mladen"] = 19.19;
	EXPECT_DOUBLE_EQ(hm3["mladen"], 19.19);
}
TEST(HashMap, konstruktor3a) {
	std::vector<std::pair<std::string, double>> data;
    HashMap<std::string, double> hm3(data.begin(), data.end());
	EXPECT_TRUE(hm3.is_empty());
	EXPECT_EQ(hm3.size(), 0);
}

// insert (konstruktor 1, insert, empty,size)
TEST(HashMap, insert) { 
	HashMap<std::string, int> hm1(5);
	auto flag = hm1.insert({ "XYZ", 32 });
	EXPECT_FALSE(hm1.is_empty());
	EXPECT_EQ(hm1.size(), 1);
	flag = hm1.insert({ "XYZ", 62 });
	EXPECT_FALSE(flag);
	EXPECT_EQ(hm1.size(), 1);
	flag = hm1.insert({ "A", 1 });
	EXPECT_EQ(hm1.size(), 2);
	flag = hm1.insert({ "B", 2 });
	EXPECT_EQ(hm1.size(), 3);
	flag = hm1.insert({ "C", 3 });
	EXPECT_EQ(hm1.size(), 4);
	flag = hm1.insert({ "D", 5 });
	EXPECT_EQ(hm1.size(), 5);
	EXPECT_TRUE(hm1.find("XYZ"));
	EXPECT_TRUE(hm1.find("A"));
	EXPECT_TRUE(hm1.find("B"));
	EXPECT_TRUE(hm1.find("D"));
	EXPECT_TRUE(hm1.find("C"));
}

TEST(HashMap, resize) { 
	HashMap<std::string, int> hm1(3);
	auto flag = hm1.insert({ "A", 32 }); 
	flag = hm1.insert({ "B", 32 }); 
	flag = hm1.insert({ "C", 32 }); 
	EXPECT_EQ(hm1.size(), 3);
	flag = hm1.insert({ "D", 32 }); 
	EXPECT_EQ(hm1.size(), 4);
	EXPECT_EQ(hm1.bucket_size(), 6);
    EXPECT_TRUE(hm1.find("A"));
	EXPECT_TRUE(hm1.find("B"));
	EXPECT_TRUE(hm1.find("D"));
	EXPECT_TRUE(hm1.find("C"));
}

TEST(HashMap, erase){
	HashMap<std::string, int> hm1(3);
	// Brisanje jedinog elementa
	hm1.insert({ "A", 32 });
	EXPECT_FALSE(hm1.is_empty());
	EXPECT_EQ(hm1.size(), 1);
	int deli = hm1.erase("A");
	EXPECT_EQ(deli, 1);
	EXPECT_TRUE(hm1.is_empty());
	EXPECT_EQ(hm1.size(), 0);
	// Ponovno brisanje
	deli = hm1.erase("A");
	EXPECT_EQ(deli, 0);
	// napuni do kraja pa obriši
	hm1.insert({ "A", 32 });
	hm1.insert({ "B", 32 });
	hm1.insert({ "C", 32 });
	EXPECT_EQ(hm1.erase("A"), 1);
}

TEST(HashMap, find){
	HashMap<std::string, int> hm1(5);
	auto flag = hm1.insert({ "A", 32 });
	EXPECT_TRUE(flag);
	flag = hm1.insert({ "B", 33 });
	EXPECT_TRUE(flag);
	flag = hm1.insert({ "C", 34 });
	EXPECT_TRUE(flag);
	flag = hm1.insert({ "D", 35 });
	EXPECT_TRUE(flag);
	flag = hm1.insert({ "E", 36 });
	EXPECT_TRUE(flag);
	auto res = hm1.find("A");
	EXPECT_EQ(res.value(), 32);
    
}

// insert (konstruktor 1, insert, empty,size)
TEST(HashMap, dohvat) { 
	HashMap<std::string, int> hm1(5);
	hm1["XYZ"] =32;
	EXPECT_FALSE(hm1.is_empty());
	EXPECT_EQ(hm1.size(), 1);
	EXPECT_TRUE(hm1.find("XYZ"));

	hm1["XYZ"] = 62;
	EXPECT_TRUE(hm1.find("XYZ").value() == 62); 
	EXPECT_EQ(hm1.size(), 1);

	hm1["A"] = 1;
	EXPECT_EQ(hm1.size(), 2);
	EXPECT_TRUE(hm1.find("A").value() == 1); 
	EXPECT_EQ(hm1.size(), 2);
	
	hm1["B"] = 2; 
	EXPECT_TRUE(hm1.find("B").value() == 2); 
	EXPECT_EQ(hm1.size(), 3);

    hm1["C"] = 3; 
	EXPECT_TRUE(hm1.find("C").value() == 3); 
	EXPECT_EQ(hm1.size(), 4);
 
    hm1["D"] = 4; 
	EXPECT_TRUE(hm1.find("D").value() == 4); 
	EXPECT_EQ(hm1.size(), 5);

	hm1["E"] = 5;
	EXPECT_EQ(hm1.size(), 6);
	EXPECT_EQ(hm1.bucket_size(), 10);
	EXPECT_TRUE(hm1.find("E").value() == 5); 

// provjeri stare elemente
    EXPECT_FALSE(hm1.is_empty());  
	EXPECT_TRUE(hm1.find("XYZ").value() == 62);  
	EXPECT_TRUE(hm1.find("A").value() == 1);  
	EXPECT_TRUE(hm1.find("B").value() == 2);   
	EXPECT_TRUE(hm1.find("C").value() == 3);  
	EXPECT_TRUE(hm1.find("D").value() == 4);  

}

TEST(HashMap, clear) {
	HashMap<std::string, int> hm{ {"AASD",17}, {"LOI", 78} }; 
	auto rez = hm.insert({ "VAL", -11 }); // 3
	rez = hm.insert({ "MladenJ", 55 });   // 4
	rez = hm.insert({ "VVVVVV", -100 });  // 5. element  
	EXPECT_EQ(hm.size(), 5);
	hm.clear();
	EXPECT_TRUE(hm.is_empty());
	EXPECT_TRUE(hm.size() == 0);
}

TEST(HashMap, CCtor){
	HashMap<std::string, int> hm{ {"AASD",17}, {"LOI", 78} }; 
	HashMap<std::string, int> hm1(hm);

    const auto * dhm = hm.data();
	const auto * dhm1 = hm1.data();

    for(size_t i=0; i<hm.bucket_size(); ++i){
        EXPECT_EQ(dhm[i].get_flag(), dhm1[i].get_flag()); 
		if(dhm[i].is_full()){
              EXPECT_STREQ(dhm[i].get_key().c_str(), dhm1[i].get_key().c_str());
              EXPECT_EQ(dhm[i].get_val(), dhm1[i].get_val()); 
		}
	}
}

TEST(HashMap, MCtor){
	HashMap<std::string, int> hm{ {"AASD",17}, {"LOI", 78} }; 
	HashMap<std::string, int> hm1(hm);
	HashMap<std::string, int> hm2 = std::move(hm);

    EXPECT_TRUE(hm.is_empty());

    const auto * dhm1 = hm1.data();
	const auto * dhm2 = hm2.data();

    for(size_t i=0; i<hm1.bucket_size(); ++i){
        EXPECT_EQ(dhm1[i].get_flag(), dhm2[i].get_flag()); 
		if(dhm1[i].is_full()){
              EXPECT_STREQ(dhm1[i].get_key().c_str(), dhm2[i].get_key().c_str());
              EXPECT_EQ(dhm1[i].get_val(), dhm2[i].get_val()); 
		}
	}
}


TEST(HashMap, MOP){
	HashMap<int, int> hm{ {4,17}, {1024, 78} }; 
	HashMap<int, int> hm1(hm);
	HashMap<int, int> hm2;
	hm2 = std::move(hm);

    EXPECT_TRUE(hm.is_empty());

    const auto * dhm1 = hm1.data();
	const auto * dhm2 = hm2.data();

    for(size_t i=0; i<hm1.bucket_size(); ++i){
        EXPECT_EQ(dhm1[i].get_flag(), dhm2[i].get_flag()); 
		if(dhm1[i].is_full()){
              EXPECT_EQ(dhm1[i].get_key(), dhm2[i].get_key());
              EXPECT_EQ(dhm1[i].get_val(), dhm2[i].get_val()); 
		}
	}
}

TEST(HashMap, COP){
	HashMap<double, char> hm{ {4.1,'g'}, {1024.8, 'b'} }; 
	HashMap<double, char> hm1; 
	hm1 = hm;

    const auto * dhm1 = hm1.data();
	const auto * dhm = hm.data();

    for(size_t i=0; i<hm.bucket_size(); ++i){
        EXPECT_EQ(dhm1[i].get_flag(), dhm[i].get_flag()); 
		if(dhm[i].is_full()){
              EXPECT_DOUBLE_EQ(dhm1[i].get_key(), dhm[i].get_key());
              EXPECT_EQ(dhm1[i].get_val(), dhm[i].get_val()); 
		}
	}
}