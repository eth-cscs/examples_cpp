#include <memory>
#include <cassert>
#include <iostream>

class Object{

public:

	Object(void) = default;
	
	Object(const int i_value):
		m_value(i_value)
		{}

	int getValue() const { return m_value; }

	void setValue(const int i_value) { m_value = i_value; }

private:

	int m_value;

};

std::unique_ptr<Object> makeObject(const int i_value) {

	return std::unique_ptr<Object>(new Object(i_value));

}

int main() {

	// 0 - Create unique_ptr
	std::unique_ptr<Object> up1(new Object(23));

	// 1 - Transfer ownership
	std::unique_ptr<Object> up2(std::move(up1));

	// 2 - Transfer again
	std::unique_ptr<Object> up3 = std::move(up2);

	// 3 - Check ownership
	assert(up1==false);
	assert(up1.get()==nullptr);

	// 4 - Fix my Factory function using unique_ptr
	const int value(23);
	std::unique_ptr<Object> up4(makeObject(value));

	// 5 - Create a shared_ptr using same resource (owned by up4)
	std::shared_ptr<Object> sp1(std::move(up4));

	// 6 - Check ownership
	assert(!up4);
	assert(sp1);

	// 7 - Create a shared_ptr using makeObject
	std::shared_ptr<Object> sp2(makeObject(3));
}	
