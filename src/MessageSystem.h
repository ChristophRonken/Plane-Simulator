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
void logMessage(const string &str);

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
ofstream* openNewLogFile(const string &name);

/**
 * Opens and returns a new ATC communication logfile
 * @param name
 * @return ofstream
 */
ofstream* openNewCommunicationLogFile(const string &name);

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
 * @param plane
 * @param airport
 * @param time
 */
void initialCommunicationMessage(Airplane* plane, Airport* airport, const string &time);

/**
 * ATC tells airplane to descend to 5000ft
 * @param plane
 * @param time
 */
void descendTo5000ftMessage(Airplane* plane, const string &time);

/**
 * Airplane says it will start descending to 5000 ft
 * @param plane
 * @param time
 */
void descendTo5000ftConfirmation(Airplane* plane, const string &time);

/**
 * Tell the plane to wait before descending
 * @param plane
 * @param time
 */
void waitBeforeDescendMessage(Airplane* plane, const string &time);

/**
 * Airplane confirms waiting message
 * @param plane
 * @param time
 */
void waitBeforeDescendConfirmation(Airplane* plane, const string &time);

/**
 * Tell the plane descend to 3000ft
 * @param plane
 * @param time
 */
void descendTo3000ftMessage(Airplane* plane, const string &time);

/**
 * Airplane says it will start descending
 * @param plane
 * @param time
 */
void descendTo3000ftConfirmation(Airplane* plane, const string &time);

/**
 * Tell the airplane to start the final approach
 * @param plane
 * @param runway
 * @param time
 */
void finalApproachMessage(Airplane* plane, Runway* runway, const string &time);

/**
 * Airplane says it will start it's final approach
 * @param plane
 * @param runway
 * @param time
 */
void finalApproachConfirmation(Airplane* plane, Runway* runway, const string &time);

/**
 * Send message after the final approach
 * @param plane
 * @param airport
 * @param runway
 * @param time
 */
void afterLandingMessage(Airplane* plane, Airport* airport, Runway* runway, const string &time);

/*
 * Take off messages
 */

/**
 * Request IFR Permission to start departure procedure
 * @param plane
 * @param time
 */
void IFRRequest(Airplane* plane, const string &time);

/**
 * Accept IFR Request
 * @param plane
 * @param time
 */
void IFRMessage(Airplane* plane, const string &time);

/**
 * Confirm IFR's Accepting
 * @param plane
 * @param time
 */
void IFRConfirmation(Airplane* plane, const string &time);

// After IFR authorization
/**
 * Request pushback Message
 * @param plane
 * @param time
 */
void pushbackRequest(Airplane* plane, const string &time);

/**
 * Accept pushback request message
 * @param plane
 * @param time
 */
void pushbackMessage(Airplane* plane, const string &time);

/**
 * Confirm pushback acceptance
 * @param plane
 * @param time
 */
void pushbackConfirmation(Airplane* plane, const string &time);

/**
 * Send ready for taxi message
 * @param plane
 * @param time
 */
void readyToTaxiMessage(Airplane* plane, const string &time);


/**
 * plane is holding short at runway message
 * @param plane
 * @param runway
 * @param time
 */
void holdingShortAtRunway(Airplane* plane, Runway* runway, const string &time);

/**
 * Tell the plane to wait at the runway
 * @param plane
 * @param time
 */
void waitAtRunwayMessage(Airplane* plane, const string &time);

/**
 * plane Says he heard the wait at runway message
 * @param plane
 * @param time
 */
void waitAtRunwayConfirmation(Airplane* plane, const string &time);

/**
 * Tell the plane to line up on the runway
 * @param plane
 * @param runway
 * @param time
 */
void lineUpRunwayMessage(Airplane* plane, Runway* runway, const string &time);

/**
 * The plane says it has heard the linup message
 * @param plane
 * @param runway
 * @param time
 */
void lineUpRunwayConfirmation(Airplane* plane, Runway* runway, const string &time);

/**
 * Tell the plane it is cleared for take-off
 * @param plane
 * @param runway
 * @param time
 */
void clearedForTakeOffMessage(Airplane* plane, Runway* runway, const string &time);

/**
 * The plane says it has heared the clearance message
 * @param plane
 * @param runway
 * @param time
 */
void clearedForTakeOffConfirmation(Airplane* plane, Runway* runway, const string &time);


/**
 * Tell the plane to go to a holding point
 * @param plane
 * @param taxiCrossing
 * @param taxiPoint
 * @param time
 */
void toHoldingPointMessage(Airplane* plane, const string &taxiCrossing, const string &taxiPoint, const string &time);

/**
 * The plane says it has heard the to holding point message
 * @param plane
 * @param taxiCrossing
 * @param taxiPoint
 * @param time
 */
void toHoldingPointConfirmation(Airplane* plane, const string &taxiCrossing, const string &taxiPoint, const string &time);

/**
 * Tell the plane to go to the given runway
 * @param plane
 * @param runway
 * @param taxiPoint
 * @param time
 */
void toRunwayMessage(Airplane* plane, Runway* runway, const string &taxiPoint, const string &time);

/**
 * The plane says it has heard th to runway message
 * @param plane
 * @param runway
 * @param taxiPoint
 * @param time
 */
void toRunwayConfirmation(Airplane* plane, Runway* runway, const string &taxiPoint, const string &time);

/**
 * Tell the plane to go to the gate
 * @param plane
 * @param gateIndex
 * @param taxiPoint
 * @param time
 */
void toGateMessage(Airplane* plane, int gateIndex,  const string &taxiPoint, const string &time);

/**
 * The plane says it has heard the to gate message
 * @param plane
 * @param gateIndex
 * @param taxiPoint
 * @param time
 */
void toGateConfirmation(Airplane* plane, int gateIndex,  const string &taxiPoint, const string &time);

/**
 * The plane asks if it is cleared to cross the runway
 * @param plane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossRequest(Airplane* plane, const string &taxiCrossing, const string &time );

/**
 * Tell the plane it is cleared to cross the runway
 * @param plane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossMessage(Airplane* plane, const string &taxiCrossing, const string &time );

/**
 * The plane says it has heard the cleared to cross message
 * @param plane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossConfirmation(const string &taxiCrossing, const string &time );


/**
 * Emergancy above 3000 ft, ask for help
 * @param plane
 * @param airport
 * @param time
 */
void EmergencyAbove3000ftRequest(Airplane* plane, Airport* airport, const string &time);

/**
 * Emergancy above 3000 ft, instructions
 * @param plane
 * @param runway
 * @param time
 */
void EmergencyAbove3000ftMessage(Airplane* plane, Runway* runway, const string &time);

/**
 * Emergancy below 3000 ft, ask for instructions
 * @param plane
 * @param airport
 * @param time
 */
void EmergencyBelow3000ftRequest(Airplane* plane, Airport* airport, const string &time);

/**
 * Emergancy bellow 3000 ft, instructions
 * @param plane
 * @param time
 */
void EmergencyBelow3000ftMessage(Airplane* plane, const string &time);


#endif //PSE_V1_MESSAGESYSTEM_H
