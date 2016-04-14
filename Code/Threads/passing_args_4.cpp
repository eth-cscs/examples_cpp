#include <thread>
#include <iostream>


class X{

public:
	void set(int i_int) { m_int=i_int; }
	int get(void) const { return m_int; }
	
private:
	int m_int;
	
};

void setX(int i_int, X& io_x)
{
	io_x.set(i_int);
}

void setX_ptr(int i_int, X* io_x)
{
	io_x->set(i_int);
}

int main()
{
	X x;
	
	std::thread t(setX, 1, std::ref(x));
//	std::thread t(setX, 1, x); // Error explanation
	t.join();
	std::cout<<"x int value: "<<x.get()<<std::endl;

	t = std::thread(setX_ptr, 2, &x);
    t.join();
	std::cout<<"x int value: "<<x.get()<<std::endl;

	t = std::thread(&X::set, &x, 3);
	t.join();
	std::cout<<"x int value: "<<x.get()<<std::endl;
}
