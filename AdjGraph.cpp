#include "Heap.h"
#include "Union.h"
#include <limits.h>

#include "AdjGraph.h"
#include "Util.h"

#include <iostream>
using namespace std;

AdjGraph::AdjGraph()
{

}

AdjGraph::AdjGraph(int size): _table(Array<Vector<Pair<int, int> > >(size)), _size(size)
{
    //ctor
}

AdjGraph::~AdjGraph()
{
    //dtor
}

void AdjGraph::addEdge(int a, int b, int weight, bool directional)
{
    this->_table[a].push_back(Pair<int, int>(b, weight));
    if(!directional)
    {
        this->_table[b].push_back(Pair<int, int>(a, weight));
    }
}


bool distCompare(const Pair<int, int> & a, const Pair<int, int> & b )
{
    return a.b < b.b;
}

Array<int> AdjGraph::minTreePrim()
{
    // Shortest distance to node from connected graph
    Array<int> dist(this->_size);
    // INT_MAX means infinite
    setAll(dist, INT_MAX);

    // Parent node that has the shortest distance to the node
    Array<int> parent(this->_size);
    // -1 means no yet parent
    setAll(parent, -1);

    // Position in the heap of the node
    Array<int> hPos(this->_size);
    // -1 means not in heap
    setAll(hPos, -1);


    // Setup heap of nodes and distance of them to the connected node
    Heap<Pair<int, int> > h(distCompare, false);

    // Ass first Node (0) to heap with 0 distance to self
    hPos[0] = h.push(Pair<int, int>(0, 0));

    // Should iterate n-1 times
    while(!h.isEmpty())
    {
        // Pop node with shortest distance to connected graph, or starting node
        int v = h.pop().a;

        // Indicate node is in the connected tree
        dist[v] = -1;

        // For each node connected to this node
        for(int i = 0; i < this->_table[v].size(); i++)
        {
            // Get node
            int u = this->_table[v][i].a;

            // Get nodes weight
            int uWeight = this->_table[v][i].b;

            // Update distance from connected graph if distance from node v is shorter
            if(uWeight < dist[u])
            {
                // Update distance of u
                dist[u] = uWeight;

                // Update parent of u to be v
                parent[u] = v;

                // If u is is not in the heap, add it to the heap
                if(hPos[u] == -1)
                {
                    hPos[u] = h.push(Pair<int, int>(u, uWeight));
                }
                // If it is in the heap update the heap with it's u's new weight
                else
                {
                    h.resortByID(hPos[u]);
                }
            }
        }
    }

    // Return parent array
    return parent;
}

void AdjGraph::print()
{
    for(int i = 0; i < this->_table.size(); i++)
    {
        for(int j = 0; j < this->_table[i].size(); j++)
        {
            cout << i + 1 << ", "<<this->_table[i][j].a + 1 << " - " << this->_table[i][j].b << " : ";
        }
        cout << endl;
    }
}
