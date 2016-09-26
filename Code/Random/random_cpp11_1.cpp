#include <random>
#include <iostream>

int main() {
	std::default_random_engine e(232323);
	std::uniform_real_distribution<double> d{0,1};
	for(unsigned int i=0;i<10;++i){
		double rnd = d(e);
		std::cout<<"Random number value: "<<rnd<<std::endl;
	}
}
