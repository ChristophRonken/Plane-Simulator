//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_AIRPORTHANDLER_H
#define PSE_V1_AIRPORTHANDLER_H

#include <fstream>
#include <ctime>
#include <cmath>
#include "AirportClass.h"
#include "AirplaneClass.h"
#include "RunwayClass.h"
#include "TaxiRoute.h"
#include "FlightPlan.h"
#include "../xml/tinyxml.h"

enum ESuccess {importAborted, partialImport, success};

class AirportHandler {

    AirportHandler* self;

    vector<Airport*> airports;
    vector<Airplane*> airplanes;
    const static double gTimeUnit = 0.1;   // in seconds
    const static double gSimulationStartTime = 12; // in hours
    vector<int> occupiedColor;
    vector<int> freeColor;

public:
    AirportHandler();

    virtual ~AirportHandler();

    /**
     * Removes an airplane from the saved Airplanes
     * Preconditions: AirportHandler::airplaneExists(callsign)
     * Postconditions: !AirportHandler::airplaneExists(callsign)
     * @param callsign
     */
    void removeAirplane(const string &number);


    /**
     * Adds an airport to the saved airports
     * Preconditions: AirportHandler::validAirport(Airport*)
     * @param airport
     */
    void addAirport(Airport *airport);

    /**
     * Removes an airport from the saved airports
     * Preconditions: AirportHandler::airportExists(iata)
     * Postcondition: !AirportHandler::airportExists(iata)
     * @param iata
     */
    void removeAirport(const string &iata);

    /**
     * Add airplanes, airports and runways from an given xml file.
     * Preconditions: AirportHandler::validFileName(string)
     * @param fileName
     */
    ESuccess addXmlData(const string &fileName);

    /**
     * Returns a vector with the saved airports
     * @return airports
     */
    const vector<Airport *> &getAirports() const;

    /**
     * Sets the saved airports to the given vector of airports.
     * Note that if you already had other airports saved,
     * they will dissapear from this handler
     * and might cause memory leaks if not deleted properly.
     * It is adviced to only use this function to initialize the vector of airports.
     * Precondition: validAirports(vector<Airport*>)
     * Postcondition: Airports == AirportHandler::getAirports()
     * @param airports
     */
    void setAirports(const vector<Airport *> &airports);

    /**
     * Returns a vector with all the saved airplanes
     * @return airplanes
     */
    const vector<Airplane *> &getAirplanes() const;

    /**
     * Dets the saved planes to the given vector of planes.
     * Note that if you already had other airplanes saved,
     * they will dissapear from this handler
     * and might cause memory leaks if not deleted properly.
     * It is adviced to only use this function to initialize the vector of airplanes.
     * Precondition: AirportHandler::validAirplanes(Airplanes);
     * Postconditions: AirportHandler::getAirplanes() == Airplanes
     * @param airplanes
     */
    void setAirplanes(const vector<Airplane *> &airplanes);

    /**
     * Adds an airplane to the list of planes
     * Precondition: AirportHandler::validAirplane(Airplane*)
     * Postconditions: AirportHandler::airplaneExists(Plane->getNumber())
     * @param Plane
     */
    void addAirplane(Airplane* airplane);

    /**
     * Get a string with the info of all planes and airports
     * @return info
     */
    string getInfo();

    /**
     * Prints info of the planes and airports in the console
     */
    void printInfo();

    /**
     * Outputs a file, with the info of the airplanes and airports, to the working directory
     */
    void fileOutput(const string &fileName = "AirportInfo.txt");;

    /**
     * Run a simultaion of an airport
     * Preconditions: !AirportHandler::getAirports().empty()
     * @param name of the airport to run a simulation on
     */
    void runSimulation(const string &name);

    /**
     * Get the pointer to the airportwith the given name.
     * @param name of the airport
     * @return Airport*
     */
    Airport* getAirport(const string &name);

    /**
     * Check if an airplane exists
     * @param callsign
     * @return bool
     */
    bool airplaneExists(const string &callsign);

    /**
     * Check if an airport already exists.
     * @param callsign
     * @return bool
     */
    bool airportExists(const string &iata);

    /**
     * Check if a filename is valid
     * @param name
     * @return bool
     */
    bool validFileName(const string &name);

    /**
     * Check if the vector of airplanes is valid (no duplicates or faulty initialised airplanes)
     * @param Planes
     * @return bool
     */
    bool validAirplanes(vector<Airplane*> airplanes);

    /**
     * Check if the vector of airports is valid (no duplicates or faulty initialised airports)
     * @param Ports
     * @return bool
     */
    bool validAirports(vector<Airport*> airports);

    /**
     * Check if an airplane is valid to add to the system (no duplicate or faulty initialised)
     * @param Plane
     * @return bool
     */
    bool validAirplane(Airplane* airplane);

    /**
     * Check if an airport is valid to add to the system (no duplicate or faulty initialised)
     * @param Port
     * @return bool
     */
    bool validAirport(Airport* airport);

    /**
     * Check if an airport is empty (no airplanes in or around the airport)
     * @param Port
     * @return bool
     */
    bool airportEmpty(Airport *airport);

    /**
     * Outputs a file with the given airports iata as file name,
     * containing a 2D graphical representation of the Airport in it's current state
     * Preconditions: airportExists(string AirportIata);
     * @param AirportIata
     */
    void GraphicalAirport2D(const string &iata);

    /**'
     * Changes a double to it's corresponding time in string format (hh:mm)
     * Time is relative to the starting time of the simulation (default = 12:00)
     * @param passedTimeUnits
     * @return string
     */
    string timeToString(double passedTimeUnits);

    /**
     * Outputs an ini file containg the data to be read in a graphical engine
     * to represent the airport in a 3D environement
     * @param AirportIata
     */
    void GraphicalAirport3D(const string &iata);

    /**
     * Check if the Airporthandler was propperly initiallized and isn't NULL
     * @return bool
     */
    bool propperlyInitialised();


};


#endif //PSE_V1_AIRPORTHANDLER_H
