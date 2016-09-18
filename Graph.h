#include "Array.h"
#include "Vector.h"
#include "Pair.h"
#ifndef GRAPH_H
#define GRAPH_H


class Graph
{
    public:
        Graph();
        Graph(int nodes);
        virtual ~Graph();
        void addEdge(int a, int b, int weight, bool directional = false);
        int getWeight(int a, int b);
        //Vector<int> shortestPath(int start, int end);
        Vector<Pair<int, int> > minTreePrim();
    protected:

    private:
        Array<Array<int> > _table;
        int _size;
};

#endif // GRAPH_H
