#include "Vector.h"
#include "Array.h"
#include "Pair.h"
#include "Union.h"
#ifndef BRUTEGRAPH_H
#define BRUTEGRAPH_H


class BruteGraph
{
    public:
        BruteGraph();
        virtual ~BruteGraph();
        BruteGraph(int size);
        void addEdge(int a, int b, int weight, bool directional = false);
        Array<int> minTreeBrute();
        Pair<Array<int>, int> bruteRecursive(Array<int> parents, Union u, int v, int parent);
        int findDist(int, int);
        //void print();
    protected:
    private:
        Array<Vector<Pair<int, int> > > _table;
        int _size;
};

#endif // BRUTEGRAPH_H
