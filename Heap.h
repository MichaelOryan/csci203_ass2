#include "Vector.h"
#include "Util.h"
#ifndef HEAP_H
#define HEAP_H

template<class T>
class Heap
{
    public:
        // Default constructor
        Heap();

        // Tell the heap if it should be a min or max heap
        Heap(bool maxHeap);

        // Constructor with passed in comparitor function
        Heap(bool (*)(const T &, const T &), bool maxHeap);

        // Destructor
        virtual ~Heap();

        // Push an element onto the heap, returns index for O(1) access to element for later
        int push(const T & t);

        // Pop the top element off the heap and return it
        T pop();

        // Mutable access to the top element in the heap
        T peek() {return _data[_heap[0]];}

        // Mutable access to the top element of the heap
        T& front() {return _data[_heap[0]];}

        // Let the heap know that the first element has been altered and it should reorder itself
        void frontChanged();

        // Change the top element in the heap
        void updateFront(T);

        // Returns whether our heap is empty or not
        bool isEmpty() {return _size == 0;}

        // Mutable access to an element by ID returned from push
        T& getByID(int);

        // Const access to an element by ID returned from push
        const T& peekByID(const int & index) const;

        // Tell the heap that an element at an ID return from push has changed and it should reorder itself
        void resortByID(int);

        // Iterator that moves through the elements in no particular order but can visit all elements in heap
        class Iterator;

        // Iterator to the "first" element
        Iterator begin() {return Iterator(this, 0);}

        // Iterator to the one past the end of the last iterator
        Iterator end() {return Iterator(this, this->_size);}

        class Iterator
        {
            public:
            Iterator(){}
            Iterator(const Iterator& iterator) {this->index = iterator.index; this->parent = iterator.parent;}
            Iterator(Heap<T> * parent):parent(parent){}
            Iterator(Heap<T> * parent, int index):parent(parent), index(index){}
            ~Iterator(){}
            T& operator*(){return this->parent->getByID(parent->_heap[index]);}
            Iterator operator++(int){this->index++; return *this;}
            void update(){this->parent->resortByID(parent->_heap[index]);}
            bool operator==(const Iterator & rhs) const {return this->parent == rhs.parent && this->index == rhs.index;}
            bool operator<(const Iterator & rhs) const {return this->parent == rhs.parent && this->index < rhs.index;}
            Iterator operator=(const Iterator & rhs) {this->index = rhs.index; this->parent = rhs.parent; return *this;}
            int getID() {return this->_heap[index];}

            private:

                Heap<T> * parent;
                int index;
        };

    private:
        int index;


    protected:

    private:

        // Comparison Function
        bool (*_comp)(const T &, const T &);

        // Compare two elements and return if they are in order
        bool compare(const int & a, const int & b);

        // Delete an element from the heap by it's position in the heap array
        void deleteElement(int heapIndex);

        // Our vector of indexes holding the _heap index where their element is returned from push
        Vector<int> _indexes;

        // Our heap order
        Vector<int> _heap;

        // The elements stored in the heap. They don't move so small overhead for speed gain when elements are large
        Vector<T> _data;

        // Sift up an index on the _heap
        void siftup(int index);

        // Sift down an index on the _heap
        void siftdown(int index);

        // Returns the size of the heap
        int _size;

        // Initalise the heap
        void init(bool (*)(const T &, const T &));

        // Swap two elements by their _heap index
        void heapSwap(int a, int b);

        // Whether we are using a min or max heap
        bool _maxHeap;

};

// Initalise Heap an empty
template<class T>
void Heap<T>::init(bool (*f)(const T &, const T &))
{
    this->_comp = f;
    _size = 0;

}

// Default constructor
template<class T>
Heap<T>::Heap()
{
    // min heap
    this->_maxHeap = false;

    // a < b
    init(&defaultComparitor);

}

// Type constructor
template<class T>
Heap<T>::Heap(bool maxHeap)
{
    this->_maxHeap = maxHeap;

    // a < b
    init(&defaultComparitor);
}

// Constructor with passed in comparitor function
template<class T>
Heap<T>::Heap(bool (*newcomp)(const T &, const T &), bool maxHeap)
{
    this->_maxHeap = maxHeap;

    // Use newcomp comparitor for ordering
    init(newcomp);
}

// Destructor
template<class T>
Heap<T>::~Heap()
{

}

// Delete an element from the heap at the given _heap index
template<class T>
void Heap<T>::deleteElement(int heapIndex)
{
    // Move reference to the end of the _heap
    heapSwap(heapIndex, this->_size - 1);

    // reduce size by one. _heap reference still in memory but outside of considered _heap
    this->_size--;

    // Sift down the previous last element from the top
    siftdown(heapIndex);
}

// const access to an element by an index returned by push
template<class T>
const T& Heap<T>::peekByID(const int & index) const
{
    // Maybe only need _data[index];
    return _data[_heap[_indexes[index]]];
}

// Mutable access to an element by index returned by push
template<class T>
T& Heap<T>::getByID(int dataID)
{
    // Maybe only need _data[dataID]
    return _data[_heap[_indexes[dataID]]];
}


// tell the heap that an element at an index returned by push is potentially out of order
template<class T>
void Heap<T>::resortByID(int dataID)
{
    siftup(_indexes[dataID]);
    siftdown(_indexes[dataID]);
}

// default comparitor of two elements
template<class T>
bool Heap<T>::compare(const int & a, const int & b)
{
    // Do we have a max heap?
    if(this->_maxHeap)
    {
        // Return if in order for max heap
        return this->_comp(_data[a], _data[b]);
    }
    // Else we have a min heap
    else
    {
        // Return if in order for min heap
        return !this->_comp(_data[a], _data[b]);
    }

}

// Swap a reference on _heap and update _index to still "point" to it
template<class T>
void Heap<T>::heapSwap(int a, int b)
{
    // Swap _index "pointers"
    _indexes[_heap[a]] = b;

    _indexes[_heap[b]] = a;

    // Swap "pointers"/references in _heap
    swap(_heap[a], _heap[b]);
}

// Push an element onto the heap
template<class T>
int Heap<T>::push(const T & t)
{
    // default index/ID to be returned
    int index = 0;

    // If our memory allocated for _heap is larger than our heap size
    if(_heap.size() > _size)
    {
        // put one past last index, if there was already something there from a pop/delete
        // then it'll point to an unused element index on _data
        // Our index = the position in _data
        index = _heap[_size];

        // Assign element to _data
        _data[index] = t;

        // Update _indexes to "point" to the correct _heap index
        _indexes[index] = _size;
    }
    // If our heap is the same size as our _heap/_index/_data sizes push to the end of the _heap/_data/_index vectors
    else
    {
        // Push "pointer" to the back of _heap vector
        _heap.push_back(_size);

        // Push element to the back of _data vector
        _data.push_back(t);

        // Push back "pointer" to _indexes for the _heap index just pushed back
        this->_indexes.push_back(_heap.size()-1);

        // Update index
        index = _indexes.size() - 1;
    }

    // Update size
    _size++;

    // siftup in last index
    siftup(_size - 1);

    // return a reference index/id to the element just added
    return index;
}

// Remove the top element from the heap and return it
template<class T>
T Heap<T>::pop()
{
    // Copy our top element
    T first = _data[_heap[0]];

    // delete it from the heap
    this->deleteElement(0);

    // Return the element
    return first;
}


// Recursive implementation of siftup comments from lectures
template<class T>
void Heap<T>::siftup(int index)
{
    //  if first index return
    if(index < 1)
    {
        return;
    }
   //  find parent i/2 // care for diff from array starting at 1 and 0
    int parent = (index - 1) / 2 ;
    //  if heap[p] < heap[i] return
    if(compare(_heap[index], _heap[parent]))
    {
        return;
        // keep highest on the left on the array so it fill up from left to right in the array
        int child = parent * 2 + 1;
        if( _size > child + 1 && compare(_heap[child], _heap[child + 1]))
        {
            //swap(_heap[child], _heap[child + 1]);
            heapSwap(child, child + 1);
            siftdown(child + 1 );
        }
    }

    //  else
    else
    {
        //  swap heap[p] with heap[i]
        //swap(_heap[parent], _heap[index]);
        heapSwap(parent, index);
        //  siftup(p)
        siftup(parent);
    }


}

// Siftdown iterative implementation adapted from recursive from lectures
template<class T>
void Heap<T>::siftdown(int index)
{
    // find children of index
    int child = (index * 2) + 1;
    int child2 = child + 1;

    // While our first child is not out of bounds (second child will be if it is)
    while(child < _size)
    {
        // if our second child is in bounds compare to first
        if(child2 < _size && compare(_heap[child], _heap[child2]))
        {
            // if order is second then first then we consider the second child instead of the first for ordering
            child = child2;
        }
        // Compare chosen child to parent
        if(compare(_heap[index], _heap[child]))
        {
            // If out of order then swap parent and child
            heapSwap(index, child);

            // Index is now the child which is where the old parent now is
            index = child;

            // Calc it's new children
            child = (index * 2) + 1;
            child2 = child + 1;
        }
        // Else We have correct order and we can just set child to be _size so the loop ends
        else
        {

            child = _size;
        }
    }

}

// Change the first element in this heap to something else
template<class T>
void Heap<T>::updateFront(T t)
{
    // Assign
    this->_data[_heap[0]] = t;

    // Check order
    siftdown(0);
}

// Tell the heap that the top element has changed
template<class T>
void Heap<T>::frontChanged()
{
    siftdown(0);
}

#endif // HEAP_H
