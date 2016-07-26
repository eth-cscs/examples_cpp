#include <iostream>
#include <vector>

void read(std::string & in) {
    std::cout << "Write something\n";
    std::cin >> in;
}

int main() {
    std::string input;
    read(input);
    std::vector<std::string> vector;

    while (input != "end") {
        std::cout << "inserting \"" << input << "\"\n";
        vector.push_back(std::move(input));
        std::cout << "What's left :\"" << input << "\"\n";
        read(input);
    }

    std::cout << "\n************\n\n";
    for (auto const& s: vector) {
        std::cout << s << "\n";
    }
}