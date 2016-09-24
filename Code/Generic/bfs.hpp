#ifndef _GENERIC_BFS_HPP_
#define _GENERIC_BFS_HPP_

#include <vector>
#include <stack>

namespace graphlib {


    /** What are the requirements on the Graph type?

        member functions:
        bool is_marked()
        /unspecified/ unmark()
        /unspecified/ set_as_marked()
        /something that can mark a node/ operator[nodeid_t]

        member types:
        nodeid_t

        nodes member functions:
        nodeid_t id()
        bool is_marked()
        /unspecified/ mark();

     */
    template <typename Graph>
    std::vector<typename Graph::nodeid_t>
    bfs(Graph& graph, typename Graph::nodeid_t source) {
        if (graph.is_marked()) graph.unmark();
        // the following set the graph in a marked state, since we want to
        // mark individual nodes without having to access them everytime
        // from the IDs of the nodes we already have in our hands later
        // on. So the graph class may be not
        graph.set_as_marked();
        std::vector<typename Graph::nodeid_t> out{source};

        std::stack<typename Graph::nodeid_t> stack;
        stack.push(source);
        graph[source].mark();

        while (!stack.empty()) {
            auto topid = stack.top();
            stack.pop();
            auto node = graph[topid];

            std::for_each(node.begin(), node.end(),
                          [&out, &stack, &graph](auto neighborid) {
                              // the next decltype(auto) is to support
                              // the case in which operator[] returns
                              // a reference or a proxy object passed
                              // back by value
                              decltype(auto) neighbor = graph[neighborid];
                              if (!neighbor.is_marked()) {
                                  stack.push(neighbor.id());
                                  neighbor.mark();
                                  out.push_back(neighbor.id());
                              }
                          });
        }
        return out;
    }
} // namespace graphlib


#endif
