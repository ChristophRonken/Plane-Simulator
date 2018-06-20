//
// Created by oliviervh on 12.04.18.
//

#ifndef PSE_V1_AIRPLANEROUTE_H
#define PSE_V1_AIRPLANEROUTE_H

#include <iostream>
#include <vector>
#include "DesignByContract.h"

using namespace std;

class FlightPlan
{
    FlightPlan *self;
    string destination;
    int departure;
    int interval;
    int arrival;

  public:
    /**
     * Constructor
     */
    FlightPlan();

    /**
     * Returns the destination of the flight plan
     * @return string
     */
    const string &getDestination() const;

    /**
     * Sets the destination of the flight plan
     * Preconditions: propperlyInitialised()
     * Postconditions: FlightPlan::getDestination() == destination
     * @param destination
     */
    void setDestination(const string &destination);

    /**
     * Returns the departure time of the flight plan
     * Preconditions: propperlyInitialised()
     * @return int
     */
    int getDeparture() const;

    /**
     * Sets the departure time of the flight plan
     * Preconditions: propperlyInitialised()
     * Postconditions: FlightPlan::getDeparture() == departure
     * @param departure
     */
    void setDeparture(int departure);

    /**
     * Returns the interval between arriving and departing again
     * @return int
     */
    int getInterval() const;

    /**
     * Sets the interval between arriving and departing again
     * Preconditions: propperlyInitialised()
     * Postconditions: FlightPlan::getInterval() == interval
     * @param interval
     */
    void setInterval(int interval);

    /**
     * Returns the arrival time
     * @return int
     */
    int getArrival() const;

    /**
     * Sets the arrival time
     * Preconditions: propperlyInitialised()
     * Postconditions: FlightPlan::getArrival() == arrival
     * @param arrival
     */
    void setArrival(int arrival);

    /**
     * Checks if the flight plan was propperly initialised
     * @return bool
     */
    bool properlyInitialised();

    /**
     * Check if the flight plan is valid
     * @return bool
     */
    bool isValid();
};

#endif //PSE_V1_AIRPLANEROUTE_H
