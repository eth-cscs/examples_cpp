#include <random>
#include <fstream>
#include <iostream>

int main() {

	// Create default random engine
	std::default_random_engine e;

	// Create uniform_int_distribution d1 with generation in [1,6)
	std::uniform_int_distribution<> d1{1,6};
	std::cout<<"d1 range: ["<<d1.min()<<";"<<d1.max()<<"]"<<std::endl;

	// Permanently reset d1 for generation in [0,2)
	d1.param(std::uniform_int_distribution<>::param_type{0,2});
	std::cout<<"d1 range: ["<<d1.min()<<";"<<d1.max()<<"]"<<std::endl;

	// Temporarily reset d1 for generation in [1,6)
	d1(e,std::uniform_int_distribution<>::param_type{1,6});
	std::cout<<"d1 range: ["<<d1.min()<<";"<<d1.max()<<"]"<<std::endl;

	// Create uniform_int_distribution d2 with generation in [1,6)
	std::uniform_int_distribution<> d2{1,6};

	// Compare the distribution status
	std::cout<<"(d1==d2)? "<<(d1==d2)<<std::endl;

	// Permanently reset d1 for generation in [0,2)
	d2.param(std::uniform_int_distribution<>::param_type{0,2});
	std::cout<<"(d1==d2)? "<<(d1==d2)<<std::endl;
	
	// Save status of d1 in d1_status.out
	std::cout<<"Save status of d1 in d1_status.out"<<std::endl;
	std::fstream d1_status;
	d1_status.open("d1_status.out",std::fstream::out);
	d1_status<<d1;
	d1_status.close();
	
}
