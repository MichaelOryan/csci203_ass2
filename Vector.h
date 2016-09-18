#include "Array.h"
#ifndef VECTOR_H
#define VECTOR_H

template<class T>
class Vector
{
    public:
        // Default constructor
        Vector();

        // Create a vector of n initial memory size
        Vector(int);

        // Copy constructor
        Vector(const Vector<T> &);

        // Destructor
        virtual ~Vector();

        // Return size of this vector
        int size() const;

        //Set the size of this array
        void setSize(int);

        // Return mutable first element in this vector
        T& first();

        // Return mutable last element in this vector
        T& last();

        // Append an element to the end of this vector
        void push_back(const T&);

        // Mutable Index access to an element in this vector, no bounds checking
        T& operator[] (const int & index);

        // Const index access to an element in this vector, no bounds checking
        const T& operator[] (const int & index) const;

        // Returns if this Vector is empty
        bool isEmpty() {return _size == 0;}

        // Assignment operator, make this array the same as another one
        Vector<T>& operator=(const Vector<T> &);

        // Remove and return the last element in this vector
        T& pop_back();

        // Swap the values and elements held in this array with those of another
        void swapWith(Vector &);

        // Get values at an index
        const T& getIndex(const int & index) const;
    protected:
    private:
        // Set the dynamically memory allocated for this vector
        void setMemSize(int);

        // Initalise this vector to a size
        void init(int size);

        // The array holding the vectors elements
        Array<T> _array;

        // Size of this vector
        int _size;

        // Increase the size of this vector when it gets full
        void grow();
};

// Initalise this vectors memory to a size
template<class T>
void Vector<T>::init(int size)
{
    this->_size = 0;
    this->_array = Array<T>(size);
}

// Create a vector with a starting memory size. Not vector size
template<class T>
Vector<T>::Vector(int size)
{
    init(size);
}

// Copy constructor
template<class T>
Vector<T>::Vector(const Vector<T> & source)
{
    // This vector is the same size as the source
    this->_size = source._size;

    // Copy the underlying array from the source into this one
    this->_array = source._array;
}

// Default vector constructor
template<class T>
Vector<T>::Vector()
{
    init(1);
}

template<class T>
Vector<T>::~Vector()
{

}

// Set the memory size of this vector
template<class T>
void Vector<T>::setMemSize(int size)
{
    // Create new array of new size
    Array<T> newArray(size);

    // Copy from the old array into the new one
    newArray.copyFrom(this->_array, min(size, this->_array.size()));

    // Swap the array in the vector with the new one
    newArray.swapArrays(this->_array);
}

// Grow our Vector when it gets full
template<class T>
void Vector<T>::grow()
{
    // Calc new size
    int newSize = this->_array.size() * 2;

    // If we have 0 size (or less than 0) we need atleast 1 memory size
    if( newSize < 1)
    {
        newSize = 1;
    }

    // Change allocated memory for this vector
    this->setMemSize(newSize);
}

// Set the memory size of this vector, no trimming
template<class T>
void Vector<T>::setSize(int size)
{
    // If the new size is greater than the current size
    if(!this->_array.getSize() <= size)
    {
        setMemSize(size);
        this->_size = size;
    }

}

// Return size of vector, elements not memory
template<class T>
int Vector<T>::size() const
{
    return this->_size;
}

// Mutable access to first element
template<class T>
T& Vector<T>::first()
{
    return this->_array[0];
}

// Mutable access to last element
template<class T>
T& Vector<T>::last()
{
    return this->_array[this->size()-1];
}

// remove and return last element, no bounds checking
template<class T>
T& Vector<T>::pop_back()
{
    if(this->_size > 0)
    {
        this->_size--;
    }
    return this->_array[this->_size];
}

// Append an element to the next index after the last element in this vector
template<class T>
void Vector<T>::push_back(const T& t)
{
    // If we have full allocated memory allocate more
    if(this->size() >= this->_array.size())
    {
        grow();
    }

    // Append to last + 1 index
    this->_array[this->size()] = t;

    // update new size
    this->_size++;
}

// Mutable access to an elemment at an index
template<class T>
T& Vector<T>::operator[] (const int & index) // for non-const objects: can be used for assignment
{
    return this->_array[index];
}

// Const access to an elemment at an index
template<class T>
const T& Vector<T>::operator[] (const int & index) const // for const objects: can only be used for access
{
    return this->_array[index];
}

// Assignment operator, make this vector the same as another one
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T> & rhs)
{
    this->_array = rhs._array;
    this->_size = rhs._size;
    return *this;

}

// Swap this vectors values and elements with another one
template<class T>
void Vector<T>::swapWith(Vector & other)
{
    swap(this->_size, other._size);
    this->_array.swapArrays(other._array);
}

// Const access to an elemment at an index
template<class T>
const T& Vector<T>::getIndex(const int & index) const
{
    return this->_array[index];
}

#endif // VECTOR_H


