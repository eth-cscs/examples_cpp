#include <iostream>
#include <array>
#include <cassert>
#include <cmath>
#include "../show.h"

// Suppose we have a class to store a point in a Dims dimensional space
// The following may be the primary template
template <typename Type, int Dims>
class point {
    std::array<Type, Dims> m_coord;

public:
    point() : m_coord{} {}

    point(std::array<Type, Dims> && list)
            : m_coord{list}
    {}

    std::string version() const {
        return "Primary template";
    }

    Type operator[](int i) const;
    Type& operator[](int i);

    double norm() const ;
};

// We can specialize it for integer fields and 3D spaces
// for which we may have a fast implementation for the operations
// (for instance using SSE instructions)
template <>
class point<int8_t, 3> {
    std::array<int8_t, 3> m_coord;

public:
    point() : m_coord{} {}

    point(std::array<int8_t,3> && list)
            : m_coord{list}
    {}

    std::string version() const {
        return "<int_8, 3>";
    }

    uint8_t operator[](int i) const;
    uint8_t& operator[](int i);

    double norm() const ;
};

template <int ND>
class point<int8_t, ND> {
    std::array<int8_t, ND> m_coord;

public:
    point() : m_coord{} {}

    point(std::array<int8_t,ND> && list)
            : m_coord{list}
    {}

    std::string version() const {
        return "<int_8, ND=" + std::to_string(ND) + ">";;
    }

    uint8_t operator[](int i) const;
    uint8_t& operator[](int i);

    double norm() const ;
};

/* It turns out the norm implementation is the same for almost all the
 * implementations, so we can save code
 */
template <typename T, int D>
inline double point<T,D>::norm() const {
    double res{};

    for (int8_t v : m_coord) {
        res += v * v;
    }
    return std::sqrt(static_cast<double>(res));
}

/* For the <int8_t, 3> version it's different
 */
//no need for template <>
inline double point<int8_t,3>::norm() const {
    double res{};
    std::cout << "I was cheating, it's the same\n";
    for (int8_t v : m_coord) {
        res += v * v;
    }
    return std::sqrt(static_cast<double>(res));
}

/* For the <int8_t, 3> version it's different
 */
template <int X>
inline double point<int8_t,X>::norm() const {
    double res{};
    std::cout << "I was cheating, it's the same\n";
    for (int8_t v : m_coord) {
        res += v * v;
    }
    return std::sqrt(static_cast<double>(res));
}

template <typename T, int D>
inline T point<T,D>::operator[](int i) const {
    return m_coord[i];
}

template <typename T, int D>
inline T& point<T,D>::operator[](int i) {
    return m_coord[i];
}

template <typename T, int D>
point<T,D> operator+(point<T,D> const& a, point<T,D> const& b) {
    point<T,D> res;
    for (int i = 0; i < D; ++i) {
        res[i] = a[i] + b[i];
    }
    return res;
};

int main() {
    point<double, 4> point1{{1.2,1.4,1.6,1.8}};
    point<int, 4>    point2{{1,2,3,4}};
    point<int8_t, 4> point3{{1,-2,3,-4}};
    point<int8_t, 3> point4{{-3,2,1}};

    SHOW(point1.version());
    SHOW(point2.version());
    SHOW(point3.version());
    SHOW(point4.version());

    SHOW(point1.norm());
    SHOW(point2.norm());
    SHOW(point3.norm());
    SHOW(point4.norm());

    // auto point5 = point1 + point<float, 4>{{-.2, -.4, -.6, -.8}}; // Error must match the types
    auto point5 = point1 + point<double, 4>{{-.2, -.4, -.6, -.8}};
}
