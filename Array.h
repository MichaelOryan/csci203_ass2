#include "Util.h"
#ifndef ARRAY_H
#define ARRAY_H

template<class T>
class Array
{
    public:
        // Uninitalised array
        Array();

        // Construct an array of n size
        Array(int);

        // Clean up memory
        virtual ~Array();

        // Copy constructor
        Array(const Array<T> &);

        // Access index, no bounds checking, mutable value returned
        T& operator[](const int &);

        // Access index, no bounds checking, returns const of value
        const T& operator[](const int &) const;

        // Copy the values of another array into this one
        Array<T>& operator=(const Array<T>&);

        // Return the size/;length of this array
        int size() const {return _size;}

        // Copy from another array into this one. Will try and copy the enture source array.
        void copyFrom(const Array &);

        // Copy the first n elements of an array into this one
        void copyFrom(const Array &, const int & size);

        // Swap the values and elements held in two arrays.
        void swapArrays(Array & target);

    protected:

    private:
        // Free the dynamic memory held by this array
        void clearMemory();

        // Allocate dynamic memory for this array
        void init(int size);

        // PTR to dynamic memory allocated
        T* _array;

        // Size of array and dynamic memory allocated
        int _size;
};

// Allocate memory and record the size
template<class T>
void Array<T>::init(int size)
{
    this->_size = max(size, 1);
    this->_array = new T[this->_size];
}

// For an uninitialised array. Defaults to size of 1
template<class T>
Array<T>::Array()
{
    this->_size = 1;
    init(this->_size);
}

// Create an array with a fixed size
template<class T>
Array<T>::Array(int size)
{
    init(size);
}

// Deallocate dynamic memory for this array
template<class T>
void Array<T>::clearMemory()
{
    // If we have some dynmaic memory allocated
    if (this->_size > 0)
    {
        // Free it
        delete [] _array;
    }
    // update size to reflect 0 sized array
    _size = 0;
}

// Deconstructor
template<class T>
Array<T>::~Array()
{
    // clean up of memory
    clearMemory();
}

// Copy Constructor
template<class T>
Array<T>::Array(const Array<T> & rhs)
{
    // Allocate memory to the same size as the source array
    init(rhs._size);

    // copy the source array into this array
    copy(rhs._array, this->_array, this->_size);
}


// Copy from a source array into this array of the source size
template<class T>
void Array<T>::copyFrom(const Array & source)
{
    copy(source._array, this->_array, source._size);
}

// Copy from a source array of a passed in size eg; the size of this array
template<class T>
void Array<T>::copyFrom(const Array & source, const int & size)
{
    copy(source._array, this->_array, size);
}


// Swap the values and elements held by two arrays;
template<class T>
void Array<T>::swapArrays(Array & target)
{
    // Pointer values to dynamic memory swapped
    swap(this->_array, target._array);

    // New sizes updated, ie; swapped
    swap(this->_size, target._size);
}

// Index access to array, eg; int x = array[4]; Const implementation
template<class T>
const T& Array<T>::operator[](const int & index) const
{
    return _array[index];
}

// Mutable access to an index in the array. eg; array[4] = 234543;
template<class T>
T& Array<T>::operator[] (const int & index)
{
    return _array[index];
}

// Assignment, assign this array the values and elements of a source array
template<class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
    // Clear this arrays memory
    this->clearMemory();

    // Allocate memory to size of source array
    this->init(rhs._size);

    // Copy the contents of the source array into this array
    this->copyFrom(rhs);

    // Returb this array
    return *this;
}
#endif // ARRAY_H
