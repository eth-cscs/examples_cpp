#include <thread>
#include <mutex>
#include <iostream>

class data_struct{

	int m_data;
	
public:
	data_struct(int i_value):
		m_data(i_value)
		{}
	
	void work_on_data(void) {
		
		std::cout<<"Running work_on_data method"<<std::endl;
		std::cout<<"work_on_data starts on local data = "<<m_data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(6));
		std::cout<<"work_on_data terminates on local data = "<<m_data<<std::endl;
		std::cout<<"Running work_on_data method done!"<<std::endl;
	}

	void set_data(int i_data) {
		m_data = i_data;
	}
	
};

class protected_data_struct{

	int m_data;
	std::mutex m_mutex;

public:
	
	protected_data_struct(int i_value):
		m_data(i_value)
		{}
	
	void work_on_data(void) {

		std::lock_guard<std::mutex> lock_guard(m_mutex);
		std::cout<<"Running work_on_data method"<<std::endl;
		std::cout<<"work_on_data starts on local data = "<<m_data<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(6));
		std::cout<<"work_on_data terminates on local data = "<<m_data<<std::endl;
		std::cout<<"Running work_on_data method done!"<<std::endl;
	}

	void set_data(int i_data) {
		std::lock_guard<std::mutex> lock_guard(m_mutex);
		m_data = i_data;
	}
};

int main()
{

	// 1 - Data race: unprotected concurrent read/write access  
	std::cout<<"Data race: unprotected concurrent read/write access"<<std::endl;
	data_struct data_struct_a(10);
	std::thread t1([](data_struct& io_data){
			io_data.work_on_data();
		},std::ref(data_struct_a));	
	
	std::thread t2([](data_struct& io_data){
			io_data.set_data(5);
		},std::ref(data_struct_a));

	t1.join();
	t2.join();

	// 2 - Protected concurrent read/write access 
	std::cout<<std::endl;
	std::cout<<"Protected concurrent read/write access"<<std::endl;
	protected_data_struct protected_data_struct_a(10);
	t1 = std::thread([](protected_data_struct& io_data){
			io_data.work_on_data();
		},std::ref(protected_data_struct_a));

	t2 = std::thread([](protected_data_struct& io_data){
			io_data.set_data(5);
		},std::ref(protected_data_struct_a));
	
	t1.join();
	t2.join();
}
