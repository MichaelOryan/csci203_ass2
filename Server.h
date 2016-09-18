#include "Customer.h"
#include "CustomerQueue.h"
#include "Heap.h"
#ifndef SERVER_H
#define SERVER_H


class Server
{
    public:
        // For unitialised servers, assign by copy constructor
        Server();

        // Constructor for a Server
        Server(Heap<CustomerQueue> & q, int queueID);

        // Copy constructor
        Server(const Server &);

        // Deconstructor
        virtual ~Server();

        // Ordering of servers by when they finish
        bool operator<(const Server & rhs) const;

        // Serve a customer without putting them in the customer queue. Ie; there is a queue size of 0 and the server was idle
        void serveCustomer(Customer);

        // Finish serving a customer and grab a new one from the queue if applicable. Return wait time in queue for customer
        double finishCustomer(const double & time);

        // Get total idle time of this server
        double getTotalIdleTime();

        // Is this server idle
        bool isIdle();

        // When will this server finish serving their customer
        double getFinishTime();

        // Get the closeness to the door of this servers queue
        int getOrder() const;

    protected:

    private:

        // Serve a customer from this assigned servers customer queue
        double serveQueueCustomer(const double & time);

        // Initalisation of the server, needs a heap of CustomerQueues and an Index/ID of it's assigned queue to server customers from
        void init(Heap<CustomerQueue> & q, int);

        // The heap of CustomerQueues which contains this servers queue to server customers from
        Heap<CustomerQueue> * _queue;

        // Index/ID of the Queue in the CustomerQueue Heap to take/serve customer from
        int _queueID;

        // Total idle time of this server
        double _totalIdleTime;

        // When this server will be finished serving their current/last if idle customer
        double _finishTime;

        // Is this server serving a customer? Ie; are they idle
        bool _idle;

};

#endif // SERVER_H
