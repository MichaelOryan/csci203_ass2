#include "Event.h"

Event::Event()
{

}

Event::~Event()
{

}

// Constructor for an Event, needs when this event happens and the type of event. Customer arrives or server finishes serving a customer
Event::Event(double timeEventHappens, EventType eventType)
{
    // When this event happens
    this->_timeEventHappens = timeEventHappens;

    // What event happens
    this->_eventType = eventType;
}
