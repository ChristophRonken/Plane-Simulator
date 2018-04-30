// author: Ronken Christoph & Van Hautte Olivier
// date: 02/05/2018
// version: 2.0

#ifndef PSE_V1_AIRPLANEROUTE_H
#define PSE_V1_AIRPLANEROUTE_H

#include <iostream>
#include <vector>


using namespace std;


class FlightPlan {

    FlightPlan* self;
    string destination;
    int departure;
    int interval;
    int arrival;

public:

    FlightPlan();

    /**
     * Get a string containing the destination airport
     * @return destination
    */
    const string &getDestination() const;

    /**
     * Sets the destination airport
     * @param destination
     */
    void setDestination(const string &destination);

    /**
     * Get an integer containing the departure time
     * @return departure
     */
    int getDeparture() const;

    /**
     * Sets the departure time
     * @param departure
     */
    void setDeparture(const int &departure);

    /**
     * Get an integer containing the interval time
     * @return interval
     */
    int getInterval() const;

    /**
     * Sets the interval time
     * @param interval
     */
    void setInterval(const int &interval);

    /**
     * Get an integer containing the arrival time
     * @return arrival
     */
    int getArrival() const;

    /**
     * Sets the arrival time
     * @param arrival
     */
    void setArrival(const int &arrival);

    /**
     * Check if the FlightPlan is properly initialised
     * @return bool
     */
    bool propperlyInitialised();

    /**
     * Check if the values of the FlightPlan are propperly initialised
     * @return bool
     */
    bool isValid();


};



#endif //PSE_V1_AIRPLANEROUTE_H
