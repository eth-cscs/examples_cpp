#include <iostream>
#include <thread>


void hello_fun() {
	
	std::cout<<"Hello world from fun!"<<std::endl;
}

struct hello_struct
{
	void operator()() const {
		std::cout<<"Hello world from struct!"<<std::endl;
	}

};

int main()
{
	// 1 - Say hello from function 
	std::thread t_fun(hello_fun);
	t_fun.join();

	// 2 - Say hello from struct
	hello_struct h;
	std::thread t_struct(h);
	t_struct.join();

	// 3 - Say hello from struct with uniform initializer
	std::thread t_struct_unif{hello_struct()};
	t_struct_unif.join();

	// 4 - Say hello from lambda expression
	std::thread t_lambda([](){
			std::cout<<"Hello world from lambda!"<<std::endl;
		});
	t_lambda.join();
}
