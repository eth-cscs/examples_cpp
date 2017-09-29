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

// 1. Identify the memory leak problem (test with valgrind)
// 2. Fix the bug using smart pointers
class Vector{
public:
  
  Vector(int i_data_size)
    :m_data_size(i_data_size)
  {
    
    m_meta_data = new int[3];

    // Check size request
    if(i_data_size > 1000 || i_data_size < 0)
      throw Size(i_data_size);    
  }
  
  ~Vector() {

    if(m_meta_data) {
      delete [] m_meta_data;
      m_meta_data = nullptr;
    }

  }

  Vector(const Vector&) = delete;
  Vector(Vector&&) = delete;
  
private:
  int* m_meta_data;
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
