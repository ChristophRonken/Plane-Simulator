//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_AirportCLASS_H
#define PSE_V1_AirportCLASS_H

#include <iostream>
#include <sstream>
#include "AirplaneClass.h"
#include "RunwayClass.h"
#include "MessageSystem.h"
#include <vector>
#include <algorithm>
#include "Utils.h"


using namespace std;

class Runway;

class Airplane;

class Airport {

    Airport* self;

    string name;
    string iata;
    string callsign;

    int gates;

    vector<bool> gatesOccupied;

    Airplane* wait5000;
    Airplane* wait3000;

public:
    vector<Runway*> runways;

    Airport();

    /**
     * construct an Airport with parameters
     * @param name
     * @param iata
     * @param callsign
     * @param gates
     */
    Airport(const string &name, const string &iata, const string &callsign, int gates);

    /**
     * Airport destructor
     */
    virtual ~Airport();

    /**
     * get the name of the Airport
     * @return name
     */
    const string &getName() const;

    /**
     * set the name of the airport
     * Postconditions: Airport::getName() == name
     * @param name
     */
    void setName(const string &name);

    /**
     * get the iata of the airport
     * @return Iata
     */
    const string &getIata() const;

    /**
     * set the iata of the airport
     * Postconditions: Airport::getIata() == iata
     * @param iata
     */
    void setIata(const string &iata);

    /**
     * get the callsign of the airport
     * @return callsign
     */
    const string &getCallsign() const;

    /**
     * sets the callsign of the airport
     * Postconditions: Airport::getCallsign() == callsign
     * @param callsign
     */
    void setCallsign(const string &callsign);

    /**
     * get the amount of gates in the airport
     * @return gates
     */
    int getGates() const;

    /**
     * set the amount of gates in the airport
     * Postconditions: Airport::getGates() == gates
     *      && Airport:getGatesOccupied().size() == unsigned(Airport::getGates())
     * @param gates
     */
    void setGates(int gates);

    /**
     * get the runways in the airport
     * @return Runways
     */
    const vector<Runway *> &getRunways() const;

    /**
     * set the runways in the airport
     * Preconditions: Airport::validRunways(runways)
     * Postconditions: Airport::getRunways() == runways
     * @param Runways
     */
    void setRunways(const vector<Runway *> &Runways);

    /**
     * get a vector with for each gate index a bool ti show if it's occupied
     * @return occuiped gates
     */
    const vector<bool> &getGatesOccupied() const;

    /**
     * set wich gates are occupied through a vector
     * Postconditions: Airport::getGatesOccupied() == gatesOccupied
     * @param GatesOccupied
     */
    void setGatesOccupied(const vector<bool> &GatesOccupied);

    /**
     * adds a runway to the airport
     * Preconditions: !runwayExists(runway->getName())
     *      && !runway->getName().empty()
     *      && (runway->getType() == "asphalt" or runway->getType() == "grass")
     *      && !Airport::runwayExists(runway->getName())
     * Postcondition: Airport::runwayExists(runway->getName())
     * @param runway
     */
    void addRunway(Runway* runway);

    /**
     * removes a runway from the airport
     * Precontition: Airport::runwayExists(name)
     *      && !name.empty()
     * Postcondition: !Airport::runwayExists(name)
     * @param name
     */
    void removeRunway(const string &name);

    /**
     * gets the airports info as a string
     * @return
     */
    string getInfo();

    /**
     * set a certain gate to occ
     * Precondition: validGateIndex(i)
     * Postcondition: Airport::getGateOccupied(i) == occ
     * @param int i : index of the gate
     * @param bool occ : occupied or not
     */
    void setGateOccupied(int i, bool occ);

    /**
     * get if a certain gate is occupied
     * Precondition: validGateIndex(int)
     * @param int i
     * @return occupied
     */
    bool getGateOccupied(int i);

    /**
     * Returns a vector with the indexes of all the free gates
     * Postconditions: &result != NULL
     * @return FreeGates
     */
    vector<int> getFreeGates();

    /**
     * Returns a vector with the indexes of all the free Runways
     * Postconditions: &result != NULL
     * @return FreeRunways
     */
    vector<int> getFreeRunways();

    /**
     * Check if the gate index is valid and unoccupied
     * @param i
     * @return bool
     */
    bool validGateIndex(int i);

    /**
     * Check if the runway with the given name exists
     * @param name
     * @return bool
     */
    bool runwayExists(const string &name);

    /**
     * Get the Airplane that is currentle waiting at height 5000.
     * @return
     */
    Airplane* getWait5000();

    /**
     * Get the Airplane that is currently waiting at height 3000.
     * @return
     */
    Airplane* getWait3000();

    /**
     * Set the Airplane that is currently waiting at height 5000.
     * Postcondition: Airport::getWait5000() == plane
     * @param plane
     */
    void setWait5000(Airplane* plane);

    /**
     * Set the Airplane that is currently waiting at height 3000.
     * Postcondition: Airport::getWait3000() == plane
     * @param plane
     */
    void setWait3000(Airplane* plane);

    /**
     * Get the runway by name (string)
     * if the runway doesn't exist, it return NULL
     * @return Runway
     */
    Runway* getRunway(const string &name);

    /**
     * Check if the airport is propperly initialised
     * @return
     */
    bool properlyInitialised();

    /**
     * Check if the values of the airport are propperly initialised
     * @return bool
     */
    bool isValid();

    /**
     * Checks if a vetor of runways is valid to set as this airport's runways
     * @param runways
     * @return
     */
    bool validRunways(vector<Runway*> runways);

};


#endif //PSE_V1_AirportCLASS_H
