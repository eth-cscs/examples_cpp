#include <thread>
#include <future>
#include <cmath>
#include <iostream>
#include <stdexcept>

double my_sqrt(double i_value) {

	if(i_value<0.0)
		throw std::invalid_argument("Invalid argument provided");
	return std::sqrt(i_value);
}

void my_sqrt_promise(double i_value, std::promise<double> i_promise) {

	if(i_value<0.0)
		i_promise.set_exception(std::make_exception_ptr(std::invalid_argument("Invalid argument provided")));
	else
		i_promise.set_value(std::sqrt(i_value));
}

int main() {

	// 1 - Async exception handling
	std::cout<<"Async exception handling"<<std::endl;
	std::future<double> future_f = std::async(std::launch::async,my_sqrt,-1.0);
	try {
		double res = future_f.get();
		std::cout<<"Sqrt result "<<res<<std::endl;
	}
	catch(std::exception const & e) {
		std::cout<<e.what()<<std::endl;
	}


    // 2 - Packaged task exception handling
	std::cout<<std::endl;
	std::cout<<"Packaged task exception handling"<<std::endl;
	auto task_f = std::packaged_task<double(double)>(my_sqrt);
	future_f = task_f.get_future();
	std::thread thread_f(std::move(task_f),-1.0);
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	try {
		double res = future_f.get();
		std::cout<<"Sqrt result "<<res<<std::endl;
	}
	catch(std::exception const & e) {
		std::cout<<e.what()<<std::endl;
	}
	thread_f.join();

    // 3 - Promise exception handling
	std::cout<<std::endl;
	std::cout<<"Promise task exception handling"<<std::endl;
	std::promise<double> promise_sqrt;
	auto future_sqrt = promise_sqrt.get_future();
	std::thread thread_sqrt(my_sqrt_promise,-1.0,std::move(promise_sqrt));
	try {
		double res = future_sqrt.get();
		std::cout<<"Sqrt result "<<res<<std::endl;
	}
	catch(std::exception const & e) {
		std::cout<<e.what()<<std::endl;
	}
	thread_sqrt.join();
}
