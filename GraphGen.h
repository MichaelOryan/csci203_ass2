#include "Vector.h"
#ifndef GRAPHGEN_H
#define GRAPHGEN_H

struct Edge;

class GraphGen
{
    public:

        GraphGen();
        virtual ~GraphGen();
        Vector<Edge> genEdges(int nodes);

    protected:
    private:
};

struct Edge
{
    Edge(){}
    ~Edge(){}
    Edge(const Edge & rhs)
    {
        start = rhs.start;
        end = rhs.end;
        weight = rhs.weight;

    }
    int start;
    int end;
    int weight;
};
#endif // GRAPHGEN_H
