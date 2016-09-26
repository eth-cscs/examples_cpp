#include <thread>
#include <memory>
#include <iostream>
#include <cassert>

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

void setX_move(int i_int,std::unique_ptr<X> i_ptr)
{
	i_ptr->set(i_int);
}

int main()
{
	X x;

	// 1- Check pass by reference mechanism
	std::thread t(setX, 1, std::ref(x));
	t.join();
	std::cout<<"x int value: "<<x.get()<<std::endl;

	t = std::thread(setX_ptr, 2, &x);
    t.join();
	std::cout<<"x int value: "<<x.get()<<std::endl;

	t = std::thread(&X::set, &x, 3);
	t.join();
	std::cout<<"x int value: "<<x.get()<<std::endl;

	// 2 - Move only argument type
	std::unique_ptr<X> ux(new X);
	ux->set(-3);
	t = std::thread(setX_move,23,std::move(ux));
	assert(!ux);
	t.join();
}
