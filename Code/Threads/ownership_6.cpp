#include <thread>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void fun(){
	sleep(10);
}

void print_fun(std::string i_message){

	std::cout<<"Thread message: "<<i_message<<std::endl;
	sleep(10);
}

std::thread create_thread(){
	
	return std::thread(print_fun,"create_thread()");
	
}

void take_ownership(std::thread i_t){

	std::thread local_t(std::move(i_t));
	std::cout<<"Thread ownership taken, waiting for work completion"<<std::endl;
	local_t.join();
	std::cout<<"Work completed"<<std::endl;
}


int main()
{
	
#if 1
	
	//// Base ownership transfer
	std::cout<<"Base ownership transfer: "<<std::endl;
	std::thread t1(fun);
	std::thread t2;
	std::cout<<"Is t1 joinable? "<<t1.joinable()<<std::endl;
	std::cout<<"Is t2 joinable? "<<t2.joinable()<<std::endl;
	
//	t2 = t1; ?? What about this line?
	t2 = std::move(t1);
	std::cout<<"Is t1 joinable? "<<t1.joinable()<<std::endl;
	std::cout<<"Is t2 joinable? "<<t2.joinable()<<std::endl;
	
	t2.join();

	t1 = std::thread(fun); // Why we do not need std::move() here ?
	t2 = std::thread(fun);
//	t2.join(); // What if I delete this line...
	t2.detach(); // ...or this one?
	t2 = std::move(t1);
	t2.join();
	////
	
	std::cout<<std::endl;
#endif

#if 1
	//// Ownerhip thrasfer through functions
	std::thread t3;
	std::cout<<"Ownership transfer through functions: "<<std::endl;
	t3 = std::thread(print_fun,"main()");
	t3.join();

	t3 = create_thread();
	t3.join();

	t3 = std::thread(fun);
	std::cout<<"Is t3 joinable? "<<t3.joinable()<<std::endl;
	take_ownership(std::move(t3));
	std::cout<<"Is t3 joinable? "<<t3.joinable()<<std::endl;
    ////

	std::cout<<std::endl;
#endif
	
#if 1
	///? Ownership and move aware containers
	std::cout<<"Ownership and move aware containers"<<std::endl;
	std::cout<<"Create thread pool"<<std::endl;
	std::vector<std::thread> threads;
	for(unsigned int i=0;i<5;++i){

		std::stringstream i_string;
		i_string<<i;
		std::string message(" index is ");
		message += i_string.str();
		
		threads.push_back(std::thread(print_fun,message));
		
	}
	for(unsigned int i=0;i<5;++i){
		threads[i].join();
	}
	std::cout<<"Work completed"<<std::endl;	
	////
#endif
	
}
