#ifndef UTIL_H
#define UTIL_H


#ifndef mycopy
#define mycopy
// Copy from one pointer to another of fixed size
template<class T>
void copy(T * source, T * target, const int & size)
{
    for(int i = 0; i < size; i++)
    {
        target[i] = source[i];
    }
}
#endif // mycopy


#ifndef myswap
#define myswap
// Swap two elements, temp variable implementation
template<class T>
void swap(T & a, T & b)
{
    T temp = a;
    a = b;
    b = temp;
}
#endif // myswap

#ifndef mymin
#define mymin
// Return the lowest of two values
template<class T>
T min(const T & a, const T & b)
{
    if(a < b)
    {
        return a;
    }
    return b;
}

#endif // mymin

#ifndef mymax
#define mymax
// Return the largest of two values
template<class T>
T max(const T & a, const T & b)
{
    if(a < b)
    {
        return b;
    }
    return a;
}

#endif // mymax

#ifndef mycomparitor
#define mycomparitor

// Default comparitor. Finds if a comes before b
template<class T>
bool defaultComparitor(const T & a, const T & b)
{
    return a < b;
}

#endif

#ifndef myptrtargetcomparitor
#define myptrtargetcomparitor

// Compare the values pointed at by pointers a and b and see if *a comes before *b
template<class T>
bool ptrTargetComparitor(const T & a, const T & b)
{
    return *a < *b;
}

#endif


#endif // UTIL_H
