#ifndef PAIR_H
#define PAIR_H

template<class T, class U>
struct Pair
{
    public:

    Pair(){}
    Pair(const T & a, const U & b): a(a), b(b){}
    Pair(const Pair & pair): a(pair.a), b(pair.b){}
    ~Pair(){}
    T a;
    U b;
    protected:

    private:

};

#endif // PAIR_H
