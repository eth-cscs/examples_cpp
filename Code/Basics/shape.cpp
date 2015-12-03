// -*- compile-command: "g++ -std=c++11 shape.cpp -o shape" -*-x

/*
// Some of the code in this example comes from Kokkos, from there the
// following copyright notice
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2014) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact  H. Carter Edwards (hcedwar@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include <iostream>
#include <tuple>

template <unsigned ScalarSize, unsigned Rank, unsigned S0=1, unsigned S1=1, unsigned S2=1, unsigned S3=1, unsigned S4=1, unsigned S5=1, unsigned S6=1, unsigned S7=1>
struct Shape {
    static constexpr unsigned rank_dynamic = 0;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

namespace helper_ {
    template <typename ShapeT, unsigned N>
    struct getN;

    template <unsigned SS, unsigned R, unsigned S0, unsigned S1, unsigned S2, unsigned S3, unsigned S4, unsigned S5, unsigned S6, unsigned S7, unsigned N>
    struct getN<Shape<SS, R, S0, S1, S2, S3, S4, S5, S6, S7>, N> {
        static constexpr std::tuple<unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned> x = std::make_tuple(S0, S1, S2, S3, S4, S5, S6, S7);
        static constexpr unsigned value = std::get<N>(x);
    };
} // namespace helpert_


template <unsigned ScalarSize, unsigned Rank, unsigned S0, unsigned S1, unsigned S2, unsigned S3, unsigned S4, unsigned S5, unsigned S6, unsigned S7>
std::ostream& operator<<(std::ostream& s, Shape<ScalarSize, Rank, S0, S1, S2, S3, S4, S5, S6, S7>) {
    return s << "Shape<"
             << ScalarSize << ", "
             << Rank << ", "
             << S0 << ", "
             << S1 << ", "
             << S2 << ", "
             << S3 << ", "
             << S4 << ", "
             << S5 << ", "
             << S6 << ", "
             << S7 << ")";
};

template <unsigned ScalarSize, unsigned Rank, unsigned S1, unsigned S2, unsigned S3, unsigned S4, unsigned S5, unsigned S6, unsigned S7>
struct Shape<ScalarSize, Rank, 0, S1, S2, S3, S4, S5, S6, S7>  {
    static constexpr unsigned rank_dynamic = 1;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

template <unsigned ScalarSize, unsigned Rank, unsigned S2, unsigned S3, unsigned S4, unsigned S5, unsigned S6, unsigned S7>
struct Shape<ScalarSize, Rank, 0, 0, S2, S3, S4, S5, S6, S7>  {
    static constexpr unsigned rank_dynamic = 2;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

template <unsigned ScalarSize, unsigned Rank, unsigned S3, unsigned S4, unsigned S5, unsigned S6, unsigned S7>
struct Shape<ScalarSize, Rank, 0, 0, 0, S3, S4, S5, S6, S7>  {
    static constexpr unsigned rank_dynamic = 3;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

template <unsigned ScalarSize, unsigned Rank, unsigned S4, unsigned S5, unsigned S6, unsigned S7>
struct Shape<ScalarSize, Rank, 0, 0, 0, 0, S4, S5, S6, S7>  {
    static constexpr unsigned rank_dynamic = 4;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

template <unsigned ScalarSize, unsigned Rank, unsigned S5, unsigned S6, unsigned S7>
struct Shape<ScalarSize, Rank, 0, 0, 0, 0, 0, S5, S6, S7>  {
    static constexpr unsigned rank_dynamic = 5;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

template <unsigned ScalarSize, unsigned Rank, unsigned S6, unsigned S7>
struct Shape<ScalarSize, Rank, 0, 0, 0, 0, 0, 0, S6, S7>  {
    static constexpr unsigned rank_dynamic = 6;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

template <unsigned ScalarSize, unsigned Rank, unsigned S7>
struct Shape<ScalarSize, Rank, 0, 0, 0, 0, 0, 0, 0, S7>  {
    static constexpr unsigned rank_dynamic = 7;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

template <unsigned ScalarSize, unsigned Rank>
struct Shape<ScalarSize, Rank, 0, 0, 0, 0, 0, 0, 0, 0>  {
    static constexpr unsigned rank_dynamic = 8;
    static constexpr unsigned scalar_size = ScalarSize;
    static constexpr unsigned rank = Rank;
};

template< class ShapeType , unsigned N ,
          unsigned R = ShapeType::rank_dynamic >
struct ShapeInsert ;

template< class ShapeType , unsigned N >
struct ShapeInsert< ShapeType , N , 0 >
{
    typedef Shape< ShapeType::scalar_size ,
                   ShapeType::rank + 1 ,
                   N ,
                   helper_::getN<ShapeType, 0>::value,
                   helper_::getN<ShapeType, 1>::value,
                   helper_::getN<ShapeType, 2>::value,
                   helper_::getN<ShapeType, 3>::value,
                   helper_::getN<ShapeType, 4>::value,
                   helper_::getN<ShapeType, 5>::value,
                   helper_::getN<ShapeType, 6>::value> type;
};

template< class ShapeType , unsigned N >
struct ShapeInsert< ShapeType , N , 1 >
{
    typedef Shape< ShapeType::scalar_size ,
                   ShapeType::rank + 1 ,
                   0 ,
                   N ,
                   helper_::getN<ShapeType, 1>::value,
                   helper_::getN<ShapeType, 2>::value,
                   helper_::getN<ShapeType, 3>::value,
                   helper_::getN<ShapeType, 4>::value,
                   helper_::getN<ShapeType, 5>::value,
                   helper_::getN<ShapeType, 6>::value> type;
};

template< class ShapeType , unsigned N >
struct ShapeInsert< ShapeType , N , 2 >
{
    typedef Shape< ShapeType::scalar_size ,
                   ShapeType::rank + 1 ,
                   0 ,
                   0 ,
                   N ,
                   helper_::getN<ShapeType, 2>::value,
                   helper_::getN<ShapeType, 3>::value,
                   helper_::getN<ShapeType, 4>::value,
                   helper_::getN<ShapeType, 5>::value,
                   helper_::getN<ShapeType, 6>::value> type;
};

template< class ShapeType , unsigned N >
struct ShapeInsert< ShapeType , N , 3 >
{
    typedef Shape< ShapeType::scalar_size ,
                   ShapeType::rank + 1 ,
                   0 ,
                   0 ,
                   0 ,
                   N ,
                   helper_::getN<ShapeType, 3>::value,
                   helper_::getN<ShapeType, 4>::value,
                   helper_::getN<ShapeType, 5>::value,
                   helper_::getN<ShapeType, 6>::value> type;
};

template< class ShapeType , unsigned N >
struct ShapeInsert< ShapeType , N , 4 >
{
    typedef Shape< ShapeType::scalar_size ,
                   ShapeType::rank + 1 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   N ,
                   helper_::getN<ShapeType, 4>::value,
                   helper_::getN<ShapeType, 5>::value,
                   helper_::getN<ShapeType, 6>::value> type;
};

template< class ShapeType , unsigned N >
struct ShapeInsert< ShapeType , N , 5 >
{
    typedef Shape< ShapeType::scalar_size ,
                   ShapeType::rank + 1 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   N ,
                   helper_::getN<ShapeType, 5>::value,
                   helper_::getN<ShapeType, 6>::value> type;
};

template< class ShapeType , unsigned N >
struct ShapeInsert< ShapeType , N , 6 >
{
    typedef Shape< ShapeType::scalar_size ,
                   ShapeType::rank + 1 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   N ,
                   helper_::getN<ShapeType, 6>::value> type;
};

template< class ShapeType , unsigned N >
struct ShapeInsert< ShapeType , N , 7 >
{
    typedef Shape< ShapeType::scalar_size ,
                   ShapeType::rank + 1 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   0 ,
                   N > type ;
};




template< class T >
struct AnalyzeShape // : public Shape< sizeof(T) , 0 >
{
    typedef void specialize ;

    typedef Shape< sizeof(T), 0 >  shape ;

    typedef       T  array_intrinsic_type ;
    typedef       T  value_type ;
    typedef       T  type ;

    typedef const T  const_array_intrinsic_type ;
    typedef const T  const_value_type ;
    typedef const T  const_type ;

    typedef       T  non_const_array_intrinsic_type ;
    typedef       T  non_const_value_type ;
    typedef       T  non_const_type ;
};

template<>
struct AnalyzeShape<void> // : public Shape< 0 , 0 >
{
    typedef void specialize ;

    typedef Shape< 0 , 0 >  shape ;

    typedef       void  array_intrinsic_type ;
    typedef       void  value_type ;
    typedef       void  type ;
    typedef const void  const_array_intrinsic_type ;
    typedef const void  const_value_type ;
    typedef const void  const_type ;
    typedef       void  non_const_array_intrinsic_type ;
    typedef       void  non_const_value_type ;
    typedef       void  non_const_type ;
};

template< class T >
struct AnalyzeShape< const T > // : public AnalyzeShape<T>::shape
{
private:
    typedef AnalyzeShape<T> nested ;
public:

    typedef typename nested::specialize specialize ;

    typedef typename nested::shape shape ;

    typedef typename nested::const_array_intrinsic_type  array_intrinsic_type ;
    typedef typename nested::const_value_type            value_type ;
    typedef typename nested::const_type                  type ;

    typedef typename nested::const_array_intrinsic_type  const_array_intrinsic_type ;
    typedef typename nested::const_value_type            const_value_type ;
    typedef typename nested::const_type                  const_type ;

    typedef typename nested::non_const_array_intrinsic_type  non_const_array_intrinsic_type ;
    typedef typename nested::non_const_value_type            non_const_value_type ;
    typedef typename nested::non_const_type                  non_const_type ;
};

template< class T >
struct AnalyzeShape< T * >
    // : public ShapeInsert< typename AnalyzeShape<T>::shape , 0 >::type
{
private:
    typedef AnalyzeShape<T> nested ;
public:

    typedef typename nested::specialize specialize ;

    typedef typename ShapeInsert< typename nested::shape , 0 >::type shape ;

    typedef typename nested::array_intrinsic_type * array_intrinsic_type ;
    typedef typename nested::value_type             value_type ;
    typedef typename nested::type                 * type ;

    typedef typename nested::const_array_intrinsic_type * const_array_intrinsic_type ;
    typedef typename nested::const_value_type             const_value_type ;
    typedef typename nested::const_type                 * const_type ;

    typedef typename nested::non_const_array_intrinsic_type * non_const_array_intrinsic_type ;
    typedef typename nested::non_const_value_type             non_const_value_type ;
    typedef typename nested::non_const_type                 * non_const_type ;
};

template< class T >
struct AnalyzeShape< T[] >
    // : public ShapeInsert< typename AnalyzeShape<T>::shape , 0 >::type
{
private:
    typedef AnalyzeShape<T> nested ;
public:

    typedef typename nested::specialize specialize ;

    typedef typename ShapeInsert< typename nested::shape , 0 >::type shape ;

    typedef typename nested::array_intrinsic_type  array_intrinsic_type [] ;
    typedef typename nested::value_type            value_type ;
    typedef typename nested::type                  type [] ;

    typedef typename nested::const_array_intrinsic_type  const_array_intrinsic_type [] ;
    typedef typename nested::const_value_type            const_value_type ;
    typedef typename nested::const_type                  const_type [] ;

    typedef typename nested::non_const_array_intrinsic_type  non_const_array_intrinsic_type [] ;
    typedef typename nested::non_const_value_type            non_const_value_type ;
    typedef typename nested::non_const_type                  non_const_type [] ;
};

template< class T >
struct AnalyzeShape< const T[] >
    // : public ShapeInsert< typename AnalyzeShape< const T >::shape , 0 >::type
{
private:
    typedef AnalyzeShape< const T > nested ;
public:

    typedef typename nested::specialize specialize ;

    typedef typename ShapeInsert< typename nested::shape , 0 >::type shape ;

    typedef typename nested::array_intrinsic_type  array_intrinsic_type [] ;
    typedef typename nested::value_type            value_type ;
    typedef typename nested::type                  type [] ;

    typedef typename nested::const_array_intrinsic_type  const_array_intrinsic_type [] ;
    typedef typename nested::const_value_type            const_value_type ;
    typedef typename nested::const_type                  const_type [] ;

    typedef typename nested::non_const_array_intrinsic_type  non_const_array_intrinsic_type [] ;
    typedef typename nested::non_const_value_type            non_const_value_type ;
    typedef typename nested::non_const_type                  non_const_type [] ;
};

template< class T , unsigned N >
struct AnalyzeShape< T[N] >
    // : public ShapeInsert< typename AnalyzeShape<T>::shape , N >::type
{
private:
    typedef AnalyzeShape<T> nested ;
public:

    typedef typename nested::specialize specialize ;

    typedef typename ShapeInsert< typename nested::shape , N >::type shape ;

    typedef typename nested::array_intrinsic_type  array_intrinsic_type [N] ;
    typedef typename nested::value_type            value_type ;
    typedef typename nested::type                  type [N] ;

    typedef typename nested::const_array_intrinsic_type  const_array_intrinsic_type [N] ;
    typedef typename nested::const_value_type            const_value_type ;
    typedef typename nested::const_type                  const_type [N] ;

    typedef typename nested::non_const_array_intrinsic_type  non_const_array_intrinsic_type [N] ;
    typedef typename nested::non_const_value_type            non_const_value_type ;
    typedef typename nested::non_const_type                  non_const_type [N] ;
};

template< class T , unsigned N >
struct AnalyzeShape< const T[N] >
// : public ShapeInsert< typename AnalyzeShape< const T >::shape , N >::type
{
private:
    typedef AnalyzeShape< const T > nested ;
public:

    typedef typename nested::specialize specialize ;

    typedef typename ShapeInsert< typename nested::shape , N >::type shape ;

    typedef typename nested::array_intrinsic_type  array_intrinsic_type [N] ;
    typedef typename nested::value_type            value_type ;
    typedef typename nested::type                  type [N] ;

    typedef typename nested::const_array_intrinsic_type  const_array_intrinsic_type [N] ;
    typedef typename nested::const_value_type            const_value_type ;
    typedef typename nested::const_type                  const_type [N] ;

    typedef typename nested::non_const_array_intrinsic_type  non_const_array_intrinsic_type [N] ;
    typedef typename nested::non_const_value_type            non_const_value_type ;
    typedef typename nested::non_const_type                  non_const_type [N] ;
};



int main() {

    using shape = Shape<10, 4, 0, 5, 7>;

    std::cout << shape() << std::endl;

    std::cout << ShapeInsert<shape, 52>::type() << std::endl;

    std::cout << AnalyzeShape<double**[][666]>::shape() << std::endl;

    return 0;
}
