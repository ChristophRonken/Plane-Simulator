//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_AirplaneCLASS_H
#define PSE_V1_AirplaneCLASS_H

#include <iostream>
#include <cmath>
#include <map>

#include "Airport.h"
#include "Runway.h"
#include "FlightPlan.h"
#include "TaxiRoute.h"
#include "DesignByContract.h"
#include "Utils.h"

using namespace std;

class Airport;
class Runway;

const int kPrivateSmallSquawk = 0001;
const int kPrivateMediumSquawk = 1000;
const int kAirlineMediumPropellerSquawk = 2000;
const int kAirlineMediumJetSquawk = 3000;
const int kAirlineLargeSquawk = 4000;
const int kMilitarySquawk  = 5000;
const int kEmegencySquawk =  6000;

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
    bool emergencySequenceInitiated;

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

    /**
     * Get if the plane has been checked
     * @return
     */
    bool getTechnicalChecked() const;

    /**
     * Set if the plane has been technically checked
     * Preconditions: propperlyInitialised()
     * @param boolean
     */
    void setTechnicalChecked(bool boolean);

    /**
     * get the ID number
     * @return
     */
    const string &getNumber() const;

    /**
     * Set ID number
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Get the engine of the airplane
     * @return engine
     */
    const string &getEngine() const;

    /**
     * Sets the engine of the airplan
     * Preconditions: propperlyInitialised()e
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * returns true if the plane is ready for departure
     * Preconditions: propperlyInitialised()
     * @return readyForDeparture
     */
    bool isReadyForDeparture() const;

    /**
     * lands the plane in the given airport
     * A runway is optional
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
     * Precondition: Airplane::atAirport() && validRunway() &&
     *      Airplane::getCurrentTask() == "IFR" || Airplane::getCurrentTask() == "pushback"
     *      || Airplane::getCurrentTask() == "request taxi" && Airplane::flightPlan != NULL
     */
    void pushBack();

    /**
     * send the plane to exit the airport
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
     * @param airport
     * @return bool
     */
    bool notFinished();

    /**
     * execute a task
     * Preconditions: propperlyInitialised()
     * @param airport
     */
    void execTask(Airport* airport);

    /**
     * Get the destination of this airplane
     * Preconditions: propperlyInitialised()
     * @return string
     */
    const string &getDestination();

    /**
     * Initialize the plane's variables to start a simulation
     * Preconditions: propperlyInitialised()
     * @param airport
     */
    void initSimulation(Airport *airport);

    /**
     * Check if the gate index is both valid and unoccupied
     * Preconditions: propperlyInitialised()
     * @param gate
     * @return bool
     */
    bool validGate(int gate = -1);

    /**
     * Check if this airplane can take off/land on the given Runway.
     * If no runway is given, it will see if a Runway exists with the same requirements
     * Preconditions: propperlyInitialised()
     * @param runway
     * @return bool
     */
    virtual bool validRunway(Runway* runway = NULL);

    /**
     * Check if the location to land is valid
     * Preconditions: propperlyInitialised()
     * @param airport
     * @param runway
     * @return bool
     */
    bool validLandingSpot(Airport* airport, Runway* runway = NULL );

    /**
     * Check if the airplane is at an airport
     * Preconditions: propperlyInitialised()
     * @return bool
     */
    bool atAirport();

    /**
     * Check if the airplane is at a gate
     * Preconditions: propperlyInitialised()
     * @return bool
     */
    bool atGate();

    /**
     * Check if the airplane is ready for take-off
     * Preconditions: propperlyInitialised()
     * @return bool
     */
    bool readyForTakeOff();

    /**
     * Set the squawk code of this plane
     * If none was given, it will generate an appropriate code
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
     * Postcondition: Airplane::getAttemptgate() == attemptgate
     * @param attemptgate
     */
    void setAttemptGate(int attemptgate);

    /**
     * Check if the airplane has permission to descend
     * Preconditions: propperlyInitialised()
     * @param height
     * @param airport
     * @param Runway
     * @return bool
     */
    bool permissionToDescend(int, Airport*, Runway*);

    /**
     * Make the airplane taxi to a (given) runway if possible
     * Preconditions: propperlyInitialised()
     * Preconditions: Airplane::getCurrentTask() == "going to runway" &&
     *      (Airplane::getAttemptRunway() != NULL
     */
    void taxiToRunway();

    /**
     * Make the airplane taxi to a given gate
     * Preconditions: propperlyInitialised()
     * @param gate
     */
    void taxiToGate(int gate = -1);

    /**
     * Perform an emergency landing
     * Preconditions: propperlyInitialised()
     * @param airport
     */
    void emergencyLanding(Airport*);

    /**
     * Check if the input value would be a valid engine type for the airplane.
     * Preconditions: propperlyInitialised()
     * @param engine
     * @return bool
     */
    virtual bool validEngineType(const string &type);

    /**
     * check if the input value would be a valid size for the airplane
     * Preconditions: propperlyInitialised()
     * @param size
     * @return bool
     */
    virtual bool validSize(const string &size);

    /**
     * Let passengers exit the plane
     * Preconditions: propperlyInitialised()
     */
    void exitPlane();

    /**
     * Let passengers enter the plane
     * Preconditions: propperlyInitialised()
     */
    void enterPlane();

    /**
     * Perform a technical Check on the airplane
     * Preconditions: propperlyInitialised()
     */
    void technicalCheck();

    /**
     * Refuel the airplane
     * Preconditions: propperlyInitialised()
     */
    void refuel();


    /**
     * Check if the plane was properly initialized
     * Preconditions: propperlyInitialised()
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
     * Preconditions: propperlyInitialised()
     * @return bool
     */
    bool getSimulationFinished();

   /**
    * Set if the simulation was finished
    * Preconditions: propperlyInitialised()
    * Postcondition: Airplane::getsimulationFinished() == finished
    * @param finished
    */
    void setSimulationFinished(bool finished);

    /**
     * Get the current task the plane is performing
     * Preconditions: propperlyInitialised()
     * @return string
     */
    const string &getCurrentTask() const;

    /**
     * Set the current task the plane is performing
     * Preconditions: propperlyInitialised()
     * Postconditions: Airplane::getCurrentTask() == currentTask
     * @param currentTask
     */
    void setCurrentTask(const string &currentTask);

    /**
     * Preform tasks that happen over a longer period
     * Preconditions: propperlyInitialised()
     */
    void continueTask(Airport * airport);

    /**
     * Descend X ft
     * Preconditions: propperlyInitialised()
     */
    void descend(Airport * airport);

    /**
     * Ascend X ft
     * Preconditions: propperlyInitialised()
     */
    void ascend(Airport * airport);

    /**
     * Returns boolean isWaitAtRunway
     * Preconditions: propperlyInitialised()
     * @return isWaitAtRunway
     */
    bool isWaitAtRunway() const;

    /**
    * sets bool waitAtRunway
     * Preconditions: propperlyInitialised()
    * Postconditions: Airplane::isWaitAtRunway() == waitAtRunway
    * @param waitAtRunway
    */
    void setWaitAtRunway(bool waitAtRunway);

    /**
     * Returns boolean isWaitOnRunway
     * Preconditions: propperlyInitialised()
     * @return isWaitOnRunway
     */
    bool isWaitOnRunway() const;

    /**
    * sets bool waitOnRunway
     * Preconditions: propperlyInitialised()
    * Postconditions: Airplane::isWaitOnRunway() == waitOnRunway
    * @param waitOnRunway
    */
    void setWaitOnRunway(bool waitOnRunway);

    /**
     * Returns boolean alreadyLinedUp
     * Preconditions: propperlyInitialised()
     * @return alreadyLinedUp
     */
    bool isAlreadyLinedUp() const;

    /**
    * sets bool alreadyLinedUp
     * Preconditions: propperlyInitialised()
    * Postconditions: Airplane::isAlreadyLinedUp() == alreadyLinedUp
    * @param alreadyLinedUp
    */
    void setAlreadyLinedUp(bool alreadyLinedUp);

    /**
     * Returns boolean isPermissionToTakeOff
     * Preconditions: propperlyInitialised()
     * @return isPermissionToTakeOff
     */
    bool isPermissionToTakeOff() const;

    /**
    * sets bool permissionToTakeOff
     * Preconditions: propperlyInitialised()
     * Postconditions: Airplane::isPermissionToTakeOff() == permissionToTakeOff
    * @param permissionToTakeOff
    */
    void setPermissionToTakeOff(bool permissionToTakeOff);

    /**
    * reduces fuel accordingly to the plane type
    * Preconditions: propperlyInitialised()
    */
    void useFuel();

    /**
    * Returns boolean emergencySequenceInitiated
    * @return emergencySequenceInitiated
    */
    bool isEmergencySequenceInitiated() const;

    /**
    * sets bool emergencySequenceInitiated
     * Postconditions: Airplane::isEmergencySequenceInitiated() == emergencySequenceInitiated
    * @param emergencySequenceInitiated
    */
    void setEmergencySequenceInitiated(bool emergencySequenceInitiated);
};


/// Airplane Subtype

class AirplaneMilitairy : public Airplane {
public:

    AirplaneMilitairy();

    virtual bool validEngineType(const string &type);

    virtual bool validSize(const string &size);

    bool validRunway(Runway* runway = NULL);

};

/// Airplane Subtype

class AirplanePrivate : public Airplane {
public:

    AirplanePrivate();

    virtual bool validEngineType(const string &type);

    virtual bool validSize(const string &size);

    bool validRunway(Runway* runway = NULL);
};

/// Airplane Subtype

class AirplaneAirline : public Airplane {
public:

    AirplaneAirline();

    virtual bool validEngineType(const string &type);

    virtual bool validSize(const string &size);

    bool validRunway(Runway* runway = NULL);


};

/// Airplane Subtype

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
