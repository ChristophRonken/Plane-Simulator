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

class Airplane;
class Runway;
class Airport;

using namespace std;

/**
 * Prints an action message in the console
 * @param s
 */
void actionMessage(string s);

/**
 * Prints a notification message
 * @param s
 */
void notificationMessage(string s);

/**
 * Prints an error message in the console
 * @param s
 */
void errorMessage(string s);

/**
 * Prints a succes messade in the console
 * @param s
 */
void succesMessage(string s);

/**
 * Prints a notification of an input in the console
 * @param s
 */
void inputMessage(string s);

/**
 * Converts Ints to strings
 * @param int i
 * @return string
 */
string intToString(int i);

/**
 * Returns the ofstream object containing all the text send to the Message functions
 * @return text
 */
ofstream* getText();

void closeFile();

/*
 * Landing messages
 */

// 10.000 ft
void initialCommunicationMessage(Airplane* Plane, Airport* Port, string time);

void descendTo5000ftMessage(Airplane* Plane, string time);

void descendTo5000ftConfirmation(Airplane* Plane, string time);

// Waiting pattern
void waitBeforeDescendMessage(Airplane* Plane, string time);

void waitBeforeDescendConfirmation(Airplane* Plane, string time);

// 5.000 ft
void descendTo3000ftMessage(Airplane* Plane, string time);

void descendTo3000ftConfirmation(Airplane* Plane, string time);

// 3.000 ft
void finalApproachMessage(Airplane* Plane, Runway* Runw, string time);

void finalApproachConfirmation(Airplane* Plane, Runway* Runw, string time);

// after landing
void afterLandingMessage(Airplane* Plane, Airport* Port, Runway* Runw, string time);

/*
 * Take off messages
 */

// At gate
void IFRRequest(Airplane* Plane, string time);

void IFRMessage(Airplane* Plane, string time);

void IFRConfirmation(Airplane* Plane, string time);

// After IFR authorization
void pushbackRequest(Airplane* Plane, string time);

void pushbackMessage(Airplane* Plane, string time);

void pushbackConfirmation(Airplane* Plane, string time);

// From gate
void readyToTaxiMessage(Airplane* Plane, string time);


// Waiting at Runway
void holdingShortAtRunway(Airplane* Plane, Runway* Runw, string time);

// Keep waiting at runway (first holdingShortAtRunway())
void waitAtRunwayMessage(Airplane* Plane, string time);

void waitAtRunwayConfirmation(Airplane* Plane, string time);

// Enter runway (first holdingShortAtRunway())
void lineUpRunwayMessage(Airplane* Plane, Runway* Runw, string time);

void lineUpRunwayConfirmation(Airplane* Plane, Runway* Runw, string time);

// take off (first holdingShortAtRunway())
void clearedForTakeOffMessage(Airplane* Plane, Runway* Runw, string time);

void clearedForTakeOffConfirmation(Airplane* Plane, Runway* Runw, string time);


// Taxiing
void toHoldingPointMessage(Airplane* Plane, Runway* Runw, string taxiPoint, string time);

void toHoldingPointConfirmation(Airplane* Plane, Runway* Runw, string taxiPoint, string time);

void toRunwayMessage(Airplane* Plane, Runway* Runw, string taxiPoint, string time);

void toRunwayConfirmation(Airplane* Plane, Runway* Runw, string taxiPoint, string time);

void toGateMessage(Airplane* Plane, int gateIndex,  string taxiPoint, string time);

void toGateConfirmation(Airplane* Plane, int gateIndex,  string taxiPoint, string time);

void clearedToCrossRequest(Airplane* Plane, Runway* Runw, string time );

void clearedToCrossMessage(Airplane* Plane, Runway* Runw, string time );

void clearedToCrossConfirmation(Airplane* Plane, Runway* Runw, string time );


// Emergency
void EmergencyAbove3000ftRequest(Airplane* Plane, string time);

void EmergencyAbove3000ftMessage(Airplane* Plane, Runway* Runw, string time);

void EmergencyBelow3000ftRequest(Airplane* Plane, string time);

void EmergencyBelow3000ftMessage(Airplane* Plane, string time);


#endif //PSE_V1_MESSAGESYSTEM_H
