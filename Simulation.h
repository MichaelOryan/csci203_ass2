#include <ostream>

#include "Heap.h"
#include "Array.h"
#include "Server.h"
#include "CustomerQueue.h"
#include "Event.h"

#ifndef SIMULATION_H
#define SIMULATION_H


class Simulation
{
    public:
        /** Default constructor */
        Simulation();
        // Constructor for Simulation requiring a customer queue, number of servers and whether it will have one shared queue or one queue per server
        Simulation(const Queue<Customer> customers, int servers, const bool & sharedQueue);
        /** Default destructor */
        virtual ~Simulation();
        void startSim();
        void printStats(std::ostream &);

    protected:

    private:
        // Initialise the simulation object
        void init(const Queue<Customer> & customers, int servers, const bool & sharedQueue);
        // Decide which event we are doing and do it
        void doEvent(const Event & event);
        // Build our queue or queues and link them to our servers
        void buildQueuesAndServers();
        // What to do when a customer arrives
        void customerArrives(const Event & e);
        // What to do when a server finishes
        void serverFinishes(const Event & e);

        // Data
        // Do we have a shared queue or one queue per server
        bool _sharedQueue;
        // Current simulation time
        double _time;
        // Number of servers we are simulating
        int _numServers;
        // Total customer count so far
        int _totalCustomers;
        // Total time spent serving customers
        double _totalServiceTime;
        // Total waiting time in the queue by customers
        double _totalQueueTime;
        // Highest queue wait
        double _maxQueueTime;

        // Each server in the following are linked to a queue
        // Our currently busy servers whom are serving a customer
        Heap<Server> _busyServers;
        // Our idle servers whom are awaiting a customer, ordered by closeness to thier queue to the door
        Heap<Server> _idleServers;
        // Our queues or queue which have been linked to each server
        Heap<CustomerQueue> _queues;
        // Our heap of events in order of when they should happen
        Heap<Event> _events;
        // Customers that will be arriving to be served
        Queue<Customer> _customers;

};

#endif // SIMULATION_H
