//
// Created by oliviervh on 12.04.18.
//

#include "FlightPlan.h"


FlightPlan::FlightPlan() {
    self = this;
}

const string &FlightPlan::getDestination() const {
    return FlightPlan::destination;
}
void FlightPlan::setDestination(const string &destination) {
    FlightPlan::destination = destination;
    ENSURE(FlightPlan::getDestination() == destination, "destination set" );
}

int FlightPlan::getDeparture() const {
    return FlightPlan::departure;
}
void FlightPlan::setDeparture(int departure) {
    FlightPlan::departure = departure;
    ENSURE(FlightPlan::getDeparture() == departure, "departure time set" );
}

int FlightPlan::getInterval() const {
    return FlightPlan::interval;
}

void FlightPlan::setInterval(int interval) {
    FlightPlan::interval = interval;
    ENSURE(FlightPlan::getInterval() == interval, "interval set" );
}

int FlightPlan::getArrival() const {
    return FlightPlan::arrival;
}
void FlightPlan::setArrival(int arrival) {
    FlightPlan::arrival = arrival;
    ENSURE(FlightPlan::getArrival() == arrival, "arrival time set" );
}

bool FlightPlan::propperlyInitialised() {
    return (this == self);
}

bool FlightPlan::isValid() {
    return !(destination.empty() || interval == 0 || !propperlyInitialised());
}
