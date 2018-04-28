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
    Airport* airPort;

    string type;
    int length;

    bool occupied;

    TaxiRoute * taxiRoute;

    bool holdingShortOccupied;
    bool wachtoprunway;
    bool permissiontocross;
    bool crossing;

public:
    /**
      * Construct a runway with parameters
      * @param name
      * @param airPort
      */
    Runway(const string &name, Airport *airPort);

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
    void setAirport(Airport* Port);

    /**
     * gets if the runway is occupied
     * @return occupied
     */
    bool isOccupied() const;

    /**
     * Sets occupied to the given param
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
    void setLength(int length);

    /**
     * Set the value of the variable with name == Type
     * If the type is invalid, nothing happens
     * @param Type
     * @param Value
     */
    void setVar(string Type, string Value);

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
    
    void setHoldingShortOccupied(bool);

    void setWaitingOnRunway(bool);

    bool getHoldingShortOccupied();

    bool getWaitingOnRunway();

    bool getCrossing();

    void setCrossing(bool);

    bool getPermissionToCross();

    void setPermissionToCross(bool);

    bool propperlyInitialised();
    
    bool isValid();

};


#endif //PSE_V1_RUNWAYCLASS_H
