#include <memory>
#include <iostream>
#include <string>
#include <cassert>

struct Base{

	virtual std::string f(void) const { return "Base"; }
};


struct Derived : public Base {

    std::string f(void) const { return "Derived"; }
};


int main(){

	// 0 - Update using only std::shared_ptr
	std::shared_ptr<Base> sp_base(new Derived);

	// 1 - What is the called f() method?
	assert(sp_base->f() == "Derived");
}
