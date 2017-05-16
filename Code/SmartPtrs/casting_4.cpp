#include <memory>
#include <cassert>

struct Base{

	virtual bool f(void) const { return false; }	
};


struct Derived : public Base {
	
	bool f(void) const { return true; }

	void setter(void) {}
		
};


bool f(std::shared_ptr<const Base> i_sp_base) {

	// 7 - Dynamic downcast to a shared_ptr to Derived object type 
	std::shared_ptr<const Derived> sp_derived_cast_from_base = std::static_pointer_cast<const Derived>(i_sp_base);
	return sp_derived_cast_from_base->f();
		
}

int main(){

	// 0 - Create shared_ptr to Base object type
	std::shared_ptr<Base> sp_base(new Base);

	// 1 - Static downcast to a shared_ptr to Derived object type
	std::shared_ptr<Derived> sp_cast_from_base = std::static_pointer_cast<Derived>(sp_base);

	// 2 - Which method are we calling?
    assert(sp_cast_from_base->f()==false);

	// 3 - Check smart pointer count
	assert(sp_base.use_count() == 2);
	assert(sp_cast_from_base.use_count()==2);

	// 4 - Dynamic downcast to a shared_ptr to Derived object type
	std::shared_ptr<Derived> sp_dyna_cast_from_base = std::dynamic_pointer_cast<Derived>(sp_base);

	// 5 - Check smart pointer validity
	assert(sp_dyna_cast_from_base==nullptr);

	// 6 - Call a function waiting for a shared_ptr to Base passing a shared_ptr to Derived
	assert(f(std::shared_ptr<const Derived>(new Derived)));

	// 8 - Complete my code and call the non const method on sp_const_derived
	std::shared_ptr<const Derived> sp_const_derived(new Derived);
	std::const_pointer_cast<Derived>(sp_const_derived)->setter();
	
}
