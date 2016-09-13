#include <iostream>
#include <iomanip>
#include "graph.hpp"
#include "bfs2.hpp"
#include <functional>

template <typename Graph, typename Src, typename MK, typename CM>
void test_from(Graph & G, Src s, MK&& marker, CM&& checkmark) {
    auto&& r1 = bfs(G, s, std::forward<MK>(marker), std::forward<CM>(checkmark));
    std::cout << "Starting at " << s << ": {";
    for (auto i: r1) {std::cout << i << ", ";}
    std::cout << "}\n";
}

class marker_t {
    std::unordered_map<int, bool> m_marks;

    void show(std::string const& prefix) const {
        // std::cout << prefix << " - The MARKS ";
        // std::for_each(m_marks.begin(), m_marks.end(),
        //               [](auto& x) { std::cout << "("
        //                                       << x.first << ", "
        //                                       << std::boolalpha << x.second
        //                                       << ") "; }
        //               );
        // std::cout << "\n";
    }
public:
    // returns the previous mark
    bool mark(int id) {
        show("MARK");
        auto it = m_marks.find(id);
        if (it != m_marks.end()) {
            bool prev = it->second;
            it->second = true;
            return prev;
        } else {
            m_marks.insert(std::make_pair(id, true));
            return false;
        }
    }

    bool is_marked(int id) const {
        show("IS_MARKED");
        auto it = m_marks.find(id);
        if (it != m_marks.end()) {
            return it->second;
        } else {
            return false;
        }
    }

    void unmark_all() {
        std::for_each(m_marks.begin(), m_marks.end(),
                      [](auto& x) { x.second = false; }
                      );
    }
};

template <typename GType>
void run() {
    using namespace std::placeholders;
    GType G{3,7,4,6,8};
    G[3].neighbors({4,7});
    G[7].neighbors({6,8});
    G[4].neighbors({7,8});
    G[6].neighbors({7,8});
    G[8].neighbors({6});

    marker_t marker;

    test_from(G, 7, std::bind(&marker_t::mark, &marker, _1), std::bind(&marker_t::is_marked, &marker, _1));
    marker.unmark_all();
    test_from(G, 3, std::bind(&marker_t::mark, &marker, _1), std::bind(&marker_t::is_marked, &marker, _1));
    marker.unmark_all();
    test_from(G, 4, std::bind(&marker_t::mark, &marker, _1), std::bind(&marker_t::is_marked, &marker, _1));
    marker.unmark_all();
    test_from(G, 6, std::bind(&marker_t::mark, &marker, _1), std::bind(&marker_t::is_marked, &marker, _1));
    marker.unmark_all();
    test_from(G, 8, std::bind(&marker_t::mark, &marker, _1), std::bind(&marker_t::is_marked, &marker, _1));
}

int main() {
    using namespace graphlib;

    run<al_graph>();
    run<am_graph>();
}
