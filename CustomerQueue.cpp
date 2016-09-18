#include "CustomerQueue.h"

CustomerQueue::CustomerQueue()
{

}

CustomerQueue::~CustomerQueue()
{

}

// Constructor for a Customer Queue. Needs order from door because customers will go to the closest queue first if they are the same length
CustomerQueue::CustomerQueue(const int & orderFromDoor)
{
    // Closeness to door, closer to door prefered when same queue length
    this->_orderFromDoor = orderFromDoor;

    // Largest queue size recorded by this queue
    this->_maxQueueLength = 0;

    // When this queue last changed. Ie; when a customer was added or taken from the queue
    this->_lastChange = 0;

    // Queue length multiplied by time. Divide by total time to get average queue length
    this->_weightedQueueLength = 0;
}

// Copy constructor for a customer  queue
CustomerQueue::CustomerQueue(const CustomerQueue & rhs)
{
    this->_maxQueueLength = rhs._maxQueueLength;
    this->_lastChange = rhs._lastChange;
    this->_orderFromDoor = rhs._orderFromDoor;
    this->_queue = rhs._queue;
    this->_weightedQueueLength = rhs._weightedQueueLength;
}

// Does the queue contain any customers?
bool CustomerQueue::isEmpty() const
{
    return this->_queue.isEmpty();
}

// Add a customer to the end of the queue
void CustomerQueue::enqueue(Customer customer)
{
    // The current time is when this customer arrives
    double time = customer.getArrivalTime();

    // Calculate and add to the weighted queue length. Queue length * time passed since last change in queue. Divide by total time for average
    this->_weightedQueueLength += (time - this->_lastChange) * this->_queue.size();

    // Queue changed so update when this queue last changed, ie; now
    this->_lastChange = time;

    // Add the customer to the queue data structor
    this->_queue.enqueue(customer);

    // if our queue is longer than the max, set it's current length to the new max queue length
    if(this->_queue.size() > this->_maxQueueLength)
    {
        this->_maxQueueLength = this->_queue.size();
    }
}

// Remove a customer from the queue
Customer CustomerQueue::dequeue(const double & time)
{
    // Calculate a new weighted queue length. Queue length * time passed since last change
    this->_weightedQueueLength += (time - this->_lastChange) * this->_queue.size();

    // Queue has changed so update when the queue last changed. ie; now
    this->_lastChange = time;

    // Return the customer and remove from the queue
    return this->_queue.dequeue();
}


// Return the largest/longest sized queue this CustomerQueue had
int CustomerQueue::maxQueueLength()
{
    return this->_maxQueueLength;
}

// Ordering of Customer Queues
bool CustomerQueue::operator<(const CustomerQueue & rhs) const
{
    // Same size then by closest to door
    if(this->_queue.size() == rhs._queue.size())
    {
        return this->_orderFromDoor < rhs._orderFromDoor;
    }

    // different size // update for min heap when heap is changed
    return this->_queue.size() < rhs._queue.size();
}

// Calulate and return the average queue length of this queue
double CustomerQueue::calcAvgLength(const double & timePassed)
{
    return this->_weightedQueueLength / timePassed;
}

// Get the position of this queue from the door, lower closer
int CustomerQueue::getOrder()
{
    return this->_orderFromDoor;
}
