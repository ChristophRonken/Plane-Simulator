//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_AirplaneCLASS_H
#define PSE_V1_AirplaneCLASS_H

#include <iostream>
#include <cmath>
#include <map>

#include "Airport.h"
#include "RunwayClass.h"
#include "FlightPlan.h"
#include "TaxiRoute.h"
#include "DesignByContract.h"
#include "Utils.h"

using namespace std;

class Airport;
class Runway;

enum ESqauwkCode {privateSmallSquawk, privateMediumSquawk, airlineMediumPropellerSquawk, airlineMediumJetSquawk,
                    airlineLargeSquawk, militarySquawk, emegencySquawk};

enum EState {   init, incoming, descending, descendARMS, descendWait,
                descendBRMS, descendCRMS, onFinalApproach, landing, onRunway,
                outOfFuel,iEmergencyRMS, oEmergencyRMS, iEmergencyMMS, oEmergencyMMS,
                eLanded, eUnboardingPassengers, gUnboardingPassengers, eTechnicalCheck, gTechnicalCheck,
                eRefuel, gRefuel, inGate, boardPassengers, ifr,
                ifrRMS, ifrMMS, ifrCMS, pushbackRMS, pushbackMMS,
                pushbackCMS, taxiRequest, onTaxiPoint, taxiPointMMS, taxiPointCMS,
                onTaxiCrossing, taxiCrossingRMS, taxiCrossingMMS, taxiCrossingCMS, taxiCrossingNF,
                onHoldingPoint, holdingPointRMS, holdingPointMMS, holdingpointCMS, ascending,
                simulationIsFinished, idle};

const int kSmall = 1;
const int kMedium = 2;
const int kLarge = 3;

const int kRunwayLengthA = 500;
const int kRunwayLengthB = 1000;
const int kRunwayLengthC = 1500;
const int kRunwayLengthD = 2000;
const int kRunwayLengthE = 3000;

class Airplane {

    Airplane* self;

    string number;
    string callsign;
    string model;
    EState state;
    string engine;
    string size;
    string type;


    Airport* airport;
    Runway* runway;
    Runway* attemptRunway;

    int gate;
    int fuel;
    int fuelCapacity;
    int passengers;
    int passengerCapacity;
    int height;
    int operationTime;
    int attemptGate;
    int crossingIndex;
    int squawkCode;

    string currentTask;

    FlightPlan* flightPlan;
    TaxiRoute* taxiRoute;
    string taxiPoint;
    string taxiCrossing;

    bool alreadyLinedUp;
    bool permissionToTakeOff;

    bool technicalChecked;

    bool waitAtRunway;
    bool waitOnRunway;

    bool simulationFinished;

    const static int kFuelPerMinute = 10000;
    const static int kBoardingExitingTime = 5;
    const static int kProprellerDescentionSpeed = 500;
    const static int kJetDescentionSpeed = 1000;
    const static int kProprellerAscentionSpeed = 500;
    const static int kJetAscentionSpeed = 1000;

    const static int kHeightLevelA = 10000;
    const static int kHeightLevelB = 5000;
    const static int kHeightLevelC = 3000;
    const static int kHeightLevelD = 1000;
protected:


public:

    Airplane(string type = "none")  ;

    virtual ~Airplane();

    bool getTechnicalChecked() const;
    void setTechnicalChecked(bool boolean);

    /**
     * get the ID number
     * @return
     */
    const string &getNumber() const;

    /**
     * Set ID number
     * Postcondition: Airplane::getNumber() == number
     * @param number
     */
    void setNumber(const string &number);

    /**
     * returns the planes callsign
     * @return callsign
     */
    const string &getCallsign() const;

    /**
     * sets the planes callsign
     * Postcondition: Airplane::getCallsign() == callsign
     * @param callsign
     */
    void setCallsign(const string &callsign);

    /**
     * get plane model
     * @return model type
     */
    const string &getModel() const;

    /**
     * set planes model
     * Postcondition: Airplane::getModel() == model
     * @param model
     */
    void setModel(const string &model);

    /**
     * get current state of the plane
     * @return state
     */
    const EState &getState() const;

    /**
     * sets the state of the plane
     * Postcondition: Airplane::getState() == state
     * @param state
     */
    void setState(const EState &state);

    /**
     *returns a pointer to the current airport
     * @return Airport *
     */
    Airport *getAirport() const;

    /**
     * sets the current airport
     * Postcondition: Airplane::getAirport() == airport
     * @param airport
     */
    void setAirport(Airport *airport);

    /**
     * returns a pointer to the current runway
     * @return Runway*
     */
    Runway *getRunway() const;

    /**
     * sets the current runway
     * Postcondition: Airplane::getRunway() == runway
     * @param runway
     */
    void setRunway(Runway *runway);

    /**
     * returns the current gate number
     * @return gate
     */
    int getGate() const;

    /**
     * Sets the gate index
     * Preconditions: validGate(gate) && (gate == -1 || Airport::atGate())
     * Postconditions: Airplane::getGate() == gate
     * @param gate
     */
    void setGate(int gate);

    /**
     * returns the amount of fuel
     * @return fuel
     */
    int getFuel() const;

    /**
     * Sets the amount of fuel
     * Postcondition: Airplane::getFuel() == fuel
     * @param fuel
     */
    void setFuel(int fuel);

    /**
     * Get the max fuel capacity
     * @return int
     */
    int getFuelCapacity() const;

    /**
     * Sets the max fuel capacity
     * Postcondition: Airplane::getFuelCapacity() == fuelCapacity
     * @param fuelCapacity
     */
    void setFuelCapacity(int fuelCapacity);

    /**
     * get the amount of passengers
     * @return passengers
     */
    int getPassengers() const;

    /**
     * sets the amount of passengers
     * Postcondition: Airplane::getPassengers() == passengers
     * @param passengers
     */
    void setPassengers(int passengers);

    /**
     * gets the max passenger capacity of the plane
     * @return passengerCapassity
     */
    int getPassengerCapacity() const;

    /**
     * sets the max passenger capacity
     * Postcondition: Airplane::getPassengerCapacity() == passengerCapacity
     * @param passengerCapacity
     */
    void setPassengerCapacity(int passengerCapacity);

    /**
     * Get the current flying height of the airplane
     * @return int
     */
    int getHeight() const;

    /**
     * Set the current flying height of the airplane
     * Postcondition: Airplane::getHeight() == height
     * @param height
     */
    void setHeight(int height);

    /**
     * Get the type of airplane
     * @return aiplane type
     */
    const string &getType() const;

    /**
     * Set the type of the airplane
     * Preconditions: Airplane::validPlaneType(type)
     * Postcondition: Airplane::getType() == type)
     * @param type
     */
    void setType(const string &type);

    /**
     * Get the engine of the airplane
     * @return engine
     */
    const string &getEngine() const;

    /**
     * Sets the engine of the airplane
     * Preconditions: Airplane::validEngine(engine)
     * Postcondition: Airplane::getEngine() == engine
     * @param engine
     */
    void setEngine(const string &engine);

    /**
     * Get the size of the plane
     * @return size
     */
    const string &getSize() const;

    /**
     * Sets the size of the airplane
     * Preconditions: Airplane::validSize(size)
     * Postcondition: Airplane::getSize() == size
     * @param size
     */
    void setSize(const string &size);

    /**
     * Get the operation time of the airplane
     * @return int
     */
    int getOperationTime() const;

    /**
     * Sets the operation time of the airplane
     * Postcondition: Airplane::getOperationTime() == operationTime
     * @param operationTime
     */
    void setOperationTime(int operationTime);


    /**
     * gets the info of the plane as a string
     * @return info
     */
    string getInfo();

    /**
     * retursn true if the plane is ready for departure
     * @return readyForDeparture
     */
    bool isReadyForDeparture() const;

    /**
     * lands the plane in the given airport
     * A runway is optional
     * Precondition: Airplane::validLandingSpot(airport)
     *      && (Airplane::getCurrentTask() == "try to land"
     *      || Airplane::getCurrentTask() == "landing"
            || Airplane::getCurrentTask() == "descending to 5000ft."
            || Airplane::getCurrentTask() == "descending to 3000ft."
            || Airplane::getCurrentTask() == "descending to 0ft.")
     * Postconditions:  Airplane::getState() == "At runway"
     *      || Airplane::getRunway() != NULL
     * @param airport
     * @param R
     */
    void land(Airport* airport);

    /**
     * sends the plane to the given runway
     * if no runway was given, it will choose the first free runway
     * Precondition: Airplane::atAirport() && validRunway() &&
     *      Airplane::getCurrentTask() == "IFR" || Airplane::getCurrentTask() == "pushback"
     *      || Airplane::getCurrentTask() == "request taxi" && Airplane::flightPlan != NULL
     */
    void pushBack();

    /**
     * send the plane to exit the airport
     * Precondition: Airplane::readyForTakeOff()
     *      && (Airplane::getCurrentTask() == "taking off"
     *      || Airplane::getCurrentTask() == "at holding point")
     *      && Airplane::getRunway() != NULL
     *      && Airplane::getAirport() != NULL
     * Postconditions: Airplane::getRunway() == NULL
     *      && Airplane::getState() == "Airborne"
     *      && Airplane::getAirport() == NULL
     *      && Airplane::getHeight() != 0
     */
    void takeOff();

    /**
     * Check if the plane finished all it's tasks
     * @param airport
     * @return bool
     */
    bool notFinished();

    /**
     * execute a task
     * @param airport
     */
    void execTask(Airport* airport);

    /**
     * Get the destination of this airplane
     * @return string
     */
    const string &getDestination();

    /**
     * Initialize the plane's variables to start a simulation
     * @param airport
     */
    void initSimulation(Airport *airport);

    /**
     * Check if the gate index is both valid and unoccupied
     * @param gate
     * @return bool
     */
    bool validGate(int gate = -1);

    /**
     * Check if this airplane can take off/land on the given Runway.
     * If no runway is given, it will see if a Runway exists with the same requirements
     * @param runway
     * @return bool
     */
    virtual bool validRunway(Runway* runway = NULL);

    /**
     * Check if the location to land is valid
     * @param airport
     * @param runway
     * @return bool
     */
    bool validLandingSpot(Airport* airport, Runway* runway = NULL );

    /**
     * Check if the airplane is at an airport
     * @return bool
     */
    bool atAirport();

    /**
     * Check if the airplane is at a gate
     * @return bool
     */
    bool atGate();

    /**
     * Check if the airplane is ready for take-off
     * @return bool
     */
    bool readyForTakeOff();

    /**
     * Set the squawk code of this plane
     * If none was given, it will generate an appropriate code
     * Postconditions: !Airplane::getSquawkCode().empty()
     * @param code
     */
    void setSquawkCode(int code = 0);

    /**
     * Get the current squawk code
     * @return bool
     */
    int getSquawkCode() const;

    /**
     * Set the flight plan of this airplane
     * Postconditions: Airplane::getFlightPlan() == flightPlan
     * @param Flight
     */
    void setFlightPlan(FlightPlan *Flight);

    /**
     * Get the flightplane of this plane
     * @return FlightPlan*
     */
    FlightPlan * getFlightPlan() const;

    /**
     * Get the runway the airplane is trying to go to.
     * @return Runway
     */
    Runway *getAttemptRunway() const;

    /**
     * Set the runway the airplane is trying to go to.
     * Postconditions: Airplane::getAttemptRunway() == attemptRunway
     * @param attemptRunway
     */
    void setAttemptRunway(Runway *attemptRunway);

    /**
     * Get the taxiRoute the plane is taking
     * @return TaxiRoute*
     */
    TaxiRoute *getTaxiRoute() const;

    /**
     * Set the taxiRoute the plane is taking
     * Postconditions: Airplane::getTaxiRoute() == taxiRoute
     * @param taxiRoute
     */
    void setTaxiRoute(TaxiRoute *taxiRoute);

    /**
     * Get the taxipoint the plane is on
     * @return string
     */
    const string &getTaxiPoint() const;

    /**
     * set the taxipoint the plane is on
     * Postconditions: Airplane::getTaxiPoint() == taxiPoint
     * @param taxiPoint
     */
    void setTaxiPoint(const string &taxiPoint);

    /**
     * Get the taxiCrossing the plane is on
     * @return string
     */
    const string &getTaxiCrossing() const;

    /**
     * Set the taxiCrossing the plane is on
     * Postconditions: Airplane::getTaxiCrossing() == taxiCrossing
     * @param taxiCrossing
     */
    void setTaxiCrossing(const string &taxiCrossing);

    /**
     * Get the gate index the plane is trying to go to
     * @return int
     */
    int getAttemptGate() const;

    /**
     * Set the gate index the plane is trying to go to
     * Postcondition: Airplane::getAttemptgate() == attemptgate
     * @param attemptgate
     */
    void setAttemptGate(int attemptgate);

    /**
     * Check if the airplane has permission to descend
     * @param height
     * @param airport
     * @param Runway
     * @return bool
     */
    bool permissionToDescend(int, Airport*, Runway*);

    /**
     * Make the airplane taxi to a (given) runway if possible
     * Preconditions: Airplane::getCurrentTask() == "going to runway" &&
     * (Airplane::getAttemptRunway() != NULL
     */
    void taxiToRunway();

    /**
     * Make the airplane taxi to a given gate
     * @param gate
     */
    void taxiToGate(int gate = -1);

    /**
     * Perform an emergency landing
     * @param airport
     */
    void emergencyLanding(Airport*);

    /**
     * Check if the input value would be a valid engine type for the airplane.
     * @param engine
     * @return bool
     */
    virtual bool validEngineType(const string &type);

    /**
     * check if the input value would be a valid size for the airplane
     * @param size
     * @return bool
     */
    virtual bool validSize(const string &size);

    /**
     * Let passengers exit the plane
     */
    void exitPlane();

    /**
     * Let passengers enter the plane
     */
    void enterPlane();

    /**
     * Perform a technical Check on the airplane
     */
    void technicalCheck();

    /**
     * Refuel the airplane
     */
    void refuel();


    /**
     * Check if the plane was properly initialized
     * @return bool
     */
    bool properlyInitialised();

    /**
     * Check if all set values are valid to run a simulation (flightplan excluded)
     * @return bool
     */
    bool isValid();

    /**
     * Check if the simulation was finished
     * @return bool
     */
    bool getSimulationFinished();

   /**
    * Set if the simulation was finished
    * Postcondition: Airplane::getsimulationFinished() == finished
    * @param finished
    */
    void setSimulationFinished(bool finished);

    /**
     * Get the current task the plane is performing
     * @return string
     */
    const string &getCurrentTask() const;

    /**
     * Set the current task the plane is performing
     * Postconditions: Airplane::getCurrentTask() == currentTask
     * @param currentTask
     */
    void setCurrentTask(const string &currentTask);

    /**
     * Preform tasks that happen over a longer period
     */
    void continueTask(Airport * airport);

    /**
     * Descend X ft
     */
    void descend(Airport * airport);

    /**
     * Ascend X ft
     */
    void ascend(Airport * airport);

    /**
     * Returns boolean isWaitAtRunway
     * @return isWaitAtRunway
     */
    bool isWaitAtRunway() const;

    /**
    * sets bool waitAtRunway
    * Postconditions: Airplane::isWaitAtRunway() == waitAtRunway
    * @param waitAtRunway
    */
    void setWaitAtRunway(bool waitAtRunway);

    /**
     * Returns boolean isWaitOnRunway
     * @return isWaitOnRunway
     */
    bool isWaitOnRunway() const;

    /**
    * sets bool waitOnRunway
    * Postconditions: Airplane::isWaitOnRunway() == waitOnRunway
    * @param waitOnRunway
    */
    void setWaitOnRunway(bool waitOnRunway);

    /**
     * Returns boolean alreadyLinedUp
     * @return alreadyLinedUp
     */
    bool isAlreadyLinedUp() const;

    /**
    * sets bool alreadyLinedUp
    * Postconditions: Airplane::isAlreadyLinedUp() == alreadyLinedUp
    * @param alreadyLinedUp
    */
    void setAlreadyLinedUp(bool alreadyLinedUp);

    /**
     * Returns boolean isPermissionToTakeOff
     * @return isPermissionToTakeOff
     */
    bool isPermissionToTakeOff() const;

    /**
    * sets bool permissionToTakeOff
     * Postconditions: Airplane::isPermissionToTakeOff() == permissionToTakeOff
    * @param permissionToTakeOff
    */
    void setPermissionToTakeOff(bool permissionToTakeOff);


    /**
    * reduces fuel accordingly to the plane type
    */
    void useFuel();
};


/// Airplane Subtypes

class AirplaneMilitairy : public Airplane {
public:

    AirplaneMilitairy();

    virtual bool validEngineType(const string &type);

    virtual bool validSize(const string &size);

    bool validRunway(Runway* runway = NULL);

};

class AirplanePrivate : public Airplane {
public:

    AirplanePrivate();

    virtual bool validEngineType(const string &type);

    virtual bool validSize(const string &size);

    bool validRunway(Runway* runway = NULL);
};

class AirplaneAirline : public Airplane {
public:

    AirplaneAirline();

    virtual bool validEngineType(const string &type);

    virtual bool validSize(const string &size);

    bool validRunway(Runway* runway = NULL);


};

class AirplaneEmergency : public Airplane {
public:

    AirplaneEmergency();

    virtual bool validEngineType(const string &type);

    virtual bool validSize(const string &size);

    bool validRunway(Runway* runway = NULL);

};

/**
* sets string gTime
 * Postconditions: getTime() == time
* @param time
*/
void setTime(const string& time);

/**
 * Returns string gTime
 * @return gTime
 */
const string &getTime();

/**
* sets string gTimePassed
 * Postconditions: getTimePassed() == time
* @param time
*/
void setTimePassed(int time);

/**
 * Returns string gTimePassed
 * @return gTimePassed
 */
int getTimePassed();

/**
* sets string gStartingTime
 * Postconditions: getStartingTime() == time
* @param time
*/
void setStartingTime(int time);

/**
 * Returns string gStartingTime
 * @return gStartingTime
 */
int getStartingTime();





#endif //PSE_V1_AirplaneCLASS_H
