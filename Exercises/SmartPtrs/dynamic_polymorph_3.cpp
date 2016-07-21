#include <memory>
#include <iostream>

struct Base{

	virtual void f(void) const { std::cout<<"Call base method"<<std::endl; }

	virtual ~Base(){
		std::cout<<"Call base dctor"<<std::endl;
	}

};


struct Derived : public Base {

	void f(void) const { std::cout<<"Call derived method"<<std::endl; }

	~Derived(){
		std::cout<<"Call derived dctor"<<std::endl;
	}

};


int main(){

	// 0 - Update to smart pointer implementation
	// TODO: we need something more complex
	Base* p_base = new Derived();
	p_base->f();
	delete p_base;
}
