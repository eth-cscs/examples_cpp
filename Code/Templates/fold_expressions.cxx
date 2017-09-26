#include <string>
#include <iostream>

struct my_string {
    std::string s;

    my_string(std::string s) : s(s) {}
};

my_string paren(int i) {
    return "(" + std::to_string(i) + ")";
}

my_string operator+(my_string a, my_string b) {
    return my_string("+" + a.s + b.s);
}

std::ostream& operator<<(std::ostream& s, my_string const& a) {
    return s << a.s;
}

template <int ...Vs>
my_string concat1() {
    return (my_string("ciao") + ... + paren(Vs));
}

template <int ...Vs>
my_string concat2() {
    return (paren(Vs) + ... + my_string("ciao"));
}

template <int ...Vs>
my_string concat3() {
    return (... + paren(Vs));
}

template <int ...Vs>
my_string concat4() {
    return (paren(Vs) + ...);
}

int main() {
    /*
      Binary left fold (I op ... op E) becomes (((I op E1) op E2) op ...) op EN

      ((((("ciao" + paren(1)) + paren(2)) + paren(3)) + paren(4)) + paren(5))
      (((( "+ciao(1)" + paren(2)) + paren(3)) + paren(4)) + paren(5))
      ((( "++ciao(1)(2)" + paren(3)) + paren(4)) + paren(5))
      (( "+++ciao(1)(2)(3)" + paren(4)) + paren(5))
      ( "++++ciao(1)(2)(3)(4)" + paren(5))
      "+++++ciao(1)(2)(3)(4)(5)"
     */
    std::cout << concat1<1,2,3,4,5>() << "\n";

    /*
      Binary right fold (E op ... op I) becomes E1 op (... op (EN−1 op (EN op I)))

      paren(1) + (paren(2) + (paren(3) + (paren(4) + (paren(5) + "ciao"))))
      paren(1) + (paren(2) + (paren(3) + (paren(4) + "+(5)ciao")))
      paren(1) + (paren(2) + (paren(3) + "+(4)+(5)ciao"))
      paren(1) + (paren(2) + "+(3)+(4)+(5)ciao")
      paren(1) + "+(2)+(3)+(4)+(5)ciao"
      "+(1)+(2)+(3)+(4)+(5)ciao"
     */
    std::cout << concat2<1,2,3,4,5>() << "\n";

    /*
      Unary left fold (... op E) becomes ((E1 op E2) op ...) op EN

      ((((paren(1) + paren(2)) + paren(3)) + paren(4)) + paren(5))
      ((("+(1)(2)" + paren(3)) + paren(4)) + paren(5))
      (("++(1)(2)(3)" + paren(4)) + paren(5))
      ("+++(1)(2)(3)(4)" + paren(5))
      "++++(1)(2)(3)(4)(5)"

     */
    std::cout << concat3<1,2,3,4,5>() << "\n";

    /*
      Unary right fold (E op ...) becomes E1 op (... op (EN-1 op EN))

      paren(1) + (paren(2) + (paren(3) + (paren(4) + paren(5))))
      paren(1) + (paren(2) + (paren(3) + "+(4)(5)"))
      paren(1) + (paren(2) + "+(3)+(4)(5)")
      paren(1) + "+(2)+(3)+(4)(5)"
      "+(1)+(2)+(3)+(4)(5)"
     */
    std::cout << concat4<1,2,3,4,5>() << "\n";
}
