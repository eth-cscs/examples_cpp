#include <thread>
#include <mutex>
#include <iostream>

class protected_data_struct_deadlock{

	int m_data;
	std::mutex m_mutex;

public:	
	protected_data_struct_deadlock(int i_value):
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

	int get_data(void) const {
		return m_data;
	}

	void swap_data(protected_data_struct_deadlock& io_data) {

		if(&io_data == this)
			return;
		
		std::lock_guard<std::mutex> lock_this(m_mutex);
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::lock_guard<std::mutex> lock_other(io_data.m_mutex);
		int tmp_data = io_data.m_data;
		io_data.m_data = m_data;
		m_data = tmp_data;
	}
	
};

class protected_data_struct_no_deadlock{

	int m_data;
	std::mutex m_mutex;

public:
	protected_data_struct_no_deadlock(int i_value):
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

	int get_data(void) const {
		return m_data;
	}

	void swap_data(protected_data_struct_no_deadlock& io_data) {

		if(&io_data == this)
			return;

		std::lock(m_mutex,io_data.m_mutex);
		std::lock_guard<std::mutex> lock_this(m_mutex,std::adopt_lock);
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::lock_guard<std::mutex> lock_other(io_data.m_mutex,std::adopt_lock);
		int tmp_data = io_data.m_data;
		io_data.m_data = m_data;
		m_data = tmp_data;
	}

};

int main()
{

	std::thread t1;
	std::thread t2;

	// Set #if to true to run deadlock case 
#if 0
    // 1 - Protected data swap with deadlock
	std::cout<<"Protected data swap with deadlock"<<std::endl;
	protected_data_struct_deadlock protected_data_struct_a_deadlock(10);
	protected_data_struct_deadlock protected_data_struct_b_deadlock(20);
	t1 = std::thread(&protected_data_struct_deadlock::swap_data,&protected_data_struct_a_deadlock,
					 std::ref(protected_data_struct_b_deadlock));
	t2 = std::thread(&protected_data_struct_deadlock::swap_data,&protected_data_struct_b_deadlock,
					 std::ref(protected_data_struct_a_deadlock));	
	t1.join();
	t2.join();

#endif

	// 2 - Protected data swap without deadlock 
	std::cout<<"Protected data swap without deadlock"<<std::endl;
	protected_data_struct_no_deadlock protected_data_struct_a_no_deadlock(10);
	protected_data_struct_no_deadlock protected_data_struct_b_no_deadlock(20);
	t1 = std::thread(&protected_data_struct_no_deadlock::swap_data,&protected_data_struct_a_no_deadlock,
					 std::ref(protected_data_struct_b_no_deadlock));
	t2 = std::thread(&protected_data_struct_no_deadlock::swap_data,&protected_data_struct_b_no_deadlock,
					 std::ref(protected_data_struct_a_no_deadlock));

	t1.join();
	t2.join();
}
