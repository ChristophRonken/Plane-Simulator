//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_RUNWAYCLASS_H
#define PSE_V1_RUNWAYCLASS_H

#include <iostream>
#include "AirportClass.h"
#include "TaxiRoute.h"
#include<vector>

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

    bool wachtaanrunway;
    bool wachtoprunway;
    bool permissiontocross;
    bool crossing;

    int aantalvliegtuigen;

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
     * sets occupied to the given param
     * @param occupied
     */
    void setOccupied(bool occupied);

    const string &getType() const;

    void setType(const string &type);

    int getLength() const;

    void setLength(int length);

    void setVar(string Type, string Value);

    void setTaxiRoute(TaxiRoute* taxi);

    TaxiRoute* getTaxiRoute();

    void setWachtaanRunway(bool);

    void setWachtopRunway(bool);

    bool getWachtaanRunway();

    bool getWachtopRunway();

    bool getCrossing();

    void setCrossing(bool);

    bool getPermissionToCross();

    void setPermissionToCross(bool);

    int getAantalVliegtuigen();

    void setAantalVliegtuigen(int);

    bool propperlyInitialized();
    
    bool isValid();

};


#endif //PSE_V1_RUNWAYCLASS_H
