#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <cassert>

void fun(){
	std::this_thread::sleep_for(std::chrono::seconds(10));
}

void print_fun(std::string i_message){

	std::cout<<"Thread message: "<<i_message<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(10));
}

std::thread create_thread(){
	
	return std::thread(print_fun,"create_thread()");
	
}

void take_ownership(std::thread i_t){
	i_t.join();
}


int main()
{
		
	// 1 - Check basic ownership transfer
	std::cout<<"Check basic ownership transfer"<<std::endl;
	std::thread t1(fun);
	std::thread t2;
	assert(t1.joinable());
	assert(!t2.joinable());
	std::cout<<"t1.joinable() "<<t1.joinable()<<std::endl;
	std::cout<<"t2.joinable() "<<t2.joinable()<<std::endl;
	
	t2 = std::move(t1);
	assert(!t1.joinable());
	assert(t2.joinable());
	std::cout<<"t1.joinable() "<<t1.joinable()<<std::endl;
	std::cout<<"t2.joinable() "<<t2.joinable()<<std::endl;
	t2.join();

	t1 = std::thread(fun);
	t2 = std::thread(fun);
	t2.detach();
	t2 = std::move(t1);
	std::cout<<"t1.joinable() "<<t1.joinable()<<std::endl;
	std::cout<<"t2.joinable() "<<t2.joinable()<<std::endl;
	t2.join();
	
	// 2 - Check ownership transfer through functions
	std::cout<<"Check ownership transfer through functions"<<std::endl;
	t1 = std::thread(print_fun,"main()");
	t1.join();

	t1 = create_thread();
	t1.join();

	t1 = std::thread(fun);
	assert(t1.joinable());
	take_ownership(std::move(t1));
	assert(!t1.joinable());
		
}
