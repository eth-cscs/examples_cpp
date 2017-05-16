#include <iostream>
#include <thread>

void f() {

	std::cout<<"Start work in f()"<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout<<"Work in f() finished"<<std::endl;
}

class thread_guard{

private:

	std::thread* t;

public:

	thread_guard(std::thread&& i_thread) = delete;

	thread_guard(std::thread& i_thread){
		t = &i_thread;
	}
	
	~thread_guard(){
		
		if(t->joinable()){
			t->join();
		}
	}
	
	thread_guard(thread_guard const &) = delete;
	thread_guard& operator=(thread_guard const &) = delete;
	
};


int main(){
	
	std::thread t(f);
	thread_guard tg(t);
	// Do we need to join t?
}
