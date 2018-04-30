//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_MESSAGESYSTEM_H
#define PSE_V1_MESSAGESYSTEM_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include "AirplaneClass.h"
#include "AirportClass.h"
#include "RunwayClass.h"
#include "DesignByContract.h"
#include "Utils.h"

class Airplane;
class Runway;
class Airport;

using namespace std;

/**
 * Print a message in the logFile
 * @param str
 */
void logMessage(string str);

/**
 * Returns the ofstream object containing all the text send to and from the ATC
 * @return ofstream
 */

ofstream* getCommunicationLogFile();

/**
 * Returns the ofstream object containing all text send to the logfile
 * @return ofstream
 */
ofstream* getLogFile();

/**
 * Opens and returns a new Logfile
 * @param name
 * @return ofstream
 */
ofstream* openNewLogFile(string name);

/**
 * Opens and returns a new ATC communication logfile
 * @param name
 * @return ofstream
 */
ofstream* openNewCommunicationLogFile(string name);

/**
 * Closes the current logfile
 */
void closeLogFile();

/**
 * Closes the current communication logfile
 */
void closeCommunicationLogFile();

/*
 * Landing messages
 */

/**
 * Initial communication message
 * @param Plane
 * @param Port
 * @param time
 */
void initialCommunicationMessage(Airplane* Plane, Airport* Port, string time);

/**
 * ATC tells airplane to descend to 5000ft
 * @param Plane
 * @param time
 */
void descendTo5000ftMessage(Airplane* Plane, string time);

/**
 * Airplane says it will start descending to 5000 ft
 * @param Plane
 * @param time
 */
void descendTo5000ftConfirmation(Airplane* Plane, string time);

/**
 * Tell the plane to wait before descending
 * @param Plane
 * @param time
 */
void waitBeforeDescendMessage(Airplane* Plane, string time);

/**
 * Airplane confirms waiting message
 * @param Plane
 * @param time
 */
void waitBeforeDescendConfirmation(Airplane* Plane, string time);

/**
 * Tell the plane descend to 3000ft
 * @param Plane
 * @param time
 */
void descendTo3000ftMessage(Airplane* Plane, string time);

/**
 * Airplane says it will start descending
 * @param Plane
 * @param time
 */
void descendTo3000ftConfirmation(Airplane* Plane, string time);

/**
 * Tell the airplane to start the final approach
 * @param Plane
 * @param Runw
 * @param time
 */
void finalApproachMessage(Airplane* Plane, Runway* Runw, string time);

/**
 * Airplane says it will start it's final approach
 * @param Plane
 * @param Runw
 * @param time
 */
void finalApproachConfirmation(Airplane* Plane, Runway* Runw, string time);

/**
 * Send message after the final approach
 * @param Plane
 * @param Port
 * @param Runw
 * @param time
 */
void afterLandingMessage(Airplane* Plane, Airport* Port, Runway* Runw, string time);

/*
 * Take off messages
 */

/**
 * Request IFR Permission to start departure procedure
 * @param Plane
 * @param time
 */
void IFRRequest(Airplane* Plane, string time);

/**
 * Accept IFR Request
 * @param Plane
 * @param time
 */
void IFRMessage(Airplane* Plane, string time);

/**
 * Confirm IFR's Accepting
 * @param Plane
 * @param time
 */
void IFRConfirmation(Airplane* Plane, string time);

// After IFR authorization
/**
 * Request pushback Message
 * @param Plane
 * @param time
 */
void pushbackRequest(Airplane* Plane, string time);

/**
 * Accept pushback request message
 * @param Plane
 * @param time
 */
void pushbackMessage(Airplane* Plane, string time);

/**
 * Confirm pushback acceptance
 * @param Plane
 * @param time
 */
void pushbackConfirmation(Airplane* Plane, string time);

/**
 * Send ready for taxi message
 * @param Plane
 * @param time
 */
void readyToTaxiMessage(Airplane* Plane, string time);


/**
 * Plane is holding short at runway message
 * @param Plane
 * @param Runw
 * @param time
 */
void holdingShortAtRunway(Airplane* Plane, Runway* Runw, string time);

/**
 * Tell the plane to wait at the runway
 * @param Plane
 * @param time
 */
void waitAtRunwayMessage(Airplane* Plane, string time);

/**
 * Plane Says he heard the wait at runway message
 * @param Plane
 * @param time
 */
void waitAtRunwayConfirmation(Airplane* Plane, string time);

/**
 * Tell the plane to line up on the runway
 * @param Plane
 * @param Runw
 * @param time
 */
void lineUpRunwayMessage(Airplane* Plane, Runway* Runw, string time);

/**
 * The plane says it has heard the linup message
 * @param Plane
 * @param Runw
 * @param time
 */
void lineUpRunwayConfirmation(Airplane* Plane, Runway* Runw, string time);

/**
 * Tell the plane it is cleared for take-off
 * @param Plane
 * @param Runw
 * @param time
 */
void clearedForTakeOffMessage(Airplane* Plane, Runway* Runw, string time);

/**
 * The plane says it has heared the clearance message
 * @param Plane
 * @param Runw
 * @param time
 */
void clearedForTakeOffConfirmation(Airplane* Plane, Runway* Runw, string time);


/**
 * Tell the plane to go to a holding point
 * @param Plane
 * @param taxiCrossing
 * @param taxiPoint
 * @param time
 */
void toHoldingPointMessage(Airplane* Plane, string taxiCrossing, string taxiPoint, string time);

/**
 * The plane says it has heard the to holding point message
 * @param Plane
 * @param taxiCrossing
 * @param taxiPoint
 * @param time
 */
void toHoldingPointConfirmation(Airplane* Plane, string taxiCrossing, string taxiPoint, string time);

/**
 * Tell the plane to go to the given runway
 * @param Plane
 * @param Runw
 * @param taxiPoint
 * @param time
 */
void toRunwayMessage(Airplane* Plane, Runway* Runw, string taxiPoint, string time);

/**
 * The plane says it has heard th to runway message
 * @param Plane
 * @param Runw
 * @param taxiPoint
 * @param time
 */
void toRunwayConfirmation(Airplane* Plane, Runway* Runw, string taxiPoint, string time);

/**
 * Tell the plane to go to the gate
 * @param Plane
 * @param gateIndex
 * @param taxiPoint
 * @param time
 */
void toGateMessage(Airplane* Plane, int gateIndex,  string taxiPoint, string time);

/**
 * The plane says it has heard the to gate message
 * @param Plane
 * @param gateIndex
 * @param taxiPoint
 * @param time
 */
void toGateConfirmation(Airplane* Plane, int gateIndex,  string taxiPoint, string time);

/**
 * The plane asks if it is cleared to cross the runway
 * @param Plane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossRequest(Airplane* Plane, string taxiCrossing, string time );

/**
 * Tell the plane it is cleared to cross the runway
 * @param Plane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossMessage(Airplane* Plane, string taxiCrossing, string time );

/**
 * The plane says it has heard the cleared to cross message
 * @param Plane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossConfirmation(Airplane* Plane, string taxiCrossing, string time );


/**
 * Emergancy above 3000 ft, ask for help
 * @param Plane
 * @param Port
 * @param time
 */
void EmergencyAbove3000ftRequest(Airplane* Plane, Airport* Port, string time);

/**
 * Emergancy above 3000 ft, instructions
 * @param Plane
 * @param Runw
 * @param time
 */
void EmergencyAbove3000ftMessage(Airplane* Plane, Runway* Runw, string time);

/**
 * Emergancy below 3000 ft, ask for instructions
 * @param Plane
 * @param Port
 * @param time
 */
void EmergencyBelow3000ftRequest(Airplane* Plane, Airport* Port, string time);

/**
 * Emergancy bellow 3000 ft, instructions
 * @param Plane
 * @param time
 */
void EmergencyBelow3000ftMessage(Airplane* Plane, string time);


#endif //PSE_V1_MESSAGESYSTEM_H
