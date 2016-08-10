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

// TODO: usare show di Mauro

int main(){
	
	// 0 - Create managed resource, manager object and first shared pointer
	std::shared_ptr<Object> sp1(new Object(23));

	// 1 - What is the object stored value?
	assert(sp1->? == ?);

	// 2 - How many pointers are pointing the same resource?
	assert(sp1.? == ?);
	
	// 3 - Create some other shared pointers for the same resource...
	std::shared_ptr<Object> sp2?; // With copy ctor
	std::shared_ptr<Object> sp3?; // With assignement operator
	std::shared_ptr<Object> sp4?; // With move constructor

	// 4 - How many pointers are pointing the same resource?  
	assert(sp1.? == ?);
	assert(sp2.? == ?);
	assert(sp3.? == ?);
	assert(sp4.? == ?);
	
	// 5 - Reset sp2
	sp2 = ?;

	// 6 - How many pointers are pointing the same resource?
    assert(sp1.? == ?);
	assert(sp2.? == ?);
	assert(sp3.? == ?);
	assert(sp4.? == ?);

	// 7 - What is the stored object value in sp4
	assert(sp4.get()->?==?);

	// 8 - Set object value to 32
	(*sp3).?;
	assert(sp4->?==?);

	// 9 - What is the status of sp1?
	assert(?sp1);

	// 10 - Create weak pointer using the existing resource
	std::weak_ptr<Object> wp1?

	// 11 - How many poninter are pointing to the same resource
	assert(wp1.? == ?);
	assert(sp1.? == ?);
	assert(sp2.? == ?);
	assert(sp3.? == ?);
	assert(sp4.? == ?);

	// 12 - Create shared pointer sp5 using wp1 and check stored value
	std::shared_ptr<Object> sp5 = wp1.?;
	assert(sp5->? == ?);

    // 13 - How many poninter are pointing to the same resource
	assert(wp1.? == ?);
	assert(sp1.? == ?);
	assert(sp2.? == ?);
	assert(sp3.? == ?);
	assert(sp4.? == ?);
	assert(sp5.? == ?);
	
	// 14 - Reset sp3, sp4 and sp5
	sp3 = ?;
	sp4 = ?;
	sp5.?;
	
	// 15 - Is inner pointer of manager object pointing somewhere?
	assert(sp5.?==?);

	// 16 - Is the managed resource still available?
	assert(wp1.?==true);
	
	// 17 - When is the Object destructor called?
}



