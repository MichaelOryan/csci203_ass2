#include "Customer.h"
#include "Queue.h"

#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H


class CustomerQueue
{
    public:
        // Default constructor
        CustomerQueue();

        // Constructor with order from door
        CustomerQueue(const int & orderFromDoor);

        // Copy constructor
        CustomerQueue(const CustomerQueue &);

        // Destructor
        virtual ~CustomerQueue();

        // Is the customer queue empty?
        bool isEmpty() const;

        // Add a customer to the queue
        void enqueue(Customer);

        // Remove and return the customer at the front of the queue
        Customer dequeue(const double & time);

        // Maximum length that this queue has been
        int maxQueueLength();

        // Comparitor for ordering
        bool operator<(const CustomerQueue & rhs) const;

        // Calculate the average length of this queue given the total time
        double calcAvgLength(const double &);

        // Get the closeness to the door order of this queue
        int getOrder();

        // Return the current length of this queue
        int length() {return this->_queue.size();}

    protected:

    private:
        // Queuelength * change in time
        double _weightedQueueLength;

        // longest length this queue has been
        int _maxQueueLength;

        // Queue of customers in this customerqueue
        Queue<Customer> _queue;

        // order of closeness to the door
        int _orderFromDoor;

        // last time this customer queue changed in length
        double _lastChange;
};

#endif // CUSTOMERQUEUE_H
