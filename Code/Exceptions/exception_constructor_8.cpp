#include <string>
#include <iostream>
#include <memory>

struct Size{

  Size(int i_size)
    :m_size(i_size)
  {}

  void print() {
    std::cout<<"Illegal size error. Size value: "<<m_size<<std::endl;
  }

  int m_size;

};

class Vector{
public:
  
  Vector(int i_data_size)
    :m_data_size(i_data_size)
  {

    //    m_meta_data = new int[3];
    m_meta_data = std::unique_ptr<int>(new int[3]);

    // Check size request
    if(i_data_size > 1000 || i_data_size < 0)
      throw Size(i_data_size);    
  }
  
  ~Vector() {
  }

  Vector(const Vector&) = delete;
  Vector(Vector&&) = delete;
  
private:
  std::unique_ptr<int> m_meta_data;
  int m_data_size;

};

int main() {

  try {    
    Vector vec(-3);
  }
  catch(Size e) {
    e.print();
  }

}
