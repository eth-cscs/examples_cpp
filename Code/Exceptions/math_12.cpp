#include <cmath>
#include <cfenv>
#include <iostream>

int main() {
  
  std::feclearexcept(math_errhandling);
  double logval = std::log(-1.);
  if(std::fetestexcept(math_errhandling)) {
    
    if(std::fetestexcept(FE_DIVBYZERO)){
      std::cout<<"Error: division by zero"<<std::endl; 
    }
    else if(std::fetestexcept(FE_OVERFLOW)){
      std::cout<<"Error: overflow"<<std::endl; 
    } 
    else if(std::fetestexcept(FE_INVALID)){
      std::cout<<"Error: invalid value"<<std::endl; 
    }
    
  }
}
