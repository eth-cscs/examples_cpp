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
	
	void modify(const int i_value);
		
private:
	
	int m_value;
	
};

#ifdef SMART

void workOnObject(const int i_value, const std::shared_ptr<Object> i_object) {

	// 0 - Add missing code
	i_object->setValue(i_value);

}


void Object::modify(const int i_value) {

	// 1 - Add missing code
	std::shared_ptr<Object> sp(this);
	workOnObject(i_value,sp);
}

#else

void workOnObject(const int i_value, Object* const i_object) {
	
	i_object->setValue(i_value);
	
}

void Object::modify(const int i_value) {
	
	workOnObject(i_value,this);
	
}

#endif


int main(){

//#ifdef SMART
//	std::shared_ptr<Object> object(new Object(23));
//#else
	Object* object = new Object(23);
//#endif
	
	object->modify(32);
	
	SHOW(object->getValue());

//#ifndef SMART
	delete object;
//#endif
	
}



