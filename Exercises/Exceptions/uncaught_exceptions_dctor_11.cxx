#include <string>
#include <iostream>

struct MyException {

  MyException(const std::string& i_message)
    :m_message(i_message)
  {}

  std::string m_message;
};

// 1. Fix MyType class using std::uncaught_exceptions()
class MyType {
  
public:
  

  ~MyType() noexcept(false) 
  {
    if(???)
      freeResources();
    }
    else {
      freeResourcesSafe();
    }
  }

private:

  void freeResources() {
    std::cout<<"Executing freeResources"<<std::endl;
    throw MyException("Exception from freeResources");
  }

  void freeResourcesSafe() {
    std::cout<<"Executing freeResourcesSafe"<<std::endl;
  }

  // 2. Hint: you need a data member...

};

class MyOtherType {

public:
  
  ~MyOtherType() {

    std::cout<<"MyOtherType dctor"<<std::endl;
    try {
      MyType myType;
    }
    catch(MyException e) {

      std::cout<<"Exception caught in ~MyOtherType()"<<std::endl;       
      std::cout<<"Error: "<<e.m_message<<std::endl;
    }
  }
};

void f() {

  try {

    MyOtherType myOtherType;
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
