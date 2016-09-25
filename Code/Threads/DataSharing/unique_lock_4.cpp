#include <thread>
#include <mutex>
#include <iostream>

class protected_data_struct{

	int m_data;
	std::mutex m_mutex;

public:
	
	protected_data_struct(int i_value):
		m_data(i_value)
		{}
	
	void work_on_data(void){

		std::lock_guard<std::mutex> lock_guard(m_mutex);
		std::cout<<"Work on data"<<std::endl;
		process_data();
		write_data();
		std::cout<<"Work on data done"<<std::endl;
	}

	void work_on_data_unique_lock(void){

		std::unique_lock<std::mutex> lock(m_mutex);
		std::cout<<"Work on data"<<std::endl;
		process_data();
		lock.unlock();
		write_data();
		std::cout<<"Work on data done"<<std::endl;
	}
	
	void process_data(void){

		std::cout<<"Process data"<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(6));
		std::cout<<"Process data done"<<std::endl;
	}

	void write_data(void){

		std::cout<<"Write data"<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(6));
		std::cout<<"Write data done"<<std::endl;
	}
		
	void set_data(int i_data) {

		std::lock_guard<std::mutex> lock_guard(m_mutex);
		std::cout<<"Set data"<<std::endl;
		m_data = i_data;
		std::cout<<"Set data done"<<std::endl;
	}

};


int main()
{

    // 1 - Blocking write 	
	std::cout<<"Blocking write"<<std::endl;
	protected_data_struct data(10);
	std::thread t1([](protected_data_struct& io_data){
			io_data.work_on_data();
		},std::ref(data));

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	std::thread t2([](protected_data_struct& io_data){
			io_data.set_data(5);
		},std::ref(data));

	t1.join();
	t2.join();

    // 2 - Non blocking write
	std::cout<<std::endl;
	std::cout<<"Non blocking write"<<std::endl;
	t1 = std::thread([](protected_data_struct& io_data){
			io_data.work_on_data_unique_lock();
		},std::ref(data));

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	t2 = std::thread([](protected_data_struct& io_data){
			io_data.set_data(5);
		},std::ref(data));

	t1.join();
	t2.join();
}
