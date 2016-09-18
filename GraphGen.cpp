#include <time.h>
#include <stdlib.h>
#include "GraphGen.h"

GraphGen::GraphGen()
{
    //ctor
}

GraphGen::~GraphGen()
{
    //dtor
}

Vector<Edge> GraphGen::genEdges(int nodes)
{
    srand(time(0));

    Vector<Edge> edges;
    for(int i = 0; i < nodes; i++)
    {
        for(int j = i + 1; j < nodes; j++)
        {
            if(j != i)
            {
                Edge nextEdge;
                nextEdge.start = i;
                nextEdge.end = j;
                nextEdge.weight = rand() % 10;
                edges.push_back(nextEdge);
            }
        }
    }
    return edges;
}
