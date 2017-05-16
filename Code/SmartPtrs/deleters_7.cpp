#include <memory>
#include <iostream>
#include <string>

int* makeArray(const int i_size) {

	return new int[i_size];
}

struct Object {

	void dumpToFile(const std::string& i_fileName) {

		std::cout<<"Dumping status in file "<<i_fileName<<std::endl;
		
	}
	
};

int main() {

	// 0 - Create a shared_ptr to int[10], what is the problem here? WARNING, THIS IS BAD CODE! USE STL CONTAINERS!!! 
	std::shared_ptr<int> sp(new int[10]);

	// 1 - Fix the above bug with a custom deleter.  WARNING, THIS IS BAD CODE! USE STL CONTAINERS!!! 
	std::shared_ptr<int> sp_new(new int[10],[](int* p_int){ delete [] p_int; });

	// 2 - Create unique_ptr from Factory function makeArray. This is the only case you would need
	// a unique_ptr of T[] type: an external function returning a raw pointer to heap array you assume ownerhip of
	std::unique_ptr<int[]> up(makeArray(10));

	// 3 - Create unique_ptr of Object that dumps the status at destruction time
	const std::string fileName = "dump_file.dat";
	auto up_deleter = [fileName](Object* i_obj){ i_obj->dumpToFile(fileName); };
	std::unique_ptr<Object, decltype(up_deleter) > up_obj(new Object,up_deleter);
}
