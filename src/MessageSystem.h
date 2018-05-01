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
 * @param airplane
 * @param airport
 * @param time
 */
void initialCommunicationMessage(Airplane* airplane, Airport* airport, const string &time);

/**
 * ATC tells airplane to descend to 5000ft
 * @param airplane
 * @param time
 */
void descendTo5000ftMessage(Airplane* airplane, const string &time);

/**
 * Airplane says it will start descending to 5000 ft
 * @param airplane
 * @param time
 */
void descendTo5000ftConfirmation(Airplane* airplane, const string &time);

/**
 * Tell the airplane to wait before descending
 * @param airplane
 * @param time
 */
void waitBeforeDescendMessage(Airplane* airplane, const string &time);

/**
 * Airplane confirms waiting message
 * @param airplane
 * @param time
 */
void waitBeforeDescendConfirmation(Airplane* airplane, const string &time);

/**
 * Tell the airplane descend to 3000ft
 * @param airplane
 * @param time
 */
void descendTo3000ftMessage(Airplane* airplane, const string &time);

/**
 * Airplane says it will start descending
 * @param airplane
 * @param time
 */
void descendTo3000ftConfirmation(Airplane* airplane, const string &time);

/**
 * Tell the airplane to start the final approach
 * @param airplane
 * @param runway
 * @param time
 */
void finalApproachMessage(Airplane* airplane, Runway* runway, const string &time);

/**
 * Airplane says it will start it's final approach
 * @param airplane
 * @param runway
 * @param time
 */
void finalApproachConfirmation(Airplane* airplane, Runway* runway, const string &time);

/**
 * Send message after the final approach
 * @param airplane
 * @param airport
 * @param runway
 * @param time
 */
void afterLandingMessage(Airplane* airplane, Airport* airport, Runway* runway, const string &time);

/*
 * Take off messages
 */

/**
 * Request IFR Permission to start departure procedure
 * @param airplane
 * @param time
 */
void IFRRequest(Airplane* airplane, const string &time);

/**
 * Accept IFR Request
 * @param airplane
 * @param time
 */
void IFRMessage(Airplane* airplane, const string &time);

/**
 * Confirm IFR's Accepting
 * @param airplane
 * @param time
 */
void IFRConfirmation(Airplane* airplane, const string &time);

// After IFR authorization
/**
 * Request pushback Message
 * @param airplane
 * @param time
 */
void pushbackRequest(Airplane* airplane, const string &time);

/**
 * Accept pushback request message
 * @param airplane
 * @param time
 */
void pushbackMessage(Airplane* airplane, const string &time);

/**
 * Confirm pushback acceptance
 * @param airplane
 * @param time
 */
void pushbackConfirmation(Airplane* airplane, const string &time);

/**
 * Send ready for taxi message
 * @param airplane
 * @param time
 */
void readyToTaxiMessage(Airplane* airplane, const string &time);


/**
 * airplane is holding short at runway message
 * @param airplane
 * @param runway
 * @param time
 */
void holdingShortAtRunway(Airplane* airplane, Runway* runway, const string &time);

/**
 * Tell the airplane to wait at the runway
 * @param airplane
 * @param time
 */
void waitAtRunwayMessage(Airplane* airplane, const string &time);

/**
 * airplane Says he heard the wait at runway message
 * @param airplane
 * @param time
 */
void waitAtRunwayConfirmation(Airplane* airplane, const string &time);

/**
 * Tell the airplane to line up on the runway
 * @param airplane
 * @param runway
 * @param time
 */
void lineUpRunwayMessage(Airplane* airplane, Runway* runway, const string &time);

/**
 * The airplane says it has heard the linup message
 * @param airplane
 * @param runway
 * @param time
 */
void lineUpRunwayConfirmation(Airplane* airplane, Runway* runway, const string &time);

/**
 * Tell the airplane it is cleared for take-off
 * @param airplane
 * @param runway
 * @param time
 */
void clearedForTakeOffMessage(Airplane* airplane, Runway* runway, const string &time);

/**
 * The airplane says it has heared the clearance message
 * @param airplane
 * @param runway
 * @param time
 */
void clearedForTakeOffConfirmation(Airplane* airplane, Runway* runway, const string &time);


/**
 * Tell the airplane to go to a holding point
 * @param airplane
 * @param taxiCrossing
 * @param taxiPoint
 * @param time
 */
void toHoldingPointMessage(Airplane* airplane, const string &taxiCrossing, const string &taxiPoint, const string &time);

/**
 * The airplane says it has heard the to holding point message
 * @param airplane
 * @param taxiCrossing
 * @param taxiPoint
 * @param time
 */
void toHoldingPointConfirmation(Airplane* airplane, const string &taxiCrossing, const string &taxiPoint, const string &time);

/**
 * Tell the airplane to go to the given runway
 * @param airplane
 * @param runway
 * @param taxiPoint
 * @param time
 */
void toRunwayMessage(Airplane* airplane, Runway* runway, const string &taxiPoint, const string &time);

/**
 * The airplane says it has heard th to runway message
 * @param airplane
 * @param runway
 * @param taxiPoint
 * @param time
 */
void toRunwayConfirmation(Airplane* airplane, Runway* runway, const string &taxiPoint, const string &time);

/**
 * Tell the airplane to go to the gate
 * @param airplane
 * @param gateIndex
 * @param taxiPoint
 * @param time
 */
void toGateMessage(Airplane* airplane, int gateIndex,  const string &taxiPoint, const string &time);

/**
 * The airplane says it has heard the to gate message
 * @param airplane
 * @param gateIndex
 * @param taxiPoint
 * @param time
 */
void toGateConfirmation(Airplane* airplane, int gateIndex,  const string &taxiPoint, const string &time);

/**
 * The airplane asks if it is cleared to cross the runway
 * @param airplane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossRequest(Airplane* airplane, const string &taxiCrossing, const string &time );

/**
 * Tell the airplane it is cleared to cross the runway
 * @param airplane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossMessage(Airplane* airplane, const string &taxiCrossing, const string &time );

/**
 * The airplane says it has heard the cleared to cross message
 * @param airplane
 * @param taxiCrossing
 * @param time
 */
void clearedToCrossConfirmation(const string &taxiCrossing, const string &time );


/**
 * Emergancy above 3000 ft, ask for help
 * @param airplane
 * @param airport
 * @param time
 */
void EmergencyAbove3000ftRequest(Airplane* airplane, Airport* airport, const string &time);

/**
 * Emergancy above 3000 ft, instructions
 * @param airplane
 * @param runway
 * @param time
 */
void EmergencyAbove3000ftMessage(Airplane* airplane, Runway* runway, const string &time);

/**
 * Emergancy below 3000 ft, ask for instructions
 * @param airplane
 * @param airport
 * @param time
 */
void EmergencyBelow3000ftRequest(Airplane* airplane, Airport* airport, const string &time);

/**
 * Emergancy bellow 3000 ft, instructions
 * @param airplane
 * @param time
 */
void EmergencyBelow3000ftMessage(Airplane* airplane, const string &time);


#endif //PSE_V1_MESSAGESYSTEM_H
