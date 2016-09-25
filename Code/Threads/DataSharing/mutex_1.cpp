#include <thread>
#include <mutex>
#include <iostream>
//#include <cstdlib>

std::mutex mutex;

void update_counter(unsigned int& io_counter) {
	io_counter++;
}

void protected_update_counter(unsigned int& io_counter) {

//	std::mutex mutex;// What if I decomment this line?
	mutex.lock();	
	io_counter++;
	mutex.unlock();
}

void protected_guard_update_counter(unsigned int& io_counter) {

	//  std::mutex mutex;// What if I decomment this line?
	std::lock_guard<std::mutex> guard(mutex);
	io_counter++;
}

int main()
{

	unsigned int counter=0;
	// 1 - Non protected update
	std::cout<<"Non protected update"<<std::endl;
	for(unsigned int i=0;i<100000;i++){
		std::thread t1(update_counter,std::ref(counter));
		std::thread t2(update_counter,std::ref(counter));
		update_counter(counter);
		t1.join();
		t2.join();
		if(counter!=3)			
			std::cout<<"Counter: "<<counter<<std::endl;
		counter=0;
	}

	
	// 2 - Protected update (with "manual" mutex lock/unlock)
	std::cout<<"Protected update (with manual mutex lock/unlock)"<<std::endl;
	for(unsigned int i=0;i<100000;i++){
		std::thread t1(protected_update_counter,std::ref(counter));
		std::thread t2(protected_update_counter,std::ref(counter));
		protected_update_counter(counter);
		t1.join();
		t2.join();
		if(counter!=3)
			std::cout<<"Counter: "<<counter<<std::endl;
		counter=0;
	}

	// 3 - Protected update (with lock_guard)
	std::cout<<"Protected update (with lock_guard)"<<std::endl;
	for(unsigned int i=0;i<100000;i++){
		std::thread t1(protected_guard_update_counter,std::ref(counter));
		std::thread t2(protected_guard_update_counter,std::ref(counter));
		protected_guard_update_counter(counter);
		t1.join();
		t2.join();
		if(counter!=3)
			std::cout<<"Counter: "<<counter<<std::endl;
		counter=0;
	}
	
	
	return 0 ;

}
