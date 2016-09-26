#include <iostream>
#include <cstdlib>

int main() {
	
	std::cout<<"RAND_MAX value: "<<RAND_MAX<<std::endl;
	std::srand(232323);
    for(unsigned int i=0;i<10;++i){
		double rnd = ((double) std::rand()/RAND_MAX);
		std::cout<<"Random number value: "<<rnd<<std::endl; 
	}
}
