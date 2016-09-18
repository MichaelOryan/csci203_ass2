#include <iostream>

#include <stdlib.h>
#include <time.h>

#include "Union.h"
#include "HeapSort.h"
#include "Vector.h"
#include "Heap.h"
#include "Pair.h"
#include "Graph.h"
#include "AdjGraph.h"
#include "BruteGraph.h"
#include "GraphGen.h"

using namespace std;


void heapSortTest()
{
    Vector<int> numbers;
    numbers.push_back(4);
    numbers.push_back(7);
    numbers.push_back(1);
    numbers.push_back(21);
    numbers.push_back(87);
    numbers.push_back(12);
    numbers.push_back(9);
    numbers.push_back(16);
    numbers.push_back(3);
    numbers.push_back(13);

    for(int i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << " ";
    }

    cout << endl;

    HeapSort::heapSort(numbers, false);

    for(int i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << " ";
    }

    cout << endl;

}

void testLink(int a, int b, Union & u)
{
    if(u.areLinked(a, b))
    {
        cout << a << " and " << b << " are linked!";
    }
    else
    {
        cout << a << " and " << b << " are not linked!";
    }
    cout << endl;
}

void unionTest()
{
    Union u(10);
    cout << "Link 0, 1" << endl;
    u.link(0, 1);
    cout << "Link 3, 4" << endl;
    u.link(3, 4);
    cout << "Link 4, 5" << endl;
    u.link(4, 5);
    cout << "Link 7, 6" << endl;
    u.link(7, 6);

    testLink(3, 5, u);
    testLink(9, 7, u);
    testLink(1, 2, u);
    testLink(0, 3, u);


}

int unionTestLink(int size)
{
    Union u(size);
    int count = 0;
    int x = rand() % size;
    int y = rand() % size;

    while(x == y)
    {
        x = rand() % size;
        y = rand() % size ;
    }
    cout << x << " " << y << endl;
    while(!u.areLinked(x, y))
    {
        count++;
        int a = rand() % size;
        int b = rand() % size;
        cin >> a >> b;

        /*while(a == b || u.areLinked(a, b))
        {
            b = rand() % size ;
        }*/
        u.link(a, b);
    }

    return count;
}

void unionTestLarge()
{
    int size = 10000;
    int total = 0;
    int count = 0;
    int _max = -1;
    int _min = -1;
    for(int i = 0; i < 100000; i++)
    {
        int thisCount = unionTestLink(size);
        if(_max == -1)
        {
            _max = thisCount;
        }
        else
        {
            _max = _max > thisCount ? _max : thisCount;
        }

        if(_min == -1)
        {
            _min = thisCount;
            cout << thisCount << endl;
        }
        else
        {
            _min = _min < thisCount ? _min : thisCount;
        }

        count++;
        total += thisCount;
    }
    cout << "Max: " << _max << endl;
    cout << "Min: " << _min << endl;
    cout << "Avg: " << (double)total / (double)count / size * 100  << "%" << endl;

}

int roll(int size)
{
    int count = 0;
    while(rand()%size >0)
    {
        count++;
    }
    return count;

}

void rollTest()
{
    int total = 0;
    int count = 0;
    int _max = -1;
    int _min = -1;
    for(int i = 0; i < 1000; i++)
    {
        int thisCount = roll(100);
        if(_max == -1)
        {
            _max = thisCount;
        }
        else
        {
            _max = _max > thisCount ? _max : thisCount;
        }

        if(_min == -1)
        {
            _min = thisCount;
        }
        else
        {
            _min = _min < thisCount ? _min : thisCount;
        }

        count++;
        total += thisCount;
    }
    cout << "Max: " << _max << endl;
    cout << "Min: " << _min << endl;
    cout << "Avg: " << (double)total / (double)count << endl;

}

/*
void graphTest()
{
    Graph g(5);
    g.addEdge(0, 1, 5);

    cout << g.getWeight(0, 1) << " : " << g.getWeight(1, 0) << endl;
    cout << g.getWeight(0, 2) << " : " << g.getWeight(1, 2) << endl;
}
*/
void heapIteratorTest()
{
    Heap<int> h;
    h.push(4);
    h.push(10);
    h.push(1);
    h.push(20);
    h.push(7);
    h.push(12);
    Heap<int>::Iterator iter = h.begin();
    while(iter < h.end())
    {
        cout << *iter << " ";
        iter++;
    }
    cout << endl;

    h.pop();
    h.pop();
    h.pop();
    iter = h.begin();

    while(iter < h.end())
    {
        cout << *iter << " ";
        iter++;
    }
    cout << endl;

}

void graphMinTree()
{
    Graph g(7);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 3, 4);

    g.addEdge(1, 3, 6);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 4, 5);
    g.addEdge(2, 5, 6);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 5, 8);
    g.addEdge(3, 6, 4);
    g.addEdge(4, 6, 7);
    g.addEdge(5, 6, 3);

    Vector<Pair<int, int> > minTree = g.minTreePrim();
    for(int i = 0; i < minTree.size(); i++)
    {
        cout << minTree[i].a << " " << minTree[i].b << endl;
    }


}

void graphMinTree1()
{
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 2);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 2, 0);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 0);
    g.addEdge(2, 3, 0);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 2);

    Vector<Pair<int, int> > minTree = g.minTreePrim();
    for(int i = 0; i < minTree.size(); i++)
    {
        cout << minTree[i].a + 1 << " " << minTree[i].b  + 1<< endl;
    }


}

void graphAdjMinTree()
{
    AdjGraph g(7);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 3, 4);

    g.addEdge(1, 3, 6);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 4, 5);
    g.addEdge(2, 5, 6);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 5, 8);
    g.addEdge(3, 6, 4);
    g.addEdge(4, 6, 7);
    g.addEdge(5, 6, 3);

    g.print();
    cout << endl;
    Array<int> minTree = g.minTreePrim();
    for(int i = 1; i < minTree.size(); i++)
    {
        cout << i+1 << ":" << minTree[i]+1 << endl;
    }


}

void graphBruteMinTree()
{
    BruteGraph g(7);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 3, 4);

    g.addEdge(1, 3, 6);
    g.addEdge(1, 4, 4);
    g.addEdge(2, 4, 5);
    g.addEdge(2, 5, 6);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 5, 8);
    g.addEdge(3, 6, 4);
    g.addEdge(4, 6, 7);
    g.addEdge(5, 6, 3);

    //g.print();
    Array<int> minTree = g.minTreeBrute();
    for(int i = 1; i < minTree.size(); i++)
    {
        cout << i << "-" << minTree[i] << endl;
    }


}

void graphGenTest()
{
    const int size = 5;
    //GraphGen gen;
    //Vector<Edge> edges = gen.genEdges(size);
    AdjGraph g(size);
    /*for(int i = 0; i < edges.size(); i++)
    {
        Edge nextEdge = edges[i];
        g.addEdge(nextEdge.start, nextEdge.end, nextEdge.weight);
    }*/
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 2);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 2, 0);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 0);
    g.addEdge(2, 3, 0);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 2);
    g.print();
    cout << endl;
    Array<int> minTree = g.minTreePrim();
    for(int i = 1; i < minTree.size(); i++)
    {
        cout << i+1 << ":" << minTree[i]+1 << endl;
    }
}


int main()
{
    graphMinTree1();
    //graphGenTest();
    //graphAdjMinTree();
    //graphBruteMinTree();
    return 0;
    heapIteratorTest();
   // graphTest();
    //srand (time(NULL));
    //heapSortTest();
    //unionTest();
    //unionTestLarge();
    //unionTestLink(10000);
    return 0;
    Union u(100000);
    u.link(0, 1);
    u.link(0, 10);
    u.link(12, 10);
    u.link(2, 1);

    u.link(17, 21);
    u.link(23, 24);
    u.link(25, 13);
    u.link(13, 21);
    u.link(32, 17);
    u.link(32, 12);


    int a = 2;
    int b = 12;
    if(u.areLinked(a, b))
    {
        cout << "Linked!" << endl;
    }
    else
    {
        cout << "Not linked!" << endl;
    }
    if(u.areLinked(b, a))
    {
        cout << "Linked!" << endl;
    }
    else
    {
        cout << "Not linked!" << endl;
    }
    //rollTest();

    return 0;
}
