#include <exception>

int test_fun(bool error) {

  /*
  int error_status = 0;
 
  if(error){
    error_status = 1;
  }
  return error_status;
  */
  
  return 0;
}

void test_fun_exc(bool error) {
  /*
  if(error){
    throw std::exception();
  }
  */
}

const int N_IT = 10000000;

int main(){

  
  int error_status = 0;

#if 1
  for(unsigned int i=0;i<N_IT;i++){
    
    error_status = test_fun(i%2);
    if(error_status){
      error_status = 2;
    }

  }
#endif

#if 0

  for(unsigned int i=0;i<N_IT;i++){
    
    try {
      test_fun_exc(i%2);
    }
    catch(std::exception) {
      error_status = 2;
    }
  }

#endif

}
