#include <iostream>
#include <vector>
#include <ctime>

#define PRINT_OPERATION

// 3. TODO: optimize my code with exception specification
struct MyObject {

  MyObject(void)
  {
  }
  
  MyObject(int i_size)
  {
    m_data.resize(i_size);
  }


  MyObject(const MyObject& i_object)
    :m_data(i_object.m_data)
  {
#ifdef PRINT_OPERATION
    std::cout<<"cp ctor"<<std::endl;
#endif
  }
  
  MyObject(MyObject&& i_object)
    :m_data(std::move(i_object.m_data))
  {
#ifdef PRINT_OPERATION
    std::cout<<"mv ctor"<<std::endl;
#endif
  }


  MyObject& operator=(const MyObject& i_object)
  {
#ifdef PRINT_OPERATION
    std::cout<<"cp ="<<std::endl;
#endif
    m_data = i_object.m_data;
    return *this;
  } 

  MyObject& operator=(MyObject&& i_object) noexcept
  {
#ifdef PRINT_OPERATION
    std::cout<<"mv ="<<std::endl;
#endif
    m_data = std::move(i_object.m_data);
    return *this;
  }

  std::vector<int> m_data;

};


int main() {

  // 1. Create a std::vector of MyObject
  std::vector<MyObject> obj_va(10,MyObject(1000000));

  // 2. Resize (new memory location) 
  std::clock_t start;
  double duration;
  start = std::clock();  
  obj_va.resize(3000);
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;


  std::cout<<"Resize duration "<<duration<<std::endl;
    
}
