#include <memory>
#include <iostream>

struct Base{

	virtual void f(void) const { std::cout<<"Call base method"<<std::endl; }

	virtual ~Base(){
		std::cout<<"Call base dtor"<<std::endl;
	}

};


struct Derived : public Base {

	void f(void) const { std::cout<<"Call derived method"<<std::endl; }

	~Derived(){
		std::cout<<"Call derived dtor"<<std::endl;
	}

};


int main(){

	std::shared_ptr<Base> sp_base(new Derived);
	sp_base->f();

}
