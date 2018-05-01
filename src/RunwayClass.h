//
// Created by oliviervh on 01.03.18.
//

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
     * Postconditions: Runway::getName() == name
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
     * Postconditions: Runway::getAirport() == airport
     * @param airport
     */
    void setAirport(Airport* airport);

    /**
     * gets if the runway is occupied
     * @return occupied
     */
    bool isOccupied() const;

    /**
     * Sets occupied to the given param
     * Postconditions: Runway::isOccupied() == occupied
     * @param occupied
     */
    void setOccupied(bool occupied);

    /**
     * Returns the runway type
     * @return string
     */
    const string &getType() const;

    /**
     * sets the runway type
     * Preconditions: type == "grass" || type == "asphalt"
     * Postconditions: Runway::getType() == type
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
     * Postconditions: Runway::getLength() == length,
     * @param length
     */
    void setLength(int length);

    /**
     * Set the value of the variable with name == type
     * If the type is invalid, nothing happens
     * @param type
     * @param value
     */
    void setVar(string type, string value);

    /**
     * Set the taxiRoute
     * Postconditions: Runway::getTaxiRoute() == taxi
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
     * Postcondition: Runway::getHoldingShortOccupied() == holdingShortOccupied
     * @param holdingShortOccupied
     */
    void setHoldingShortOccupied(bool holdingShortOccupied);

    /**
     * Set if a plane is already waiting for take off on the runway
     * Postcondition: Runway::getWaitingOnRunway() == waitingOnRunway
     * @param waitingOnRunway
     */
    void setWaitingOnRunway(bool waitingOnRunway);

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
     * Postcondition: Runway::getCrossing() == crossing
     * @param crossing
     */
    void setCrossing(bool crossing);

    /**
     * Check if a plane has permission to cross the runway
     * @return bool
     */
    bool getPermissionToCross();

    /**
     * Set if a plane has permission to cross te runway
     * Postconditions: Runway::getPermissionToCross() == permissionToCross
     * @param permissionToCross
     */
    void setPermissionToCross(bool permissionToCross);

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
     * Returns true if a plane is on it's way towards the Runway
     * @return
     */
    bool getOnItsWay();

    /**
     * Set if a plane is on it's way
     * Postconditions: Runway::getOnItsWay() == onItsWay
     * @param onitsway
     */
    void setOnItsWay(bool onItsWay);

};


#endif //PSE_V1_RUNWAYCLASS_H
