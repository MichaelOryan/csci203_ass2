#include "Array.h"

#ifndef UNION_H
#define UNION_H

class Union
{
    public:
        Union();
        Union(int size);
        Union(const Union &);

        ~Union();
        void link(int, int);
        bool areLinked(int, int);

    private:
        Array<int> _nodes;
        Array<int> _weight;

        int root(int i);
};


#endif // UNION_H
