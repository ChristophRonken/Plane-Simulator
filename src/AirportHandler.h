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

enum SuccessEnum {ImportAborted, PartialImport, Success};

class AirportHandler {

    AirportHandler* self;

    vector<Airport*> Airports;
    vector<Airplane*> Airplanes;
    const static double TimeUnit = 0.1;   // in seconds
    const static double simulationStartTime = 12; // in hours


public:
    AirportHandler();

    virtual ~AirportHandler();

    /**
     * Removes an airplane from the saved Airplanes
     * Preconditions: airplaneExists(string)
     * @param callsign
     */
    void removeAirplane(string callsign);

    /**
     * Adds an airport to the saved airports
     * Preconditions: validAirport(Airport*)
     * @param Airport
     */
    void addAirport(Airport *Airport);

    /**
     * Removes an airport from the saved airports
     * Preconditions: airportExists(string)
     * @param callsign
     */
    void removeAirport(string callsign);

    /**
     * Add airplanes, airports and runways from an given xml file.
     * Preconditions: validFileName(string)
     * @param fileName
     */
    SuccessEnum addXmlData(string fileName);

    /**
     * Returns a vector with the saved airports
     * @return Airports
     */
    const vector<Airport *> &getAirports() const;

    /**
     * Sets the saved airports to the given vector of airports.
     * Note that if you already had other airports saved,
     * they will dissapear from this handler
     * and might cause memory leaks if not deleted properly.
     * It is adviced to only use this function to initialize the vector of airports.
     * Precondition: validAirports(vector<Airport*>)
     * @param Airports
     */
    void setAirports(const vector<Airport *> &Airports);

    /**
     * Returns a vector with all the saved airplanes
     * @return Airplanes
     */
    const vector<Airplane *> &getAirplanes() const;

    /**
     * Dets the saved planes to the given vector of planes.
     * Note that if you already had other airplanes saved,
     * they will dissapear from this handler
     * and might cause memory leaks if not deleted properly.
     * It is adviced to only use this function to initialize the vector of airplanes.
     * Precondition: validAirplanes(vector<Airplane*>);
     * @param Airplanes
     */
    void setAirplanes(const vector<Airplane *> &Airplanes);

    /**
     * Adds an airplane to the list of planes
     * Precondition: validAirplane(Airplane*)
     * @param Plane
     */
    void addAirplane(Airplane* Plane);

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
    void fileOutput(string fileName = "AirportInfo.txt");;

    /**
     * Run a simultaion of an airport
     * @param name of the airport to run a simulation on
     */
    void runSimulation(string name);

    /**
     * Get the pointer to the airportwith the given name.
     * @param name of the airport
     * @return Airport*
     */
    Airport* getAirport(string name);

    /**
     * Check if an airplane exists
     * @param callsign
     * @return bool
     */
    bool airplaneExists(string callsign);

    /**
     * Check if an airport already exists.
     * @param callsign
     * @return bool
     */
    bool airportExists(string callsign);

    /**
     * Check if a filename is valid
     * @param name
     * @return bool
     */
    bool validFileName(string name);

    /**
     * Check if the vector of airplanes is valid (no duplicates or faulty initialised airplanes)
     * @param Planes
     * @return bool
     */
    bool validAirplanes(vector<Airplane*> Planes);

    /**
     * Check if the vector of airports is valid (no duplicates or faulty initialised airports)
     * @param Ports
     * @return bool
     */
    bool validAirports(vector<Airport*> Ports);

    /**
     * Check if an airplane is valid to add to the system (no duplicate or faulty initialised)
     * @param Plane
     * @return bool
     */
    bool validAirplane(Airplane* Plane);

    /**
     * Check if an airport is valid to add to the system (no duplicate or faulty initialised)
     * @param Port
     * @return bool
     */
    bool validAirport(Airport* Port);

    /**
     * Check if an airport is empty (no airplanes in or around the airport)
     * @param Port
     * @return bool
     */
    bool airportEmpty(Airport *Port);

    /**
     * Outputs a file with the given airports iata as file name,
     * containing a 2D graphical representation of the Airport in it's current state
     * Preconditions: airportExists(string AirportIata);
     * @param AirportIata
     */
    void GraphicalAirport2D(string & AirportIata);

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
    void GraphicalAirport3D(string & AirportIata);

    /**
     * Check if the Airporthandler was propperly initiallized and isn't NULL
     * @return bool
     */
    bool propperlyInitialised();


};


#endif //PSE_V1_AIRPORTHANDLER_H
