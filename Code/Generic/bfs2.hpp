#ifndef _GENERIC_BFS_HPP_
#define _GENERIC_BFS_HPP_

#include <vector>
#include <stack>

namespace graphlib {


    /** What are the requirements on the Graph type?

        member functions:
        /something that can mark a node/ operator[nodeid_t]

        member types:
        nodeid_t

        nodes member functions:
        nodeid_t id()
     */
    template <typename Graph, typename Marker, typename IsMarked>
    std::vector<typename Graph::nodeid_t>
    bfs(Graph& graph, typename Graph::nodeid_t source, Marker&& mark, IsMarked&& check_mark)
    {
        std::vector<typename Graph::nodeid_t> out{source};

        std::stack<typename Graph::nodeid_t> stack;
        stack.push(source);
        mark(graph[source].id());

        while (!stack.empty()) {
            auto topid = stack.top();
            stack.pop();
            auto node = graph[topid];

            std::for_each(node.begin(), node.end(),
                          [&out, &stack, &graph, &mark, &check_mark](auto neighborid) {
                              // the next decltype(auto) is to support
                              // the case in which operator[] returns
                              // a reference or a proxy object passed
                              // back by value
                              decltype(auto) neighbor = graph[neighborid];
                              if (!check_mark(neighbor.id())) {
                                  stack.push(neighbor.id());
                                  mark(neighbor.id());
                                  out.push_back(neighbor.id());
                              }
                          });
        }
        return out;
    }
} // namespace graphlib


#endif
