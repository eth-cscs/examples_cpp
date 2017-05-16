#include "../show.h"

struct instr_t {
    using basic_type = unsigned;
    basic_type oper  : 3;
    basic_type cond1 : 2;
    basic_type val1  : 3;
    basic_type cond2 : 2;
    basic_type val2  : 3;
    basic_type act   : 3;
    basic_type cell  : 4;
    basic_type : sizeof(basic_type)*8-21; // unused (not necessary at the pad)
    basic_type :0; // Force starting a new unsigned: not really necessary here
    basic_type other; // regular data member
};

std::ostream& operator<<(std::ostream& s, instr_t a) {
    return s << "inst " << a.oper
             << ", " << a.cond1
             << ", " << a.val1
             << ", " << a.cond2
             << ", " << a.val2
             << ", " << a.act
             << ", " << a.cell << "\n";
}

int main() {
    SHOW(sizeof(instr_t));
    instr_t x = instr_t{33,34,5,3,3,4,12};
    for (int i=0; i<10; ++i) {
        SHOW(x);
        x.cond1 += 1;
    }

    // static_assert(instr_t{10}.oper == 2, "");
}
