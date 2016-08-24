#include <utility>

class Owner {

private:
	double* m_data;
	
public:
	Owner(const double i_data):
		m_data(new double(i_data))
		{
		}

	Owner(const Owner& i_owner):
		m_data(new double)
		{
			*m_data = *i_owner.m_data;
		}
	
	Owner(Owner&& i_owner):
		m_data(i_owner.m_data)
		{
			i_owner.m_data = nullptr;
		}
	
	~Owner() {
		if(m_data!=nullptr)
			delete m_data;
	}
	
	double get_data() const { return *m_data; }	
	
	Owner& operator=(const Owner& i_owner){
		m_data = new double;
		*m_data = *i_owner.m_data;
	}

	Owner& operator=(Owner&& i_owner){
		m_data = i_owner.m_data;
		i_owner.m_data = nullptr;
	}
	
};

void f(const Owner& i_owner) {
	Owner tmp_owner(i_owner);	
}

int main() {
	Owner first_owner(23.);	
	Owner second_owner = first_owner;
	Owner third_owner(std::move(first_owner));
	f(third_owner);
}
