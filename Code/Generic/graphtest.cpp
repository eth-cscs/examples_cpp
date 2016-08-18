#include <iostream>
#include <iomanip>
#include "graph.hpp"
#include "bfs.hpp"

template <typename Graph, typename Src>
void test_from(Graph & G, Src s) {
    auto r1 = bfs(G, s);
    std::cout << "Starting at " << s << ": {";
    for (auto i: r1) {std::cout << i << ", ";}
    std::cout << "}\n";
}

template <typename GType>
void run() {
    GType G{3,7,4,6};
    G[3].neighbors({4,6});
    G[7].neighbors({3});
    G[4].neighbors({7});
    G[6].neighbors({});

    test_from(G, 7);
    test_from(G, 3);
    test_from(G, 4);
    test_from(G, 6);
}

int main() {
    using namespace graphlib;

    run<al_graph>();
    run<am_graph>();
}
