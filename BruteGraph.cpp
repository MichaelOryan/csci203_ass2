#include <climits>
#include "Vector.h"
#include "BruteGraph.h"
#include "Union.h"
#include "Util.h"
#include "Pair.h"

BruteGraph::BruteGraph()
{
    //ctor
}

BruteGraph::~BruteGraph()
{
    //dtor
}


BruteGraph::BruteGraph(int size): _table(Array<Vector<Pair<int, int> > >(size)), _size(size)
{

}
void BruteGraph::addEdge(int a, int b, int weight, bool directional)
{
    this->_table[a].push_back(Pair<int, int>(b, weight));
    if(!directional)
    {
        this->_table[b].push_back(Pair<int, int>(a, weight));
    }
}

int BruteGraph::findDist(int a, int b)
{
    for(int i = 0; i < this->_table[a].size(); i++)
    {
        if(this->_table[a][i].a == b)
        {
            return this->_table[a][i].b;
        }
    }
    return INT_MAX;
}

Pair<Array<int>, int> BruteGraph::bruteRecursive(Array<int> parents, Union u, int v, int parent)
{
    if(parent != -1)
    {
        u.link(v, parent);
        parents[v] = parent;
    }
    Pair<Array<int>, int> minTree;
    minTree.a = parents;
    minTree.b = INT_MAX;
    for(int i = 0; i < this->_table[v].size(); i++)
    {
        if(!u.areLinked(v, this->_table[v][i].a))
        {
            Pair<Array<int>, int> potential = bruteRecursive(parents, u, this->_table[v][i].a, v);
            if(potential.b < minTree.b)
            {
                minTree = potential;
            }
        }
    }
    if(this->_table[v].size()==0 && parent != -1)
    {
        minTree.b = findDist(v, parent);
    }
    return minTree;
}

Array<int> BruteGraph::minTreeBrute()
{
    Array<int> parents(this->_size);
    setAll(parents, 0);

    return bruteRecursive(parents, Union(this->_size), 0, -1).a;


}
//void print();
