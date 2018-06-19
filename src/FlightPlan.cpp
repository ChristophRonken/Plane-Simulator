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
    REQUIRE(properlyInitialised(), "properly initialised");
    FlightPlan::destination = destination;
    ENSURE(FlightPlan::getDestination() == destination, "destination set" );
}

int FlightPlan::getDeparture() const {
    return FlightPlan::departure;
}
void FlightPlan::setDeparture(int departure) {
    REQUIRE(properlyInitialised(), "properly initialised");
    FlightPlan::departure = departure;
    ENSURE(FlightPlan::getDeparture() == departure, "departure time set" );
}

int FlightPlan::getInterval() const {
    return FlightPlan::interval;
}

void FlightPlan::setInterval(int interval) {
    REQUIRE(properlyInitialised(), "properly initialised");
    FlightPlan::interval = interval;
    ENSURE(FlightPlan::getInterval() == interval, "interval set" );
}

int FlightPlan::getArrival() const {
    return FlightPlan::arrival;
}
void FlightPlan::setArrival(int arrival) {
    REQUIRE(properlyInitialised(), "properly initialised");
    FlightPlan::arrival = arrival;
    ENSURE(FlightPlan::getArrival() == arrival, "arrival time set" );
}

bool FlightPlan::properlyInitialised() {
    return (this == FlightPlan::self);
}

bool FlightPlan::isValid() {
    return !(FlightPlan::destination.empty() || FlightPlan::interval == 0 || !FlightPlan::properlyInitialised());
}
