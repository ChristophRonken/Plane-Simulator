//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_AirplaneCLASS_H
#define PSE_V1_AirplaneCLASS_H

#include <iostream>
#include <cmath>
#include <map>

#include "AirportClass.h"
#include "RunwayClass.h"
#include "FlightPlan.h"
#include "TaxiRoute.h"
#include "DesignByContract.h"

using namespace std;

class Airport;
class Runway;

enum ESqauwkCode {privateSmallSquawk, privateMediumSquawk, airlineMediumPropellerSquawk, airlineMediumJetSquawk,
                    airlineLargeSquawk, militarySquawk, emegencySquawk};

const int kSmall = 1;
const int kMedium = 2;
const int kLarge = 3;

const int kRunwayLengthA = 500;
const int kRunwayLengthB = 1000;
const int kRunwayLengthC = 1500;
const int kRunwayLengthD = 2000;

class Airplane {

    Airplane* self;

    string number;
    string callsign;
    string model;
    string state;
    string type;
    string engine;
    string size;
    string squawkCode;

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

    string currentTask;

    FlightPlan* flightPlan;
    TaxiRoute* taxiRoute;
    string taxiPoint;
    string taxiCrossing;

    bool technicalChecked;

    bool ifrAuthorized;
    bool pushback;

    bool requestMessageSend;
    bool messageMessageSend;
    bool confirmMessageSend;

    bool taxiRequest;

    bool emergencyInAirport;
    bool crossed;

    bool alreadyLinedUp;
    bool permissionToTakeOff;

    bool waitAtRunway;
    bool waitOnRunway;

    bool onItsWay;
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

public:

    Airplane();

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
    const string &getState() const;

    /**
     * sets the state of the plane
     * Postcondition: Airplane::getState() == state
     * @param state
     */
    void setState(const string &state);

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
     * Preconditions: validGate(gate)
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
     * set the variables of the plane
     * @param type of the given variable
     * @param value of the variable
     */
    void setVar(const string &type, const string &value);

    /**
     * prints the info of the plane in the console
     */
    void printInfo();

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
     * Precondition: this->validLandingSpot(Airport*, Runway* )
     * @param airport
     * @param R
     */
    void land(Airport* airport , Runway* R = NULL);

    /**
     * sends the plane to the given runway
     * if no runway was given, it will choose the first free runway
     * Precondition: this->atAirport() && validRunway(Runway* ) &&
     *      Airplane::getCurrentTask() == "IFR" || Airplane::getCurrentTask() == "pushback"
     *      || Airplane::getCurrentTask() == "request taxi"
     * @param runway
     */
    void pushBack(Runway* runway = NULL);

    /**
     * send the plane to gate x
     * if no gate index is given, the first free gate is chosen
     * Precondition: this->validGate() && this->atAirport()
     * @param gate
     */
    void toGate(int gate = -1);

    /**
     * send the plane to exit the airport
     * Precondition: this->readyForTakeOff()
     */
    void takeOff();

    /**
     * Check if the plane finished all it's tasks
     * @param airport
     * @return bool
     */
    bool notFinished(Airport* airport);

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
     * Check if the string type would be a valid airplane type
     * @param type
     * @return bool
     */
    bool validPlaneType(const string &type);

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
    bool validRunway(Runway* runway = NULL);

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
    const string &getSquawkCode() const;

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
     * Check if the IFR authorized the plane to initialize the departure procedure 
     * @return bool
     */
    bool isIFRAuthorized() const;

    /**
     * Set if the IFR authorized the plane to initialize the departure procedure
     * Postconditions: Airplane::isIFRAuthorized() == ifrAuthorized
     * @param ifrAuthorized
     */
    void setIFRAuthorized(bool ifrAuthorized);

    /**
     * Checl if pushback from gate is allowed
     * @return bool
     */
    bool isPushback() const;

    /**
     * Set if pushnack from gate is allowed
     * Postconditions: Airplane::isPushback() == pushback
     * @param pushback 
     */
    void setPushback(bool pushback);

    /**
     * Check if a request message is send for the next task
     * @return bool
     */
    bool isRequestMessageSend() const;

    /**
     * Set if a request message was send for the upcoming task
     * Postconditions: Airplane::isRequestMessageSend() == requestMessageSend
     * @param requestMessageSend
     */
    void setRequestMessageSend(bool requestMessageSend);

    /**
     * Check if the ATC send the airplane an instruction message for the upcoming task
     * @return bool
     */
    bool isMessageMessageSend() const;

    /**
     * Set if the ATC send the airplane an instruction message for the upcoming task
     * Postconditions: Airplane::isMessageMessageSend() == messageMessageSend
     * @param messageMessageSend
     */
    void setMessageMessageSend(bool messageMessageSend);

    /**
     * Check if the airplane send a confirmation message notifying the ATC it will perform it's instructions
     * @return bool
     */
    bool isConfirmMessageSend() const;

    /**
     * Set if the airplane send a confirmation message notifying the ATC it will perform it's instructions
     * Postconditions: Airplane::isConfirmMessageSend() == confirmMessageSend
     * @param confirmMessageSend
     */
    void setConfirmMessageSend(bool confirmMessageSend);

    /**
     * Geen idee waar deze voor is
     * @return bool
     */
    bool getEmergencyInAirport() const;

    /**
     * zie hierboven
     * Postconditions: Airplane::getEmergencyInAirport() == emergencyInAirport
     * @param emergencyInAirport
     */
    void setEmergencyInAirport(bool emergencyInAirport);

    /**
     * Check if the current task is a waiting for taxi instructions
     * @return
     */
    bool isTaxiRequest() const;

    /**
     * Set if the current task is waiting for taxi instructions
     * Postconditions: Airplane::isTaxiRequest() == taxiRequest
     * @param taxiRequest
     */
    void setTaxiRequest(bool taxiRequest);

    /**
     * Get the gate index the plane is trying to go to
     * @return int
     */
    int getAttemptgate() const;

    /**
     * Set the gate index the plane is trying to go to
     * Postcondition: Airplane::getAttemptgate() == attemptgate
     * @param attemptgate
     */
    void setAttemptgate(int attemptgate);

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
     * (Airplane::getRunway() != NULL || Airplane::getAttemptRunway() != NULL)
     */
    void taxiToRunway(Runway* runway = NULL);

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
    bool validEngineType(const string &engine);

    /**
     * check if the input value would be a valid size for the airplane
     * @param size
     * @return bool
     */
    bool validSize(const string &size);

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

    bool isOnItsWay() const;

    void setOnItsWay(bool onItsWay);
};

void setTime(const string& time);
const string &getTime();

void setTimePassed(int time);
int getTimePassed();

void setStartingTime(int time);
int getStartingTime();





#endif //PSE_V1_AirplaneCLASS_H
