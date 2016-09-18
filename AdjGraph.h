#include "Vector.h"
#include "Array.h"
#include "Pair.h"
#ifndef ADJGRAPH_H
#define ADJGRAPH_H


class AdjGraph
{
    public:
        AdjGraph();
        AdjGraph(int size);
        virtual ~AdjGraph();
        void addEdge(int a, int b, int weight, bool directional = false);
        Array<int> minTreePrim();
        void print();
    protected:

    private:
        Array<Vector<Pair<int, int> > > _table;
        int _size;
};

#endif // ADJGRAPH_H
