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
  
  MyType()
    :m_number_uncaught(std::uncaught_exceptions())
  {
    std::cout<<"Number uncaught exceptions - MyType ctor: "<<m_number_uncaught<<std::endl;
  }

  ~MyType() noexcept(false) 
  {
    std::cout<<"MyType dctor"<<std::endl;

    int number_uncaught_check = std::uncaught_exceptions();
    std::cout<<"Number uncaught exceptions - MyType ctor: "<<number_uncaught_check<<std::endl;
    if(number_uncaught_check == m_number_uncaught){
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
  int m_number_uncaught;

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
