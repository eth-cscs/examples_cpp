#include <exception>
#include <iostream>

struct ExceptionTypeA {};
struct ExceptionTypeB {};
struct ExceptionTypeC : public ExceptionTypeB {};

void f1(void) throw (ExceptionTypeA,ExceptionTypeB)
{
  throw ExceptionTypeC();
}

void f2(void) throw ()
{
  throw std::exception();
}

int main() {

  try{

    f1();

  }
  catch(...){

    std::cout<<"Caught exception from f1()"<<std::endl;

  }

  try{

    f2();

  }
  catch(...){

    std::cout<<"Caught exception from f2()"<<std::endl;

  }


}
