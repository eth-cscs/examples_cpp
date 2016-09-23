#include <memory>
#include <cassert>

class Object{

public:

	Object() = default;
	
	Object(const int i_value):
		m_value(i_value)
		{}
	
	int getValue() const { return m_value; }

	void setValue(const int i_value) { m_value = i_value; }	
	
private:
	
	int m_value;
	
};

int main(){
	
	// 0 - Create managed resource, manager object and first shared pointer
	std::shared_ptr<Object> sp1(new Object(23));

	// 1 - Create a new Object on the stack
	Object stack_ob(3);

	// 2 - Create a shared_ptr from the stack object
	std::shared_ptr<Object> sp2(&stack_ob);

	// 3 - Create a new shared_ptr from sp1
	std::shared_ptr<Object> sp3(sp1.get());

	// 4 - How many pointers are pointing the same resource?
	assert(sp1.use_count() == 1);
	assert(sp2.use_count() == 0);
	assert(sp3.use_count() == 1);

	// 5 - Create a shared_ptr to array
	std::shared_ptr<Object> sp4(new Object[10]);
	
	// Find the bugs!
}



