#include <iostream>
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
	std::shared_ptr<Object> sp = shared_from_this();
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

	std::shared_ptr<Object> object(new Object(23));
	
	object->modify(32);
	
	std::cout<<"object->getValue() "<<object->getValue()<<std::endl;;
}



