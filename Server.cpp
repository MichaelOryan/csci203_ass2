#include "Server.h"

Server::Server()
{

}

Server::~Server()
{

}

// Server constructor, needs access to the CustomerQueue heap as well as the index/id of the queue to take from
Server::Server(Heap<CustomerQueue> & q, int queueID)
{
    // Initialise server
    init(q, queueID);
}

// Copy Constructor
Server::Server(const Server & source)
{
    // Make a copy of the source into this server
    this->_queue = source._queue;
    this->_idle = source._idle;
    this->_finishTime = source._finishTime;
    this->_queueID = source._queueID;
    this->_totalIdleTime = source._totalIdleTime;
}

// Ordering of servers
bool Server::operator<(const Server & rhs) const
{
    return this->_finishTime < rhs._finishTime;

}

// Initialise a server
void Server::init(Heap<CustomerQueue> & q, int queueID)
{
    // CustomerQueue heap where queues are located
    this->_queue = &q;

    // Index/ID of the queue in the heap
    this->_queueID = queueID;

    // Current total idle time of server
    this->_totalIdleTime = 0;

    // When the current/last if idle customer will be finished being served
    this->_finishTime = 0;

    // Is this server serving a customer, ie; are they idle
    this->_idle = true;
}

// Calculate idle time given when this server started being idle and the current time
double calcIdleTime(const bool & isIdle, const double & setIdleAt, const double & currentTime)
{
    // Are we idle?
    if(isIdle)
    {
        // Return difference between current time and when this server started being idle
        return currentTime - setIdleAt;
    }
    // Wasn't idle? Then 0 idle time
    return 0;
}

// Serve a customer without putting them in a queue, ie; queue size of 0 and server idle
void Server::serveCustomer(Customer customer)
{
    // Add this servers idle time to their total idle time
    this->_totalIdleTime += calcIdleTime(this->_idle, this->_finishTime, customer.getArrivalTime());

    // Calculate the new time this server will finish serving the new customer
    this->_finishTime = customer.getServiceTime() + customer.getArrivalTime();

    // This server is no longer idle
    this->_idle = false;
}

// Serve a customer from this assigned servers customer queue
double Server::serveQueueCustomer(const double & time)
{
    // Add this servers idle time to their total idle time, should add 0
    this->_totalIdleTime += calcIdleTime(this->_idle, this->_finishTime, time);

    // Make a copy of the next customer from this servers queue. Ie; from the CustomerQueue heap by the assigned index/ID
    Customer customer = _queue->getByID(this->_queueID).dequeue(time);

    // This servers queue length has changed, move it to the right position in the CustomerQueue Heap
    _queue->resortByID(this->_queueID);

    // Calc and update the new time this server will finish serving it's current customer
    this->_finishTime = customer.getServiceTime() + time;

    // Set server no longer idle
    this->_idle = false;

    // Return the time the current/new customer spent waiting in the queue

    return customer.timeInQueue(time);
}

// What do to if we finish serving a customer
double Server::finishCustomer(const double & time)
{
    // If this servers assigned queue is empty
    if(_queue->peekByID(this->_queueID).isEmpty())
    {
        // Server is now idle
        this->_idle = true;

        // Update this servers finish time with the current non existant customer finish time. ie service time is 0 so current time
        this->_finishTime = time;

        // Didn't serve a customer so the wait time was 0 for the current non existant customer
        return 0;
    }
    else
    {
        // Serve a customer from the queue this servers assigned queue. Return the time the customer spent in the queue
        return serveQueueCustomer(time);
    }
}

// Return the total time this server has spent idle/not serving a customer
double Server::getTotalIdleTime()
{
    return this->_totalIdleTime;
}

// Return whether this server is currently idle and not serving a customer
bool Server::isIdle()
{
    return this->_idle;
}

// Return when this server will finish serving their current customer or finished serving their last custonmer

double Server::getFinishTime()
{
    return this->_finishTime;
}

// Get the closeness to the door of this servers queue
int Server::getOrder() const
{
    return this->_queue->getByID(this->_queueID).getOrder();
}
