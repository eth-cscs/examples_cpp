#include "show.h"
#include <memory>

class Object{

public:
	
	Object(const int i_value):
		m_value(i_value)
		{}

	~Object() {

		std::cout<<"dctor"<<std::endl;
			
	}

	void setValue(const int i_value) { m_value = i_value; }

	int getValue() const { return m_value; }
	
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
	std::shared_ptr<Object> sp(this);
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

//#ifdef SMART
//	std::shared_ptr<Object> object(new Object(23));
//#else
	Object* object = new Object(23);
//#endif
	
	object->modify();
	
	SHOW(object->getValue());

//#ifndef SMART
	delete object;
//#endif
	
}



