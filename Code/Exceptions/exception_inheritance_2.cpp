#include <iostream>

class Matherr {

public:
  virtual void print_message() const { std::cerr<<"Math error"<<std::endl; }
    
};


class Zerodivide : public Matherr {

  int m_a, m_b;

public:
    
  Zerodivide(int i_a, int i_b)
    :m_a(i_a)
    ,m_b(i_b)
  {}
    
  virtual void print_message() const { std::cerr<<"Division by zero error: "<<m_a<<"/"<<m_b<<std::endl; }
    
};


int divide(int i_a, int i_b) {
    
  if(i_b == 0)
    throw Zerodivide(i_a, i_b);
    
  return i_a/i_b;
}


int main() {

  try{
    int div = divide(8,0);
  }
  catch(Matherr& e) {
    std::cout<<"Matherr exc caught"<<std::endl;
    e.print_message();    
  }
  catch(Zerodivide& e) {
    std::cout<<"Zerodivide exc caught"<<std::endl;
    e.print_message();
  }
  std::cout<<std::endl;

  try{
    int div = divide(8,0);
  }
  catch(Matherr e) {
    std::cout<<"Matherr exc caught"<<std::endl;
    e.print_message();    
  }
  catch(Zerodivide e) {
    std::cout<<"Zerodivide exc caught"<<std::endl;
    e.print_message();
  }
  std::cout<<std::endl;

  try{
    int div = divide(8,0);
  }
  catch(Zerodivide e) {
    std::cout<<"Zerodivide exc caught"<<std::endl;
    e.print_message();
  }
  catch(Matherr e) {
    std::cout<<"Matherr exc caught"<<std::endl;
    e.print_message();    
  }


}
