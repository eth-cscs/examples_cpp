#include <iostream>
#include <string>

struct MyException {

  MyException(const std::string& i_message)
    :m_message(i_message)
  {}

  std::string m_message;
};


class MyType {

public:

  ~MyType() noexcept(false) 
  {
    freeResources();
  }

private:

  void freeResources() {
    throw MyException("Exception from dctor");
  }

};

void f() {

  try {
    
    MyType myType;
    throw MyException("Exception from f");

  }
  catch(MyException e) {
    
    std::cout<<"Exception caught in f()"<<std::endl; 
    std::cout<<"Error: "<<e.m_message<<std::endl;
  }

}


int main() {

  f();

}
