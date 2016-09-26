#include <thread>
#include <iostream>
#include <chrono>

void fun(){
	std::this_thread::sleep_for(std::chrono::seconds(10));
	return;
}

int main()
{

	std::thread::id t0_id = std::this_thread::get_id();
	std::thread t1(fun);
	std::thread::id t1_id(t1.get_id()); 
	std::thread t2(fun);
	std::thread::id t2_id(t2.get_id());
	std::cout<<"t0_id == t1_id "<<(t0_id==t1_id)<<std::endl;
	std::cout<<"t1_id == t2_id "<<(t1_id==t2_id)<<std::endl;
	
	std::thread t3;
	std::thread::id t3_ctor_id(t3.get_id());
	std::cout<<"t3_ctor_id == 'not any thread' "<<(t3_ctor_id==std::thread().get_id())<<std::endl;
	t3 = std::move(t1);
	std::thread::id t3_from_t1_id(t3.get_id());
	std::cout<<"t3_from_t1_id == t1_id "<<(t3_from_t1_id==t1_id)<<std::endl;

	t2.join();
	t3.join();

	
}
