#ifndef CUSTOMER_H
#define CUSTOMER_H


class Customer
{
    public:
        // Default Constructor
        Customer();

        // Destructor
        virtual ~Customer();

        // How to create a customer
        Customer(const double & arrivalTime, const double & serviceTime);

        // Calculate the time this customer has spent in the queue
        double timeInQueue(const double & timeServed);

        // Get time this customer will take to serve
        double getServiceTime() const;

        // Get arrival time of this customer
        double getArrivalTime() const;

    protected:

    private:
        // Arrival time of the customer
        double _arrivalTime;

        // Time this customer will take to serve
        double _serviceTime;
};

#endif // CUSTOMER_H
