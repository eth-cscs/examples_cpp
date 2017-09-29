#include <iostream>
#include <string>

struct MyException{};
struct MyOtherException{};

struct MyType {

  MyType(const std::string& i_scope)
    :m_scope(i_scope)
  {}

  ~MyType()
  {
    std::cout<<"MyType dctor in: "<<m_scope<<std::endl;
  }
  
  std::string m_scope;
  
};

void f3() {

  MyType a("f3");

  throw MyException();
}


void f2() {

  MyType a("f2");

  try {
    f3();
  }
  catch(MyOtherException)
  {
    std::cout<<"Exception caught in f2"<<std::endl;
  }
}

void f1() {
  
  MyType a("f1");
  
  try {
    
    f2();
  }
  catch(MyException) 
  {
    std::cout<<"Exception caught in f1"<<std::endl;
  }
  
}

int main() {

  try {
    
    MyType a("main");
    
    f1();
  
  }
  catch(MyException)
  {
    std::cout<<"Exception caught in main"<<std::endl;
  }
  
}
