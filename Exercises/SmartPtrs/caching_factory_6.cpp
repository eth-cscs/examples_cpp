#include <memory>
#include <cassert>
//#include <iostream>
#include <unordered_map>

struct Object {

	Object(const unsigned int i):
		m_value(i)
		{
//			std::cout<<"Ctor called with "<<i<<std::endl;
			// ...expensive operations
		}

	int m_value;
	
};

Object* factory(const unsigned int i){

	return new Object(i);
}

static std::unordered_map<int,std::weak_ptr<Object> > cache;

std::shared_ptr<Object> cachedFactory(const unsigned int i){

	auto objPtr = cache[i].lock();

	if(!objPtr){
		objPtr = factory(i);
		cache[i] = objPtr;
	}

	return objPtr;
}

int main(){

	// 1 - Build obj shared_ptr with slow factory method
	std::shared_ptr<Object> sp1(factory(3));

	// 2 - Build obj shared ptr with fast factory method
	auto sp2(cachedFactory(3));

	// 3 - Build obj shared ptr with fast factory method
	auto sp3(cachedFactory(3));

	// 4 - Find reference count of sp3
	assert(sp1.use_count()==?);
	assert(sp2.use_count()==?);

	// 5 - How many calls to Object ctor?
}
