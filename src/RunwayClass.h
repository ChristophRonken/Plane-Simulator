// author: Ronken Christoph & Van Hautte Olivier
// date: 02/05/2018
// version: 2.0

#ifndef PSE_V1_RUNWAYCLASS_H
#define PSE_V1_RUNWAYCLASS_H

#include <iostream>
#include <vector>
#include "AirportClass.h"
#include "TaxiRoute.h"
#include "Utils.h"


using namespace std;

class Airport;

class Runway {

    Runway* self;
    string name;
    Airport* airport;

    string type;
    int length;

    bool occupied;

    TaxiRoute * taxiRoute;

    bool holdingShortOccupied;
    bool waitingOnRunway;
    bool permissionToCross;
    bool crossing;

    bool onItsWay;

public:
    /**
      * Construct a runway with parameters
      * @param name
      * @param airport
      */
    Runway(const string &name, Airport *airport);

    /**
     * Construct a runway and set parameters later
     */
    Runway();

    /**
     * get the name of the runway
     * @return name
     */
    const string &getName() const;

    /**
     * set the name of the runway
     * @param name
     */
    void setName(const string &name);

    /**
     * get the airport the runway is located at
     * @return Airport
     */
    Airport *getAirport() const;

    /**
     * sets the airport the runway is located at
     * @param Port
     */
    void setAirport(Airport* airport);

    /**
     * gets if the runway is occupied
     * @return occupied
     */
    bool isOccupied() const;

    /**
     * Sets occupied to the given param
     * @param occupied
     */
    void setOccupied(const bool &occupied);

    /**
     * Returns the runway type
     * @return string
     */
    const string &getType() const;

    /**
     * sets the runway type
     * Preconditions: type == "grass" || type == "asphalt"
     * @param type
     */
    void setType(const string &type);

    /**
     * get the length of the runway
     * @return int
     */
    int getLength() const;

    /**
     * set the length of the runway
     * @param length
     */
    void setLength(const int &length);

    /**
     * Set the value of the variable with name == type
     * If the type is invalid, nothing happens
     * @param type
     * @param value
     */
    void setVar(const string &type, const string &value);

    /**
     *  Set the taxiRoute
     * @param taxi
     */
    void setTaxiRoute(TaxiRoute* taxi);

    /**
     * Returns the taxiRoute
     * @return 
     */
    TaxiRoute* getTaxiRoute();
    
    /**
     * Set if a plane is in the holding short position
     */
    void setHoldingShortOccupied(const bool &holdingShortOccupied);

    /**
     * Set if a plane is already waiting for take off on the runway
     */
    void setWaitingOnRunway(const bool &waitingOnRunway);

    /**
     * Check if the holding position for planes is occupied
     * @return bool
     */
    bool getHoldingShortOccupied();

    /**
     * Check if a plane is waiting for take off on the runway
     * @return bool
     */
    bool getWaitingOnRunway();

    /**
     * Check if a plane is crossing the runway
     * @return bool
     */
    bool getCrossing();

    /**
     * Set if a plane is crossing the runway
     */
    void setCrossing(const bool &crossing);

    /**
     * Check if a plane has permission to cross the runway
     * @return bool
     */
    bool getPermissionToCross();

    /**
     * Set if a plane has permission to cross te runway
     */
    void setPermissionToCross(const bool &permissionToCross);

    /**
     * Check if the plane is propperly initialised
     * @return bool
     */
    bool propperlyInitialised();

    /**
     * Check if the Values of the runway are valid
     * @return bool
     */
    bool isValid();

    /**
     * Check if the a plane is on its way to the runway
     * @return bool
     */
    bool getonItsWay();

    /**
     * Sets the bool representing a plane on its way or not
     * @return bool
     */
    void setonItsWay(const bool &onItsWay);

};


#endif //PSE_V1_RUNWAYCLASS_H
