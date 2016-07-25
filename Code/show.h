#ifndef _EXAMPLES_CPP_CODE_SHOW_H_
#define _EXAMPLES_CPP_CODE_SHOW_H_
#include <iostream>

#define SHOW(X) std::cout << #X << " :  " << X << "\n";
#define SHOW_BOOL(X) std::cout << #X << " :  " << std::boolalpha << X << "\n";
#define SHOW_PREFIX(P,X) std::cout << P << "\n" << #X << "\n" << X << "\n";
#define OUT(B) std::ostream& operator<<(std::ostream &s, B a)
#endif
