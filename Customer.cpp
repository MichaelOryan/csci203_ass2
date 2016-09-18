#include "Customer.h"

Customer::Customer()
{

}

Customer::~Customer()
{

}

// Constructor for a customer. Needs arrival time and how long it will take to serve them
Customer::Customer(const double & arrivalTime, const double & serviceTime)
{
    this->_arrivalTime = arrivalTime;
    this->_serviceTime = serviceTime;
}

// Calculate the time this customer spent in queue base on their arrival time and the time they were served
double Customer::timeInQueue(const double & timeServed)
{
    return timeServed - this->_arrivalTime;
}

// Get the time it will take to serve this customer
double Customer::getServiceTime() const
{
    return this->_serviceTime;
}

// Get the arrival time of this customer
double Customer::getArrivalTime() const
{
    return this->_arrivalTime;
}
