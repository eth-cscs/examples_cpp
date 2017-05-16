#include <memory>
#include <iostream>
#include <cassert>

class Object{

public:

	Object(const int i_value):
		m_value(i_value)
		{}

	~Object(void){
		std::cout<<"When is the destructor called?"<<std::endl;
	}
	
	int getValue() const { return m_value; }

	void setValue(const int i_value) { m_value = i_value; }	
	
private:
	
	int m_value;
	
};

int main(){
	
	// 0 - Create managed resource, manager object and first shared pointer
	std::shared_ptr<Object> sp1(new Object(23));

	// 1 - What is the object stored value?
	assert(sp1->getValue() == 23);

	// 2 - How many pointers are pointing the same resource?
	assert(sp1.use_count() == 1);
	
	// 3 - Create some other shared pointers for the same resource... (use sp1)
	std::shared_ptr<Object> sp2(sp1); // With copy ctor
	std::shared_ptr<Object> sp3 = sp1; // With assignement operator
	std::shared_ptr<Object> sp4(std::move(sp1)); // With move constructor

	// 4 - How many pointers are pointing the same resource?  
	assert(sp1.use_count() == 0);
	assert(sp2.use_count() == 3);
	assert(sp3.use_count() == 3);
	assert(sp4.use_count() == 3);
	
	// 5 - Reset sp2
	sp2 = nullptr;

	// 6 - How many pointers are pointing the same resource?
    assert(sp1.use_count() == 0);
	assert(sp2.use_count() == 0);
	assert(sp3.use_count() == 2);
	assert(sp4.use_count() == 2);

	// 7 - What is the stored object value in sp4
	assert(sp4.get()->getValue()==23);

	// 8 - Set object value to 32
	(*sp3).setValue(32);
	assert(sp4->getValue()==32);

	// 9 - What is the status of sp1?
	assert(!sp1);

	// 10 - Create weak pointer using the existing resource
	std::weak_ptr<Object> wp1(sp3); // Using sp3

	// 11 - How many poninter are pointing to the same resource
	assert(wp1.use_count() == 2);
	assert(sp1.use_count() == 0);
	assert(sp2.use_count() == 0);
	assert(sp3.use_count() == 2);
	assert(sp4.use_count() == 2);

	// 12 - Create shared pointer sp5 using wp1 and check stored value
	std::shared_ptr<Object> sp5 = wp1.lock();
	assert(sp5->getValue() == 32);

    // 13 - How many poninter are pointing to the same resource
	assert(wp1.use_count() == 3);
	assert(sp1.use_count() == 0);
	assert(sp2.use_count() == 0);
	assert(sp3.use_count() == 3);
	assert(sp4.use_count() == 3);
	assert(sp5.use_count() == 3);
	
	// 14 - Reset sp3, sp4 and sp5
	sp3 = nullptr;
	sp4 = nullptr;
	sp5 = nullptr;
	
	// 15 - Is inner pointer of manager object pointing somewhere?
	assert(sp5.get()==nullptr);

	// 16 - Is the managed resource still available?
	assert(wp1.expired()==true);
	
	// 17 - When is the Object destructor called? (sp5 = nullptr)	
}



