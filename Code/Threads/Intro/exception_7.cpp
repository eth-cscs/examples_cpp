#include <thread>
#include <iostream>
#include <exception>

void f() {

	std::cout<<"Start work in f()"<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout<<"Work in f() finished"<<std::endl;
}

void throwing_f() {

//	throw std::exception();

}

void 

int main() {

	std::thread t(f);

	try {
		throwing_f();
	}
	catch(...){
		t.join();
	}
	t.join();
}
