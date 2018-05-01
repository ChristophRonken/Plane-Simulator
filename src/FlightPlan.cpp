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
    ENSURE(FlightPlan::destination == destination, "destination set" );
}

int FlightPlan::getDeparture() const {
    return FlightPlan::departure;
}
void FlightPlan::setDeparture(int departure) {
    FlightPlan::departure = departure;
    ENSURE(FlightPlan::departure == departure, "departure time set" );
}

int FlightPlan::getInterval() const {
    return FlightPlan::interval;
}

void FlightPlan::setInterval(int interval) {
    FlightPlan::interval = interval;
    ENSURE(FlightPlan::interval == interval, "interval set" );
}

int FlightPlan::getArrival() const {
    return FlightPlan::arrival;
}
void FlightPlan::setArrival(int arrival) {
    FlightPlan::arrival = arrival;
    ENSURE(FlightPlan::arrival == arrival, "arrival time set" );
}

bool FlightPlan::propperlyInitialised() {
    return (this == FlightPlan::self);
}

bool FlightPlan::isValid() {
    return !(FlightPlan::destination.empty() || FlightPlan::interval == 0 || !FlightPlan::propperlyInitialised());
}
