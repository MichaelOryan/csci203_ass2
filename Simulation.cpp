#include <iomanip>
#include "Simulation.h"

Simulation::Simulation()
{

}

Simulation::~Simulation()
{

}

Simulation::Simulation(const Queue<Customer> customers, int servers, const bool & sharedQueue)
{
    // Set the simulation to starting values
    init(customers, servers, sharedQueue);

    // Create our servers and link them to queue(s)
    buildQueuesAndServers();
}

// To determine which server has it's queue closest to the door
bool closerToDoor(const Server & a, const Server & b)
{
    return a.getOrder() < b.getOrder();
}

void Simulation::init(const Queue<Customer> & customers, int servers, const bool & sharedQueue)
{

    // Initalise our values to starting simulation values
    this->_maxQueueTime = 0;
    this->_numServers = servers;
    this->_time = 0;
    this->_totalCustomers = 0;
    this->_totalQueueTime = 0;
    this->_totalServiceTime = 0;

    // Do we have a shared queue or one per server
    this->_sharedQueue = sharedQueue;

    // Copy our external customer queue into the simulation
    this->_customers = customers;

    // Make idleserver ordered by closeness of their servers queue to the door
    this->_idleServers = Heap<Server>(&closerToDoor, false);
}

// Build our servers and queues such that there is one shared queue
void buildSharedQueuesAndServers(Heap<CustomerQueue> & queues, Heap<Server> & servers, const int numServers)
{
    // Create one queue
    int queueID = queues.push(CustomerQueue(0));
    // Create n servers
    for(int i = 0; i < numServers; i++)
    {
        // Create a server and put on the heap with a queueID to server so it knows which queue to take from
        servers.push(Server(queues, queueID));
    }

}
// Build servers and link them to one queue each
void buildMultiQueuesAndServers(Heap<CustomerQueue> & queues, Heap<Server> & servers, const int numServers)
{
    // Create n servers
    for(int i = 0; i < numServers; i++)
    {
        // Create our queue and record it's ID
        int queueID = queues.push(CustomerQueue(numServers - i)); // reverse order because same length queues are ordered by lowest distance from door, ie lowest number
        // Create a server and put on the heap with a queueID to server so it knows which queue to take from
        servers.push(Server(queues, queueID));
    }

}

// Build our servers and queues
void Simulation::buildQueuesAndServers()
{
    // Do we have a shared queue or one queue per server
    // Servers should all start idle
    if(this->_sharedQueue)
    {
        buildSharedQueuesAndServers(this->_queues, this->_idleServers, this->_numServers);
    }
    else
    {
        buildMultiQueuesAndServers(this->_queues, this->_idleServers, this->_numServers);
    }
}

// What to do when a customer arrives
void Simulation::customerArrives(const Event & e)
{
    // Increment total customers
    this->_totalCustomers++;

    // Move time forward to when the event happens
    this->_time = e._timeEventHappens;

    // Add service time to total service time
    this->_totalServiceTime += this->_customers.peek().getServiceTime();

    // If we have an idle servers
    if(!this->_idleServers.isEmpty())
    {
        // Grab an idle server and have them serve the customer
        this->_idleServers.front().serveCustomer(this->_customers.dequeue());
        Server server = this->_idleServers.front();
        // Add an event for when this server finishes serving the customer
        this->_events.push(Event(server.getFinishTime(), Event::ServerFinish));
        // Add our server to our list of busy servers
        this->_busyServers.push(this->_idleServers.pop());

    }
    // If we have no idle servers
    else
    {
        // Find the shortest then closest queue to the door and place the customer in that queue
        this->_queues.front().enqueue(this->_customers.dequeue());
        // Reorder the heap because the queue is now potentially out of position
        this->_queues.frontChanged();
    }

    // If we have more customers then create an event for when the next one arrives
    if(!this->_customers.isEmpty())
    {
        this->_events.push(Event(this->_customers.peek().getArrivalTime(), Event::CustomerArrives));
    }


}

// What to do when a server finishes serving a customer
void Simulation::serverFinishes(const Event & e)
{
    // Move time forward to when the event happens
    this->_time = e._timeEventHappens;

    // Calculate the time the next customer spent in queue and grab the next customer
    double timeInQueue = this->_busyServers.front().finishCustomer(this->_time);

    // Update total queue waiting time
    this->_totalQueueTime += timeInQueue;

    // Update out maximum waiting time
    this->_maxQueueTime = max(this->_maxQueueTime, timeInQueue);

    // If our server is now idle remove it from the busy server list and add it to the idle server list
    if(this->_busyServers.front().isIdle())
    {
        this->_idleServers.push(this->_busyServers.pop());
    }
    // Otherwise create a new event for when this server will finish when it's next customer
    else
    {
        this->_events.push(Event(this->_busyServers.front().getFinishTime(), Event::ServerFinish));

        // Update order of the busyservers so the first to finish is at the top of the heap
        this->_busyServers.frontChanged();
    }
}

// Decide what event we have and do it
void Simulation::doEvent(const Event & event)
{
    // Which event do we have?
    switch(event._eventType)
    {
        // A customer arriving do this
        case Event::CustomerArrives: customerArrives(event); break;
        // A server finishing do this
        case Event::ServerFinish:    serverFinishes(event);break;
    }
}

void Simulation::startSim()
{
    // If we have customers
    if(!this->_customers.isEmpty())
    {
        // Add the first ones arrival time to our events
        this->_events.push(Event(this->_customers.peek().getArrivalTime(), Event::CustomerArrives));

        // While we have events, ie customers arriving or servers finishing
        while(!this->_events.isEmpty())
        {
            // Do the event that will happen next
            doEvent(this->_events.pop());
        }
    }
}


// Print the stats for all queues to ostream
void printQueueStats(Heap<CustomerQueue> & queues, const double & time, std::ostream & out)
{


    // Set decimal place limit
    out << std::setprecision(2) << std::fixed;

    // While we have queues
    while(!queues.isEmpty())
    {
        // Take the first one
        CustomerQueue current = queues.pop();

        // Print out it's stats
        out << "Queue " << std::setw(3) << current.getOrder() << ", ";
        out << "Avg: " << current.calcAvgLength(time) << ", ";
        out << "Max Length: " << current.maxQueueLength();
        out << std::endl;
    }

}

// Print out the stats for all servers
void printServerStats(Heap<Server> & servers, const double & time, std::ostream & out)
{
    // Count to keep track of the server
    int count = 1;
    // While we have more servers to print

    // Set decimal place limit
    out << std::setprecision(2) << std::fixed;

    while(!servers.isEmpty())
    {
        // Grab a server
        Server server = servers.pop();

        // Print out it's stats
        out << "Server " << std::setw(3) << count << " ";
        out << "Idle Time: " << std::setw(8) << server.getTotalIdleTime();


        // Conserve lines so it's not a million pages long for lots of servers
        if((count)% 2 == 0)
        {
            out << std::endl;
        }
        else
        {
            out << "  :  ";
        }
        count++;
    }
}

// Print out the stats of the simulation
void Simulation::printStats(std::ostream & out)
{
    out << std::setprecision(2) << std::fixed;
    // Print some information about the simulation as a whole
    out << "Type of Queueing: " << (this->_sharedQueue ? "Single Queue" : "One Queue Per Server") << std::endl;
    out << "Number of people served: " << this->_totalCustomers << std::endl;
    out << "Time last customer was finsihed being served: " << this->_time << std::endl;
    out << "Average Service Time: " << this->_totalServiceTime / this->_totalCustomers << std::endl;
    out << "Average Time in Queue: " << this->_totalQueueTime / this->_totalCustomers << std::endl;;
    out << "Max Time in Queue: " << this->_maxQueueTime << std::endl;

    out << std::endl;

    // Print out stats for each queue
    out << "Average and Max Length of Queues: " << std::endl;
    printQueueStats(this->_queues, this->_time, out);

    out << std::endl;

    // Print out stats for each server
    out << "Server Idle Time: " << std::endl;
    printServerStats(this->_idleServers, this->_time, out);

}
