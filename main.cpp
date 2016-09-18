// Standard Library
#include <iostream>
#include <string>
#include <fstream>

// Data structures
#include "Heap.h"
#include "Array.h"
#include "Vector.h"
#include "Queue.h"

// Project File Headers
#include "Customer.h"
#include "Simulation.h"
#include "Server.h"
#include "CustomerQueue.h"
#include "Simulation.h"

using namespace std;

// Read an int from ifstream
int readInt(ifstream &);

// Read a customer arrival, service time from an ifstream and return a Customer object
Customer readCustomer(ifstream &);

// Main function
int main(int argc, char *argv[])
{
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    // input file
    ifstream file;

    // Open file
    file.open(filename.c_str());

    // Read number of servers from file
    int servers = readInt(file);

    // If there's something wrong with the file
    if(!file.good())
    {
        cout << "Error with file" << endl;
        return 0;
    }

    // Create a queue of customers
    Queue<Customer> customers;

    // Read the first customer
    Customer next = readCustomer(file);

    // While we have successfully read from our file
    while(file.good())
    {
        // Enqueue the customer read from the file
        customers.enqueue(next);

        // read another customer from the file
        next = readCustomer(file);

    }

    // close file
    file.close();

    cout << "\n";
    cout << "Michael O'Ryans Queue Simulation\n";

    // create simulation
    Simulation sim(customers, servers, true);

    // Run simulation
    sim.startSim();
    cout << "Simulating One Queue per server and one shared queue\n\n";
   // write results to output
    sim.printStats(cout);

    // Seperator results
    cout << "\n\n";

    // Create simulation
    Simulation sim2(customers, servers, false);

    // start sim
    sim2.startSim();

    // Output results
    sim2.printStats(cout);

    return 0;
}

// Read an int from an ifstream
int readInt(std::ifstream & file)
{
    // error check here
    int n;
    file >> n;
    return n;
}

// Read the next customer from a file
Customer readCustomer(std::ifstream & file)
{
    // Read arrival time
    double arrival;
    file >> arrival;

    // Read service time
    double serviceTime;
    file >> serviceTime;

    // Create and return customer
    return Customer(arrival, serviceTime);

}
