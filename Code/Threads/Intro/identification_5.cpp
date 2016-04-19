#include <thread>
#include <iostream>
#include <unistd.h>

void fun(){

	sleep(20);
	return;
}

int main()
{

	std::thread::id t0_id = std::this_thread::get_id();
	
	std::thread t1(fun);
	std::thread::id t1_id(t1.get_id()); 
	
	std::thread t2(fun);
	std::thread::id t2_id(t2.get_id());
	
	std::thread t3;
	std::thread::id t3_id(t3.get_id());
	t3 = std::thread(fun);
	
	std::cout<<"t0_id = t1_id? "<<(t0_id==t1_id)<<std::endl;
	std::cout<<"t1_id = t2_id? "<<(t1_id==t2_id)<<std::endl;
	std::cout<<"t3_id = t3_id? "<<(t2_id==t3_id)<<std::endl;
	std::cout<<"t3_id = 'not any thread'? "<<(t3_id==std::thread().get_id())<<std::endl;
	
	
	t1.join();
	t2.join();
	// What about t3 join operation?

	std::cout<<"t3_id = 'not any thread'? "<<(t3.get_id()==std::thread().get_id())<<std::endl;
	t3.join();

	
}
