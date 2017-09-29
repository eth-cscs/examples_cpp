#ifndef _GENERIC_GRAPH_HPP_
#define _GENERIC_GRAPH_HPP_

#include <unordered_map>
#include <list>
#include <algorithm>
#include <cassert>
#include <vector>

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
            void neighbors(std::list<nodeid_t> && list) {
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


    /** Adjacensy matrix implementation */
    class am_graph {
    public:
        using nodeid_t = int;

    private:
        class node_t {
            bool _is_neighbor = false;

        public:
            node_t() = default;
            node_t(bool v) : _is_neighbor(v) {}

            bool is_neighbor() const {return _is_neighbor;}

            void set_neighbor(bool v) {_is_neighbor = v;}
        };

        std::vector<node_t> _data;
        std::vector<int> _indices;
        std::vector<int> _marks;

        class row_proxy {
            am_graph& _p_graph;
            int _index;

            class neighbor_proxy {
                row_proxy& _proxy;

            public:
                class iterator {
                    row_proxy& _i_proxy;
                    int _index;

                public:
                    iterator(row_proxy& p, int i) : _i_proxy(p), _index(i) {}

                    iterator operator++() {
                        _index++;
                        while (_index < _i_proxy.total_length() && !_i_proxy[_index])
                            ++_index;
                        return *this;
                    }
                    bool operator!=(iterator const b) const {
                        return (_index != b._index);
                    }

                    nodeid_t operator*() {
                        return _i_proxy.graph().id_(_index);
                    }

                }; // class iterator

                neighbor_proxy(row_proxy & p) : _proxy(p) {}

                iterator begin() const {
                    int i = 0;
                    while (!_proxy[i]) ++i;
                    return iterator(_proxy, i);
                }

                iterator end() const {
                    return iterator(_proxy, _proxy.total_length());
                }

            }; //class neighbor_proxy
        public:
            row_proxy(am_graph & data, int index)
                : _p_graph(data), _index(index)
            {}

            am_graph& graph() {return _p_graph;}

            neighbor_proxy neighbors() {
                return neighbor_proxy(*this);
            }

            neighbor_proxy neighbors(std::initializer_list<nodeid_t> const& list) {

                std::for_each(list.begin(), list.end(),
                              [&](auto id) {
                                  auto p = std::equal_range(_p_graph._indices.begin(), _p_graph._indices.end(), id);
                                  assert(p.first+1 == p.second);
                                  _p_graph(_index, p.first-_p_graph._indices.begin()).set_neighbor(true);
                              });
                return neighbor_proxy(*this);
            }

            typename neighbor_proxy::iterator begin() {
                return neighbor_proxy(*this).begin();
            }

            typename neighbor_proxy::iterator end() {
                return neighbor_proxy(*this).end();
            }

            void mark() {
                _p_graph.mark_(_index);
            }

            int total_length() const {return _p_graph.size();}

            bool is_marked() {
                return _p_graph.is_marked_(_index);
            }
            nodeid_t id() const {
                return _p_graph.id_(_index);
            }
        protected:
            bool operator[](int i) const {
                return _p_graph._data[_index*total_length()+i].is_neighbor();
            }
        }; // class row_proxy

    friend class am_graph::row_proxy;
    public:
        am_graph(std::initializer_list<nodeid_t> const& list)
            : _data(list.size()*list.size())
            , _indices(list.size())
            , _marks(list.size(), false)
        {
            std::copy(list.begin(), list.end(), _indices.begin());
            std::sort(_indices.begin(), _indices.end());
        }

        void out() {
            for (int i = 0; i < _indices.size(); ++i) {
                for (int j = 0; j < _indices.size(); ++j) {
                    std::cout << std::setw(7) << operator()(i,j).is_neighbor();
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }

        row_proxy operator[](nodeid_t id) {
            auto p = std::equal_range(_indices.begin(), _indices.end(), id);
            assert(p.first+1 == p.second);
            return row_proxy(*this, p.first-_indices.begin());
        }

        int size() const {return _indices.size();}

        bool is_marked() const {return true;}
        void set_as_marked() {}

        void unmark() {
            std::for_each(_marks.begin(), _marks.end(),
                          [](auto& v) {
                              v = false;
                          });
        }

        bool mark(nodeid_t id) {
            auto p = std::equal_range(_indices.begin(), _indices.end(), id);
            assert(p.first+1 == p.second);
            bool res = _marks[p.first-_indices.begin()];
            _marks[p.first-_indices.begin()] = true;
            return res;
        }

        void mark_(nodeid_t i) {
            _marks[i] = true;
        }

        bool is_marked_(nodeid_t i) {
            return _marks[i];
        }

        nodeid_t id_(nodeid_t i) {
            return _indices[i];
        }

        node_t& operator()(int i, int j) {
            return _data[i*_indices.size()+j];
        }

    };
} // namespace graphlib
#endif
