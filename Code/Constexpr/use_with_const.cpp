template<int N> class A {};

constexpr int sqr1(int arg)
{ return arg * arg; }

int sqr2(int arg)
{ return arg * arg; }

int main()
{
    const int X = 2;
    A<sqr1(X)> mylist1;
    //A<sqr2(X)> mylist2;
}
