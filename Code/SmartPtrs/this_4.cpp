#include "show.h"
#include <memory>

class Object : public std::enable_shared_from_this<Object>{

public:
	
	Object(const int i_value):
		m_value(i_value)
		{}

	~Object() {

		std::cout<<"dctor"<<std::endl;
			
	}

	
	
	int getValue() const { return m_value; }

	void setValue(const int i_value) { m_value = i_value; }	
	
	void modify(void);
		
private:
	
	int m_value;
	
};

#ifdef SMART

void workOnObject(const std::shared_ptr<Object> i_object) {

	// 0 - Add missing code
	i_object->setValue(32);

}


void Object::modify(void) {

	// 1 - Add missing code
	std::shared_ptr<Object> sp = shared_from_this();
	workOnObject(sp);
}

#else

void workOnObject(Object* const i_object) {
	
	i_object->setValue(32);
	
}

void Object::modify(void) {
	
	workOnObject(this);
	
}

#endif


int main(){

	std::shared_ptr<Object> object(new Object(23));
	
	object->modify();
	
	SHOW(object->getValue());
}



