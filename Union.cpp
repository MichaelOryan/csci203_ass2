// Weighted Quick Union Path Compression
// Adapcted from Java code @ https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf

#include "Union.h"

Union::Union()
{

}

Union::Union(int size)
{
    this->_nodes = Array<int>(size);
    this->_weight = Array<int>(size);
    for(int i = 0; i < size; i++)
    {
        _nodes[i] = i;
        _weight[i] = 1;
    }

}

Union::Union(const Union & source)
{
    this->_nodes = source._nodes;

}

Union::~Union()
{

}

int Union::root(int i)
{
    while(i != _nodes[i])
    {
        _nodes[i] = _nodes[_nodes[i]];
        i = _nodes[i];
    }
    return i;
}

void Union::link(int a, int b)
{
    if(a == b)
        return;
    int i = root(a);
    int j = root(b);

    if(_weight[i] < _weight[j])
    {
        _nodes[i] = j;
        _weight[j] += _weight[i];
    }
    else
    {
        _nodes[j] = i;
        _weight[i] += _weight[j];

    }
}
bool Union::areLinked(int a, int b)
{
    return root(a) == root(b);
}
