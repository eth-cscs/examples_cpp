#include <iostream>
#include <string>

struct MyException {

  MyException(std::string i_error_message)
    :m_error_message(i_error_message)
  {}

  std::string m_error_message;

};

void f3() {

  throw MyException("Throwing from f3().");

}

void f2() {

  try {
    f3();
  }
  catch(MyException& e) {
    e.m_error_message.append(" Rethrowing from f2().");
    throw;
  }

}

void f1() {

  try {
    f2();
  }
  catch(MyException& e) {
    e.m_error_message.append(" Rethrowing from f1().");
    throw;
  }

}


int main() {

  try {
    f1();
  }
  catch(MyException e) {
    std::cout<<e.m_error_message<<std::endl;
  }

}
