#include <thread>
#include <mutex>
#include <iostream>
#include <list>
#include <cstdlib>

std::list<int> elements;
std::mutex mutex;

void add(unsigned int i_num_elements){


  for(unsigned int i=0;i<i_num_elements;++i)
    elements.push_back(0);

  return;

}

void protected_add(unsigned int i_num_elements){

  //  std::mutex mutex;// What if I decomment this line?

  mutex.lock();

  for(unsigned int i=0;i<i_num_elements;++i)
    elements.push_back(0);

  mutex.unlock();

  return;

}


void protected_guard_add(unsigned int i_num_elements){

  std::mutex mutex;// What if I decomment this line?                                                                                                                                                                                                                                                                      
  std::lock_guard<std::mutex> guard(mutex);
  for(unsigned int i=0;i<i_num_elements;++i)
    elements.push_back(0);


  return;

}

void protected_guard_add_ref(unsigned int i_num_elements, std::list<int>& io_elements){

  
  // std::lock_guard<std::mutex> guard(mutex);
  for(unsigned int i=0;i<i_num_elements;++i)
    io_elements.push_back(0);  
 
  return;

}

int main()
{

  //  srand (time(NULL));

  unsigned int num_elements_1 = rand() % 1000;
  unsigned int num_elements_2 = rand() % 1000;

  //// Non protected element add case
  std::thread t1(add, num_elements_1);
  std::thread t2(add, num_elements_2);
 
  t1.join();
  t2.join();
  
  std::cout<<"Num elements (non protected case): "<<elements.size()<<" vs "<<num_elements_1+num_elements_2<<std::endl;
  ////

  //// Protected element add case (lock/unlock)
  elements.clear();
  
  t1 = std::thread(protected_add, num_elements_1);
  t2 = std::thread(protected_add, num_elements_2);

  t1.join();
  t2.join();

  std::cout<<"Num elements (protected case): "<<elements.size()<<" vs "<<num_elements_1+num_elements_2<<std::endl;
  ////

  //// Protected element add case (with lock guard)
  elements.clear();

  t1 = std::thread(protected_guard_add, num_elements_1);
  t2 = std::thread(protected_guard_add, num_elements_2);

  t1.join();
  t2.join();

  std::cout<<"Num elements (protected guard case): "<<elements.size()<<" vs "<<num_elements_1+num_elements_2<<std::endl;
  ////

  //// Protected element add case referencing a non global variable (with lock guard)
  std::list<int> local_elements;

  t1 = std::thread(protected_guard_add_ref, num_elements_1, std::ref(local_elements));
  t2 = std::thread(protected_guard_add_ref, num_elements_2, std::ref(local_elements));

  t1.join();
  t2.join();

  std::cout<<"Num elements (protected guard case/ref): "<<local_elements.size()<<" vs "<<num_elements_1+num_elements_2<<std::endl;
  ////

}
