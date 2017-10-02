#include <memory>
#include <cassert>

struct Base{

	virtual bool f(void) const { return false; }
};


struct Derived : public Base {

	bool f(void) const { return true; }

	void setter(void) {}

};

void f(std::shared_ptr<const Derived> i_derived) {

    std::const_pointer_cast<Derived>(i_derived)->setter();
}

int main(){

	// 0 - Create shared_ptr to Base object type
	std::shared_ptr<Base> sp_base(new Base);

    // 1 - Create shared_ptr to Derived object type
    std::shared_ptr<Derived> sp_derived(new Derived);

    // 2 - Static upcast of sp_derived to a new shared_ptr to base type
    std::shared_ptr<Base> sp_base_from_derived = sp_derived;

	// 3 - Check smart pointer count
    assert(sp_derived.use_count() == 2);

	// 4 - Static downcast of sp_base_from_derived to a shared_ptr to Derived object type
	std::shared_ptr<Derived> sp_derived_from_base = std::static_pointer_cast<Derived>(sp_base_from_derived);

	// 5 - Check smart pointer count
    assert(sp_derived.use_count() == 3);

	// 6 - Which method are we calling?
    assert(sp_base_from_derived->f()==true);

	// 7 - Dynamic downcast of sp_base to a shared_ptr to Derived object type
	std::shared_ptr<Derived> sp_derived_dyna_cast_from_base = std::dynamic_pointer_cast<Derived>(sp_base);

	// 8 - Check smart pointer validity
	assert(sp_derived_dyna_cast_from_base==nullptr);

	// 9 - Complete my code and call the non const method on sp_const_derived
    f(sp_derived);

}
