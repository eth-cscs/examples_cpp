#include <random>
#include <iostream>
#include <fstream>

int main(){

	// Initialize two default engines with different seeds
	std::default_random_engine e1;
	std::default_random_engine e2{232323};

	// Compare the generators status
	std::cout<<"(e1==e2)? "<<(e1==e2)<<std::endl;

	// Reseed first generator with second generator seed and compare again
	e1.seed(232323);
	std::cout<<"(e1==e2)? "<<(e1==e2)<<std::endl;

	// Generate one random number with first generator and compare e1 and e2 status
	e1();
	std::cout<<"(e1==e2)? "<<(e1==e2)<<std::endl;

    // Discard one random number of second generator and compare e1 and e2 status
	e2.discard(1);
	std::cout<<"(e1==e2)? "<<(e1==e2)<<std::endl;

	// Save current e2 status
	std::cout<<"Save e2 status in e2_status.out"<<std::endl;
	std::fstream e2_status;
	e2_status.open("e2_status.out",std::fstream::out);
	e2_status<<e2;
	e2_status.close();

    // Discard 100 random numbers of second generator and compare e1 and e2 status
	e2.discard(100);
	std::cout<<"(e1==e2)? "<<(e1==e2)<<std::endl;

	// Restore previously saved e2 status and compare it with e1  
	std::cout<<"Restore e2 status from e2_status.out"<<std::endl;
	e2_status.open("e2_status.out",std::fstream::in);
	e2_status>>e2;
	e2_status.close();
	std::cout<<"(e1==e2)? "<<(e1==e2)<<std::endl;

	// Reseed e2 with std::random_device and save its status
	std::cout<<"Save e2(rdev) status in e2_status_rdev.out"<<std::endl;
	std::random_device rdev{};
	e2.seed(rdev());
	e2_status.open("e2_status_rdev.out",std::fstream::out);
	e2_status<<e2;
	e2_status.close();
}
