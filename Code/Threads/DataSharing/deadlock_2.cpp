#include <thread>
#include <mutex>
#include <iostream>
#include <unistd.h>

/**
   @brief Data struct
*/
template <typename T>
struct data_struct{
	
	T m_data;
	
	data_struct(T i_value):
		m_data(i_value)
		{}
	
	void work_on_data(data_struct& io_data_struct) {
		
		std::cout<<"Running work_on_data method"<<std::endl;
		std::cout<<"work_on_data starts on local data = "<<m_data<<" and input data = "<<io_data_struct.m_data<<std::endl;
		sleep(4);
		std::cout<<"work_on_data terminates on local data = "<<m_data<<" and input data = "<<io_data_struct.m_data<<std::endl;
		std::cout<<"Running work_on_data method done!"<<std::endl;
		return;
		
	}
	
	void swap_data(data_struct& io_data_struct) {

		//  std::cout<<"Running swap_data method"<<std::endl;
		T tmp(m_data);
		m_data = io_data_struct.m_data;
		io_data_struct.m_data = tmp;
		//  std::cout<<"Running swap_data function done!"<<std::endl; 
		
	}
	
};


/**
   @brief Protected data struct
*/
template <typename T>
struct protected_data_struct{

	T m_data;
	std::mutex m_mutex;
	
	protected_data_struct(T i_value):
		m_data(i_value)
		{}
	

	void work_on_data(protected_data_struct& io_data_struct) {
		
		std::cout<<"Locking data in (protected) work_on_data method"<<std::endl;
		std::lock_guard<std::mutex> guard_me(m_mutex);
		sleep(2);
		std::lock_guard<std::mutex> guard_other(io_data_struct.m_mutex);
		std::cout<<"Running (protected) work_on_data method"<<std::endl;
		std::cout<<"(protected) work_on_data starts on local data = "<<m_data<<" and input data = "<<io_data_struct.m_data<<std::endl;
		sleep(4);
		std::cout<<"(protected) work_on_data terminates on local data = "<<m_data<<" and input data = "<<io_data_struct.m_data<<std::endl;
		std::cout<<"Running (protected) work_on_data method done!"<<std::endl;
		return;

	}
	
	void swap_data(protected_data_struct& io_data_struct) {

		std::cout<<"Locking data in (protected) swap_data method"<<std::endl;
		std::lock_guard<std::mutex> guard_me(m_mutex);
		sleep(2);
		std::lock_guard<std::mutex> guard_other(io_data_struct.m_mutex);
		std::cout<<"Running (protected) swap_data method"<<std::endl;
		T tmp(m_data);
		m_data = io_data_struct.m_data;
		io_data_struct.m_data = tmp;
		std::cout<<"Running (protected) swap_data method done!"<<std::endl;
		
	}

	void work_on_data_no_deadlock(protected_data_struct& io_data_struct) {

		std::cout<<"Locking data in (protected, no deadlock) work_on_data method"<<std::endl;
		std::lock(m_mutex,io_data_struct.m_mutex);
		std::lock_guard<std::mutex> guard_me(m_mutex,std::adopt_lock);
		sleep(2);
		std::lock_guard<std::mutex> guard_other(io_data_struct.m_mutex,std::adopt_lock);
		std::cout<<"Running (protected, no deadlock) work_on_data method"<<std::endl;
		std::cout<<"(protected, no deadlock) work_on_data starts on local data = "<<m_data<<" and input data = "<<io_data_struct.m_data<<std::endl;
		sleep(4);
		std::cout<<"(protected, no deadlock) work_on_data terminates on local data = "<<m_data<<" and input data = "<<io_data_struct.m_data<<std::endl;
		std::cout<<"Running (protected, no deadlock) work_on_data method done!"<<std::endl;
		return;

	}

	void swap_data_no_deadlock(protected_data_struct& io_data_struct) {

		std::cout<<"Locking data in (protected, no deadlock) swap_data method"<<std::endl;
		std::lock(m_mutex,io_data_struct.m_mutex);
		std::lock_guard<std::mutex> guard_me(m_mutex,std::adopt_lock);
		sleep(2);
		std::lock_guard<std::mutex> guard_other(io_data_struct.m_mutex,std::adopt_lock);
		std::cout<<"Running (protected, no deadlock) swap_data method"<<std::endl;
		T tmp(m_data);
		m_data = io_data_struct.m_data;
		io_data_struct.m_data = tmp;
		std::cout<<"Running (protected, no deadlock) swap_data method done!"<<std::endl;

	}
	

};


template <typename T>
void work_on_data(data_struct<T>& io_data_struct_a,data_struct<T>& io_data_struct_b) {
 
	io_data_struct_a.work_on_data(io_data_struct_b);
}

template <typename T>
void swap_data(data_struct<T>& io_data_struct_a, data_struct<T>& io_data_struct_b) {

	io_data_struct_a.swap_data(io_data_struct_b);
	
}


// TODO: unify method with class hierachy
template <typename T>
void work_on_protected_data(protected_data_struct<T>& io_data_struct_a, protected_data_struct<T>& io_data_struct_b) {

	io_data_struct_a.work_on_data(io_data_struct_b);
}

template <typename T>
void swap_protected_data(protected_data_struct<T>& io_data_struct_a, protected_data_struct<T>& io_data_struct_b) {

	io_data_struct_a.swap_data(io_data_struct_b);

}

template <typename T>
void work_on_protected_data_no_deadlock(protected_data_struct<T>& io_data_struct_a, protected_data_struct<T>& io_data_struct_b) {

	io_data_struct_a.work_on_data_no_deadlock(io_data_struct_b);
}

template <typename T>
void swap_protected_data_no_deadlock(protected_data_struct<T>& io_data_struct_a, protected_data_struct<T>& io_data_struct_b) {

	io_data_struct_a.swap_data_no_deadlock(io_data_struct_b);

}


int main()
{

	// Example 1 - Data race
	std::cout<<"Example 1 - Data race case"<<std::endl;
	data_struct<int> data_struct_a(10);
	data_struct<int> data_struct_b(20);

	std::thread t1(work_on_data<int>,std::ref(data_struct_a),std::ref(data_struct_b));
	std::thread t2(swap_data<int>,std::ref(data_struct_a),std::ref(data_struct_b));

	t1.join();
	t2.join();

	std::cout<<std::endl;

	// Example 2 - Protected data access case
	std::cout<<"Example 2 - Protected data access case"<<std::endl;
	protected_data_struct<int> protected_data_struct_a(10);
	protected_data_struct<int> protected_data_struct_b(20);

	t1 = std::thread(work_on_protected_data<int>,std::ref(protected_data_struct_a),std::ref(protected_data_struct_b));
	t2 = std::thread(swap_protected_data<int>,std::ref(protected_data_struct_a),std::ref(protected_data_struct_b));

	t1.join();
	t2.join();


	std::cout<<std::endl;
	
    // Example 3 - Deadlock-ed protected data access case
	std::cout<<"Example 3 - Deadlock-ed protected data access case"<<std::endl;
		
/*	
	t1 = std::thread(swap_protected_data,std::ref(protected_data_struct_a),std::ref(protected_data_struct_b));
	t2 = std::thread(swap_protected_data,std::ref(protected_data_struct_b),std::ref(protected_data_struct_a));

	t1.join();
	t2.join();
*/

	std::cout<<std::endl;
	
 
	// Example 4 - Deadlock free protected data access case
	std::cout<<"Example 4 - Deadlock free protected data access case"<<std::endl;
	   
	t1 = std::thread(work_on_protected_data_no_deadlock<int>,std::ref(protected_data_struct_a),std::ref(protected_data_struct_b));
	t2 = std::thread(swap_protected_data_no_deadlock<int>,std::ref(protected_data_struct_b),std::ref(protected_data_struct_a));
	
	t1.join();
	t2.join();
		
}
