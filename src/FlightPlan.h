//
// Created by oliviervh on 12.04.18.
//

#ifndef PSE_V1_AIRPLANEROUTE_H
#define PSE_V1_AIRPLANEROUTE_H

#include <iostream>
#include <vector>
#include "DesignByContract.h"

using namespace std;


class FlightPlan {

    FlightPlan* self;
    string destination;
    int departure;
    int interval;
    int arrival;

public:

    FlightPlan();

    const string &getDestination() const;

    void setDestination(const string &destination);

    int getDeparture() const;

    void setDeparture(int departure);

    int getInterval() const;

    void setInterval(int interval);

    int getArrival() const;

    void setArrival(int arrival);

    bool propperlyInitialised();

    bool isValid();


};



#endif //PSE_V1_AIRPLANEROUTE_H
