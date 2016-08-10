#include <utility>
#include <algorithm>

class Owner {

private:
	int m_size;
	double* m_data;

public:
	Owner(const unsigned int i_size):
		m_size(i_size),
		m_data(new double[i_size])
		{}

	Owner(const Owner& i_owner):
		m_size(i_owner.m_size),
		m_data(new double[i_owner.m_size])
		{
			std::copy(i_owner.m_data,i_owner.m_data+m_size,m_data);
		}

	Owner(Owner&& i_owner):
		m_size(i_owner.m_size),
		m_data(i_owner.m_data)
		{
			i_owner.m_data = nullptr;
		}
	
	~Owner() {
		if(m_data != nullptr)
			delete [] m_data;
	}

	Owner& operator=(const Owner& i_owner){
		m_size = i_owner.m_size;
		m_data = new double[i_owner.m_size];
		std::copy(i_owner.m_data,i_owner.m_data+m_size,m_data);
	}

	Owner& operator=(Owner&& i_owner){
		m_size = i_owner.m_size;
		m_data = i_owner.m_data;
		i_owner.m_data = nullptr;
	}
	
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
