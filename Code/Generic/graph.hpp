#ifndef _GENERIC_GRAPH_HPP_
#define _GENERIC_GRAPH_HPP_

#include <unordered_map>
#include <list>
#include <algorithm>

namespace graphlib {

    /** Adjacency list graph
     */
    class al_graph {
    public:
        using nodeid_t = int;
    private:
        class node_t {
            bool m_mark = false;
            nodeid_t m_id;
            std::list<nodeid_t> m_neighbors;
        public:
            using iterator = std::list<nodeid_t>::iterator;
            using const_iterator = std::list<nodeid_t>::const_iterator;

            node_t () = default;
            node_t (nodeid_t id) : m_id(id) {}

            bool mark() {bool prev=m_mark; m_mark = true; return prev;}
            bool unmark() {bool prev=m_mark; m_mark = false; return prev;}
            bool is_marked() const {return m_mark;}
            nodeid_t id() const {return m_id;}
            void neighborhs(std::list<nodeid_t> && list) {
                m_neighbors = std::move(list);
            }

            iterator begin() {return m_neighbors.begin();}
            iterator end() {return m_neighbors.end();}
            const_iterator cbegin() const {return m_neighbors.cbegin();}
            const_iterator cend() const {return m_neighbors.cend();}

        };

        using storage_t = std::unordered_map<nodeid_t, node_t>;
    public:
        using iterator = storage_t::iterator;
        using const_iterator = storage_t::const_iterator;
    private:

        storage_t _data;
        bool has_mark = false;

    public:
        al_graph() = default;
        al_graph(std::initializer_list<nodeid_t> const& list)
            : has_mark(false)
        {
            std::for_each(list.begin(), list.end(),
                          [&](nodeid_t id) {
                              _data.insert({id, node_t{id}});
                          });
        }

        iterator begin() {return _data.begin();}
        iterator end() {return _data.end();}
        const_iterator cbegin() const {return _data.cbegin();}
        const_iterator cend() const {return _data.cend();}

        bool is_marked() const {return has_mark;}
        void set_as_marked() {has_mark=true;}

        bool mark(nodeid_t nodeid) {
            has_mark=true;
            auto node = _data[nodeid];
            return node.mark();
        }

        bool unmark(nodeid_t nodeid) {
            auto node = _data[nodeid];
            return node.unmark();
        }

        void mark() {
            std::for_each(begin(), end(), [](auto &n) {n.second.mark();});
            has_mark=true;
        }

        void unmark() {
            std::for_each(begin(), end(), [](auto &n) {n.second.unmark();});
            has_mark=false;
        }

        node_t& operator[](nodeid_t id) {
            return _data[id];
        }
        node_t const& operator[](nodeid_t id) const {
            return _data.at(id);
        }

    };


} // namespace graphlib
#endif
