#include <thread>
#include <future>
#include <iostream>

void f(std::promise<std::thread::id> i_promise, double i_d, double& io_d) {
	io_d = i_d;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	i_promise.set_value(std::this_thread::get_id());
}

int main() {

	double d=0.;
	std::promise<std::thread::id> id_promise;
	auto get_id = id_promise.get_future();
	std::thread t1(f,std::move(id_promise),23.0,std::ref(d));	
	std::cout<<"Valid future "<<get_id.valid()<<std::endl;
	std::cout<<"std::this_thread::get_id() "<<std::this_thread::get_id()<<std::endl;
	std::cout<<"get_id.get() "<<get_id.get()<<std::endl;
	std::cout<<"d = "<<d<<std::endl;
	t1.join();
}
