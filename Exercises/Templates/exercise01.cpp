#include <string>
#include <iostream>

struct record_t {
    std::string firstname, lastname;
    int age;
};

std::ostream& operator<<(std::ostream &s, record_t const& x) {
    return s << "{ first: " << x.firstname << ", last: " << x.lastname << ", age: " << x.age << " }";
}

int main() {
    /* Implement afacility to make this code to work as expected */
auto record = record_t( lastname = "Bianco", age = 21, firstname = "Mauro" );
    std::cout << record << "\n";
}
