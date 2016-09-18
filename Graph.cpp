
#include "Graph.h"
#include "Heap.h"
#include "Union.h"
#include <limits.h>

#include <iostream>
using namespace std;


Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}

Graph::Graph(int nodes)
{
    this->_table = Array<Array<int> > (nodes);
    for(int i = 0; i < nodes; i++)
    {
        this->_table[i] = Array<int>(nodes);
        for(int j = 0; j < nodes; j++)
        {
            this->_table[i][j] = -1;
        }
    }
    this->_size = nodes;
}

void Graph::addEdge(int a, int b, int weight, bool directional)
{
    this->_table[a][b] = weight;
    if(!directional)
    {
        this->_table[b][a] = weight;
    }
}

int Graph::getWeight(int a, int b)
{
    return this->_table[a][b];
}


template<class T>
void printArray(const T & t)
{
    for(int i = 0; i < t.size(); i++)
    {
        cout << t[i] << " ";
    }
    cout << endl;
}

Vector<Pair<int, int> > Graph::minTreePrim()
{

    // Initialise arrays
    Array<int> nearest(this->_size);
    Array<int> mindist(this->_size);

    // Initialise set S
    Vector<Pair<int, int> > S;

    // For every node except the first set to it's distance from first node
    for(int i = 1; i < this->_size; i++)
    {
        // Nearest is first node, 0
        nearest[i] = 0;

        // -1 distance is infinite from _table, -1 is used for in mintree so change to INT_MAX
        mindist[i] = this->_table[i][0] == -1 ? INT_MAX : this->_table[i][0];
    }

    // Repeat n - 1 times so we add enough edges for the minmum tree
    for(int i = 0; i < this->_size - 1; i++)
    {
        // Set min to "infinite"
        int min = INT_MAX;

        // Initialise node to add. Will be set to another none in the next loop
        int k = 0;

        // Find the next node unconnected node that requires the smallest distance/weight to be connected to O
        for(int j = 1; j < this->_size; j++)
        {
            // exclude distances of -1 as that means they are in O
            // Check if the current nodes cost to add to O is lower than min
            if(mindist[j] >= 0 && mindist[j] < min)
            {
                // Update new minimum
                min = mindist[j];
                // Update potential new node k
                k = j;
            }
        }

        // add {nearest[k], k] to S
        S.push_back(Pair<int, int>(nearest[k], k));

        // Update mindist to reflect k being in O
        mindist[k] = -1;

        // Update new minimum distances fron the connected set O
        for(int j = 1; j < this->_size; j++)
        {
            // Check each nodes connection to k and update if distance from k lower than current mindistance
            if(this->_table[j][k] < mindist[j] && this->_table[j][k] != -1)
            {
                mindist[j] = this->_table[j][k];
                nearest[j] = k;
            }
        }
    }

    // return our set of edges S
    return S;
}
