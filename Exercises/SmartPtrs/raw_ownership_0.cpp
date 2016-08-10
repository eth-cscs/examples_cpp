#include <utility>

// TODO: switch to non array data type

class Owner {
private:
	double* m_data;
public:
	Owner(const unsigned int i_size):
		m_data(new double[i_size])
		{}
};

void f(const Owner& i_owner) {
	Owner tmp_owner(i_owner);	
}

int main() {
	const unsigned int size = 10;
	Owner first_owner(size);
	Owner second_owner = first_owner;
	Owner third_owner(std::move(first_owner));
}
