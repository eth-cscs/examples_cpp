#include <iostream>
#include "graph.hpp"
#include "bfs.hpp"

template <typename Graph, typename Src>
void test_from(Graph & G, Src s) {
    auto r1 = bfs(G, s);
    std::cout << "Starting at " << s << ": {";
    for (auto i: r1) {std::cout << i << ", ";}
    std::cout << "}\n";
}

int main() {
    using namespace graphlib;

    al_graph G{3,7,4,6};

    G[3].neighborhs({4,6});
    G[7].neighborhs({3});
    G[4].neighborhs({7});
    G[6].neighborhs({});

    test_from(G, 7);
    test_from(G, 3);
    test_from(G, 4);
    test_from(G, 6);
}
