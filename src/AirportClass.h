// author: Ronken Christoph, Van Houtte Olivier
// date: 02/05/2018
// version: 2.0

#ifndef PSE_V1_AirportCLASS_H
#define PSE_V1_AirportCLASS_H

#include <iostream>
#include <sstream>
#include <vector>
#include "AirplaneClass.h"
#include "RunwayClass.h"
#include "MessageSystem.h"

using namespace std;

class Runway;

class Airplane;

class Airport {
private:

    Airport* self;

    string name;
    string iata;
    string callsign;

    int gates;

    vector<bool> gatesOccupied;
    vector<Runway*> runways;

    Airplane* wait5000;
    Airplane* wait3000;

public:

    Airport();

    /**
     * construct an Airport with parameters
     * @param name
     * @param iata
     * @param callsign
     * @param gates
     */
    Airport(const string &name, const string &iata, const string &callsign, int &gates);

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
     * @param gates
     */
    void setGates(int &gates);

    /**
     * get the runways in the airport
     * @return Runways
     */
    const vector<Runway *> &getRunways() const;

    /**
     * set the runways in the airport
     * @param Runways
     */
    void setRunways(const vector<Runway *> &Runways);

    /**
     * get a vector with for each gate index a bool to show if it is occupied
     * @return occuiped gates
     */
    const vector<bool> &getGatesOccupied() const;

    /**
     * set which gates are occupied through a vector
     * @param GatesOccupied
     */
    void setGatesOccupied(const vector<bool> &GatesOccupied);

    /**
     * sets the var of the airport
     * @param Type of the var
     * @param Value of the var
     */
    void setVar(const string &type, const string &value);

    /**
     * adds a runway to the airport
     * Precondition: !runwayExists(string runway)
     * @param runway
     */
    void addRunway(Runway* runway);

    /**
     * removes a runway from the airport
     * Precontition: runwayExists(string name)
     * @param name
     */
    void removeRunway(const string &name);

    /**
     * prints the airports info in the console
     */
    void printInfo();

    /**
     * gets the airports info as a string
     * @return
     */
    string getInfo();

    /**
     * set a certain gate to occ
     * Precondition: validGateIndex(int i)
     * @param int i : index of the gate
     * @param bool occ : occupied or not
     */
    void setGateOccupied(const int &i, const bool &occ);

    /**
     * Returns the occupied state of a gate 
     * Precondition: validGateIndex(int)
     * @param int i
     * @return occupied
     */
    bool getGateOccupied(const int &i);

    /**
     * Returns a vector with the indexes of all the free gates
     * @return FreeGates
     */
    vector<int> getFreeGates();

    /**
     * Returns a vector with the indexes of all the free Runways
     * @return FreeRunways
     */
    vector<int> getFreeRunways();

    /**
     * Check if the gate index is valid and unoccupied
     * @param i
     * @return bool
     */
    bool validGateIndex(const int &i);

    /**
     * Check if the runway with the given name exists
     * @param name
     * @return bool
     */
    bool runwayExists(const string &name);

    /**
     * Get the Airplane that is currently waiting at height 5000.
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
     * @param plane
     */
    void setWait5000(Airplane* plane);

    /**
     * Set the Airplane that is currently waiting at height 3000.
     * @param plane
     */
    void setWait3000(Airplane* plane);

    /**
     * Get the runway by name (string)
     * Precontition: runwayExists(string name)
     * @return Runway
     */
    Runway* getRunway(const string &name);

    /**
     * Check if the airport is properly initialised
     * @return
     */
    bool properlyInitialised();

    /**
     * Check if the values of the airport are propperly initialised
     * @return bool
     */
    bool isValid();

};


#endif //PSE_V1_AirportCLASS_H
