#include <iostream>
#ifndef EVENT_H
#define EVENT_H

class Event
{
    public:
        // Definitions of the types of events
        enum EventType {ServerFinish, CustomerArrives};

        // Default constructor
        Event();

        // Constructor for an event. Need time the event happens and the type
        Event(double timeEventHappens, EventType eventType);

        // destructor
        virtual ~Event();

        // Time the event happens
        double _timeEventHappens;

        // Event type
        EventType _eventType;

        // Comparitor Function for ordering
        bool operator<(const Event & rhs) const {return this->_timeEventHappens < rhs._timeEventHappens;}

    protected:
    private:
};


#endif // EVENT_H
