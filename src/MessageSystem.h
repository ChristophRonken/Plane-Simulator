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

void initialCommunicationMessage(Airplane* Plane, Airport* Port, string time);

void waitBeforeDescendMessage(Airplane* Plane, string time);

void descendTo5000ftMessage(Airplane* Plane, string time);

void descendTo3000ftMessage(Airplane* Plane, string time);

void finalApproachMessage(Airplane* Plane, Runway* Runw, string time);

void afterLandingMessage(Airplane* Plane, Airport* Port, Runway* Runw, string time);

#endif //PSE_V1_MESSAGESYSTEM_H
