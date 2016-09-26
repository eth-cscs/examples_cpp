#include <future>
#include <iostream>
#include <thread>

std::thread::id f(double i_d, double& io_d) {
	io_d = i_d;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return std::this_thread::get_id();
}

int main() {

	double d=0.;
	auto task = std::packaged_task<std::thread::id(double i_d,double& io_d)>(f);
	auto get_id = task.get_future();
	std::thread t1(std::move(task),23.0,std::ref(d));
	std::cout<<"std::this_thread::get_id() "<<std::this_thread::get_id()<<std::endl;
	std::cout<<"get_id.get() "<<get_id.get()<<std::endl;
	std::cout<<"d = "<<d<<std::endl;
	t1.join();	
}
