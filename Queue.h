#include "Array.h"
#ifndef QUEUE_H
#define QUEUE_H

template<class T>
class Queue
{
    public:
        // Default constructor
        Queue();

        // Copy constructor
        Queue(const Queue<T> &);

        // Destructor
        virtual ~Queue();

        // Assignment operator
        Queue<T>& operator=(const Queue<T> &);

        // Enqueue an element in this queue, add to end of queue
        void enqueue(T t);

        // Remove the first element in this queue and retgurn it
        T dequeue();

        // const access to the first element in this queue
        const T& peek() const;

        // Returns size of the queue
        int size() const {return this->_count;}

        // Whether this queue is empty
        bool isEmpty() const {return _count == 0;}

    protected:

    private:
        // Increase the memory size of this queue
        void grow();

        // Underlying array holding the queue elements
        Array<T> _array;

        // Index of the first element
        int _first;

        // Number of elements in the queue
        int _count;

};

// Default constructor
template<class T>
Queue<T>::Queue()
{
    // First at first index
    _first = 0;

    // Nothing in queue
    _count = 0;

    // Allocate memory
    _array = Array<T>(1);
}

// Destructor
template<class T>
Queue<T>::~Queue()
{

}

// Copy constructor
template<class T>
Queue<T>::Queue(const Queue<T> & rhs)
{
    this->_first = rhs._first;
    this->_count = rhs._count;
    this->_array = rhs._array;
}

// Grow the memory allocateed for this queue
template<class T>
void Queue<T>::grow()
{
    // Calc new size
    int newSize = this->_count * 2;

    // Deal with 0 or negative numbers as we have at least one element being added
    if(newSize == 0)
    {
        newSize = 1;
    }

    // Create new array of the size needed
    Array<T> newArray(newSize);

    // Copy this queues array into the new array. New array will have first at index 0
    for(int i = 0; i < this->_count; i++)
    {
        // Start from the first
        int index = _first + i;

        // If we have fallen off the array then go back to the start
        if(index >= _array.getSize())
        {
            index -= _array.getSize();
        }

        // Copy to the first, then second, etc,... indexes in the new array
        newArray[i] = _array[index];
    }
    // Set new first to first index
    this->_first = 0;

    // Swap the old array with the new array
    _array.swapArrays(newArray);
}

// Add an element to the end of the queue
template<class T>
void Queue<T>::enqueue(T t)
{
    // If we don't have enough memory increase memory size
    if(_count == _array.getSize())
    {
        grow();
    }

    // Calc index we need to put the element into
    int index = _first + _count;

    // Wrap around if we fall off the end of the underlying array
    if(index >= _array.getSize())
    {
        index -= _array.getSize();
    }

    // Assign element to index one after the old last
    _array[index] = t;

    // Update count of elements in queue
    _count++;
}

// Remove the first element and return it
template<class T>
T Queue<T>::dequeue()
{
    // Grab first element in queue
    T toReturn = _array[_first];

    // Update the first element
    this->_first++;

    // If we fall off the array wrap around to the start
    if(_first >= _array.getSize())
    {
        _first = 0;
    }

    // Update count
    _count--;

    // Return element
    return toReturn;
}


// Const access to the first element in the queue
template<class T>
const T& Queue<T>::peek() const
{
    return _array[this->_first];
}


// Assign this queue the values and elements of another one
template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T> & rhs)
{
    this->_count = rhs._count;
    this->_first = rhs._first;
    this->_array = rhs._array;
    return *this;
}

#endif // QUEUE_H
