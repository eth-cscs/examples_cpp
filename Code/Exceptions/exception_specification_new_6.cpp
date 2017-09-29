#include <exception>
#include <iostream>

void f1(void) noexcept(false)
{
  throw std::exception();
}

void f2(void) noexcept(true)
{
  throw std::exception();
}

void f3(void) noexcept(noexcept(f1())) {

  try{
    f1();
  }
  catch(...){
    throw;
  }

}


int main() {

  try{

    f1();

  }
  catch(...){

    std::cout<<"Caught exception from f1()"<<std::endl;

  }

  try{

    f3();

  }
  catch(...){

    std::cout<<"Caught exception from f3()"<<std::endl;

  }

  try{

    f2();

  }
  catch(...){

    std::cout<<"Caught exception from f2()"<<std::endl;

  }

}
