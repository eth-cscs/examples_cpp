#include <exception>
#include <iostream>

int __attribute__ ((noinline)) test_fun(bool error) {
  
  int error_status = 0;
  
  if(error){
#ifdef SKIP_ERR
    error_status = 1;
#endif
  }

  return error_status;
}

void __attribute__ ((noinline)) test_fun_exc(bool error) {
  
  if(error){
#ifdef SKIP_ERR
    throw std::exception();
#endif
  }
  
}
