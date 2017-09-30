#include <exception>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "performance_fun.hpp"


int main(){

  int N_IT;
  std::cout<<"Enter number of loop iterations (I would suggest 10000000...): ";
  std::cin>>N_IT;
  if(N_IT<0){
    std::cout<<"Number of iteration must be non negative"<<std::endl;
    std::terminate();
  }

  std::srand(23);
  std::clock_t start;
  double duration;
  int rand_int;

  int error_status = 0;
  start = std::clock();
  for(unsigned int i=0;i<N_IT;i++){

    rand_int=std::rand()%2;
    error_status = test_fun(rand_int);
    if(error_status){
      error_status = 0;
    }

  }
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  std::cout<<"Loop duration (error status): "<<duration<<std::endl;


  start = std::clock();
  for(unsigned int i=0;i<N_IT;i++){

    rand_int=std::rand()%2;
    try {
      test_fun_exc(rand_int);
    }
    catch(std::exception) {
      error_status = 0;
    }
  }

  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  std::cout<<"Loop duration (exception handling): "<<duration<<std::endl;

}
