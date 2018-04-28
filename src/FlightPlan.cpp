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
}

int FlightPlan::getDeparture() const {
    return FlightPlan::departure;
}
void FlightPlan::setDeparture(int departure) {
    FlightPlan::departure = departure;
}

int FlightPlan::getInterval() const {
    return FlightPlan::interval;
}
void FlightPlan::setInterval(int interval) {
    FlightPlan::interval = interval;
}

int FlightPlan::getArrival() const {
    return FlightPlan::arrival;
}
void FlightPlan::setArrival(int arrival) {
    FlightPlan::arrival = arrival;
}

bool FlightPlan::propperlyInitialized() {
    return (this == self);
}
