#include "Util.h"

#ifndef HEAPSORT_H
#define HEAPSORT_H


namespace HeapSort
{


    template<class T>
    bool compare(const T & a, const T & b, bool maxHeap);

    template<class T>
    void siftdown(T & data, int index, int size, bool maxHeap)
    {
                // find children of index
        int child = (index * 2) + 1;
        int child2 = child + 1;

        // While our first child is not out of bounds (second child will be if it is)
        while(child < size)
        {
            // if our second child is in bounds compare to first
            if(child2 < size && compare(data[child], data[child2], maxHeap))
            {
                // if order is second then first then we consider the second child instead of the first for ordering
                child = child2;
            }
            // Compare chosen child to parent
            if(compare(data[index], data[child], maxHeap))
            {
                // If out of order then swap parent and child
                swap(data[index], data[child]);

                // Index is now the child which is where the old parent now is
                index = child;

                // Calc it's new children
                child = (index * 2) + 1;
                child2 = child + 1;
            }
            // Else We have correct order and we can just set child to be _size so the loop ends
            else
            {

                child = size;
            }
        }

    }


    template<class T>
    void makeHeap(T & data, bool maxHeap)
    {
        for(int i = data.size()/2; i >= 0; i--)
        {
            siftdown(data, i, data.size(), maxHeap);
        }
    }


    template<class T>
    void heapSort(T & data, bool maxHeap = true)
    {
        makeHeap(data, maxHeap);

        for(int i = data.size()-1; i > 0; i--)
        {
            swap(data[0], data[i]);
            siftdown(data, 0, i, maxHeap);
        }

    }


    // default comparitor of two elements
    template<class T>
    bool compare(const T & a, const T & b, bool maxHeap)
    {
        // Do we have a max heap?
        if(maxHeap)
        {
            // Return if in order for max heap
            return !(a < b);
        }
        // Else we have a min heap
        else
        {
            // Return if in order for min heap
            return                                       (a < b);
        }

    }

}
#endif // HEAPSORT_H
