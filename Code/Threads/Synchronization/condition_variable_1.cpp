#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cond_var;

bool wait_flag;
int data;
const unsigned int num_step{5};

void update_data(){

	for(unsigned int step=0;step<num_step;++step) {

		std::unique_lock<std::mutex> lock(mutex);
		while(!wait_flag) {
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		    lock.lock();
		}

		std::cout<<"Update data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		data++;
		wait_flag = false;
	}
}

void process_data(){

	for(unsigned int step=0;step<num_step;++step) {

		std::unique_lock<std::mutex> lock(mutex);
		while(wait_flag) {
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			lock.lock();
		}

		std::cout<<"Process data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		data--;
		wait_flag = true;
	}
}

void update_data_cond_var(){

	for(unsigned int step=0;step<num_step;++step) {

		std::unique_lock<std::mutex> lock(mutex);
		cond_var.wait(lock,[]{ return wait_flag; });
		wait_flag = false;
		std::cout<<"Update data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		data++;
		lock.unlock();
		cond_var.notify_one();
	}
}

void process_data_cond_var(){

	for(unsigned int step=0;step<num_step;++step) {

		std::unique_lock<std::mutex> lock(mutex);
		cond_var.wait(lock,[]{ return !wait_flag; });
		wait_flag = true;
		std::cout<<"Process data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		data--;
		lock.unlock();
		cond_var.notify_one();
	}
}


int main(){

	// 1 - While loop check synchronization 
	std::cout<<"While loop check synchronization"<<std::endl;
	data = 0;
	wait_flag = true;
	std::thread t1(update_data);
	std::thread t2(process_data);
	t1.join();
	t2.join();

	std::cout<<std::endl;
    // 2 - Condition variable synchronization
	std::cout<<"Condition variable synchronization"<<std::endl;
	data = 0;
	wait_flag = true;
	t1 = std::thread(update_data_cond_var);
	t2 = std::thread(process_data_cond_var);
	t1.join();
	t2.join();
}
