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

		while(!wait_flag) {
		}		
		std::lock_guard<std::mutex> guard(mutex);
		std::cout<<"Update data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		data++;
		wait_flag = false;
	}
}

void process_data(){

	for(unsigned int step=0;step<num_step;++step) {
		
		while(wait_flag) {
		}
		std::lock_guard<std::mutex> guard(mutex);
		std::cout<<"Process data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		data--;
		wait_flag = true;
	}
}


void update_data_protected_wait(){

	for(unsigned int step=0;step<num_step;++step) {

		mutex.lock();
		while(!wait_flag) {
			mutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			mutex.lock();
		}

		std::cout<<"Update data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		data++;
		wait_flag = false;
		mutex.unlock();
	}
}

void process_data_protected_wait(){

	for(unsigned int step=0;step<num_step;++step) {

		mutex.lock();
		while(wait_flag) {
			mutex.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			mutex.lock();
		}

		std::cout<<"Process data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		data--;
		wait_flag = true;
		mutex.unlock();
	}
}

void update_data_unique_protected_wait(){

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

void process_data_unique_protected_wait(){

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

void update_data_condition_var_book_like(){

	for(unsigned int step=0;step<num_step;++step) {

		std::lock_guard<std::mutex> lock(mutex);
		std::cout<<"Update data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		data++;
		cond_var.notify_one();
	}
}

void update_data_condition_var(){

	for(unsigned int step=0;step<num_step;++step) {

		std::unique_lock<std::mutex> lock(mutex);
//		cond_var.wait(lock,[]{ return data==0;});// TODO: check implementation to understand why this call always returns for the first call without notification
		std::cout<<"Update data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		data++;
		//      lock.unlock();//<-- Remember to unlock before notifying!
		cond_var.notify_one();//<-- Try to comment out this to see spurious wake ups! (recompile....)
		cond_var.wait(lock,[]{ return data==0; });// TODO: see TODO above, should the call be here?
	}
}

void process_data_condition_var(){

	for(unsigned int step=0;step<num_step;++step) {

		std::unique_lock<std::mutex> lock(mutex);
		cond_var.wait(lock,[]{ return data!=0; });
		std::cout<<"Process data - step: "<<step<<" input data value: "<<data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		data--;
		lock.unlock();//<-- Remember to unlock before notifying!
		cond_var.notify_one();//<-- Try to comment out this to see spurious wake ups! (recompile....)
	}
}


int main(){

	data = 0;
	
	wait_flag = true;// TODO: remove this and unify the cases using data only
	
	// Example 1 - Non-protected lock_guard based synchronization case
	std::cout<<"Example 1 - Non-protected lock_guard based synchronization case"<<std::endl;
	std::thread t1(update_data);
	std::thread t2(process_data);
	
	t1.join();
	t2.join();
	
	std::cout<<std::endl;
	
	
    // Example 2 - Protected (manual) mutex lock/unlock based synchronization case
	std::cout<<"Example 2 - Protected (manual) mutex lock/unlock based synchronization case"<<std::endl;
	t1 = std::thread(update_data_protected_wait);
	t2 = std::thread(process_data_protected_wait);

	t1.join();
	t2.join();

	std::cout<<std::endl;

    // Example 3 - Protected (unique_lock) lock/unlock based synchronization case
	std::cout<<"Example 3 - Protected (manual) mutex lock/unlock based synchronization case"<<std::endl;
	t1 = std::thread(update_data_unique_protected_wait);
	t2 = std::thread(process_data_unique_protected_wait);

	t1.join();
	t2.join();

	std::cout<<std::endl;

	// Example 4 - Protected condition_variable based synchronization case
	std::cout<<"Protected condition_variable based synchronization case"<<std::endl;
	t1 = std::thread(update_data_condition_var);
	t2 = std::thread(process_data_condition_var);

	t1.join();
	t2.join();
	
}
