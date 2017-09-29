#include <exception>
#include <iostream>

struct MyException {
  
  std::string getExceptionType() const { return "MyException"; }
  
};

void handle_exception_pointer(std::exception_ptr exc_ptr) {

  try {
    if(exc_ptr) {   
      std::rethrow_exception(exc_ptr);
    }
  }
  catch(std::exception e) {
    std::cout<<e.what()<<std::endl;
  }
  catch(MyException e) {
    std::cout<<e.getExceptionType()<<std::endl;
  }
}

int main() {

  std::exception_ptr exc_ptr;
   try {
     throw std::exception();
  }
  catch(...) {
    exc_ptr = std::current_exception();
  }  
  handle_exception_pointer(exc_ptr);

  try {
    throw MyException();
  }
  catch(...) {
    exc_ptr = std::current_exception();
  }
  handle_exception_pointer(exc_ptr);

};
