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
	std::thread t_fun(hello_fun);
	t_fun.join();

	hello_struct h;
	std::thread t_struct(h);
	t_struct.join();

	std::thread t_struct_temp{hello_struct()};
	t_struct_temp.join();


	std::thread t_lambda([](){
			std::cout<<"Hello world from lambda!"<<std::endl;
		});
	t_lambda.join();
}
