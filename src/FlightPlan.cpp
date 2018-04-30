// author: Ronken Christoph & Van Hautte Olivier
// date: 02/05/2018
// version: 2.0

#include "FlightPlan.h"


FlightPlan::FlightPlan() {
    self = this;
}

//getters & setters
const string &FlightPlan::getDestination() const {
    return FlightPlan::destination;
}
void FlightPlan::setDestination(const string &destination) {
    FlightPlan::destination = destination;
}

int FlightPlan::getDeparture() const {
    return FlightPlan::departure;
}
void FlightPlan::setDeparture(const int &departure) {
    FlightPlan::departure = departure;
}

int FlightPlan::getInterval() const {
    return FlightPlan::interval;
}
void FlightPlan::setInterval(const int &interval) {
    FlightPlan::interval = interval;
}

int FlightPlan::getArrival() const {
    return FlightPlan::arrival;
}
void FlightPlan::setArrival(const int &arrival) {
    FlightPlan::arrival = arrival;
}


//checks
bool FlightPlan::propperlyInitialised() {
    return (this == FlightPlan::self);
}
bool FlightPlan::isValid() {
    return !(FlightPlan::destination.empty() || FlightPlan::interval == 0 || !FlightPlan::propperlyInitialised());
}
