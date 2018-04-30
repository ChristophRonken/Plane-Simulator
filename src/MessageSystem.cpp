// author: Ronken Christoph & Van Hautte Olivier
// date: 02/05/2018
// version: 2.0

#include "MessageSystem.h"

ofstream gOutputCommunicationLog("CommunicationLog.txt");
ofstream gOutputLog("Log.txt");

ofstream* getCommunicationLogFile(){
    return &gOutputCommunicationLog;
}
ofstream* getLogFile(){
    return &gOutputCommunicationLog;
}
ofstream* openNewLogFile(const string &name){
    gOutputLog.open(name.c_str());
    return &gOutputLog;
}
ofstream* openNewCommunicationLogFile(const string &name){
    gOutputCommunicationLog.open(name.c_str());
    return &gOutputCommunicationLog;
}

void closeLogFile(){
    gOutputLog.close();
}
void closeCommunicationLogFile(){
    gOutputCommunicationLog.close();
}


// Default Log Messaging
void logMessage(const string &str){
    gOutputLog << str << endl;
}


//Landing messages
void initialCommunicationMessage(Airplane* plane, Airport* airport, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airport->getCallsign() << ", " << plane->getCallsign() << ", arriving at " << airport->getName() << ".\n";
}

void descendTo5000ftMessage(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$" << plane->getCallsign() << ", radar contact, descend and maintain five thousand feet, squawk " << plane->getSquawkCode() << ".\n";
}
void descendTo5000ftConfirmation(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Descend and maintain five thousand feet, squawking " << plane->getSquawkCode() << ", " << plane->getCallsign() << ".\n";
}

void waitBeforeDescendMessage(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", hold south on the one eighty radial, expect further clearance at " << time << ".\n";
}
void waitBeforeDescendConfirmation(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Holding south on the one eighty radial, " << plane->getCallsign() << ".\n";
}

void descendTo3000ftMessage(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$" << plane->getCallsign() << ", radar contact, descend and maintain three thousand feet.\n";
}
void descendTo3000ftConfirmation(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Descend and maintain five thousand feet, " << plane->getCallsign() << ".\n";
}

void finalApproachMessage(Airplane* plane, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$" << plane->getCallsign() << ", cleared ILS approach runway" << runway->getName() << ".\n";
}
void finalApproachConfirmation(Airplane* plane, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Cleared ILS approach runway " << runway->getName() << ", " << plane->getCallsign() << ".\n";
}

void afterLandingMessage(Airplane* plane, Airport* airport, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airport->getCallsign() << ", " << plane->getCallsign() << ", runway " << runway->getName() << "vacated.\n";
}


//Take off messages
void IFRRequest(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << plane->getAirport()->getCallsign() << ", " << plane->getCallsign() << ", requesting IFR clearancy to " << plane->getDestination() << ".\n";
}
void IFRMessage(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", " << plane->getAirport()->getCallsign() << ", cleared to " << plane->getDestination() << ", maintain five thousand, "
                    "expect flight level one zero zero - ten minutes after departure, squawk " << plane->getSquawkCode() << ".\n";
}
void IFRConfirmation(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "Cleared to " << plane->getDestination() << ", initial altitude five thousand, expecting one zero zero in ten, squawking "
                 << plane->getSquawkCode() << ", " << plane->getCallsign() << ".\n";
}

void pushbackRequest(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << plane->getAirport()->getCallsign() << ", " << plane->getCallsign() << " at gate " << plane->getGate() << ", requesting pushback.\n";
}
void pushbackMessage(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", " << plane->getAirport()->getCallsign() << ", pushback approved.\n";
}
void pushbackConfirmation(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Pushback approved, " << plane->getCallsign() << ".\n";
}

void readyToTaxiMessage(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << plane->getCallsign() << " is ready to taxi.\n";
}

void holdingShortAtRunway(Airplane* plane, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << plane->getAirport()->getCallsign() << ", " << plane->getCallsign() << ", holding short at " << runway->getName() << ".\n";
}

void waitAtRunwayMessage(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", hold position.\n";
}
void waitAtRunwayConfirmation(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Holding position, " << plane->getCallsign() << ".\n";
}

void lineUpRunwayMessage(Airplane* plane, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", line-up runway " << runway->getName() << " and wait.\n";
}
void lineUpRunwayConfirmation(Airplane* plane, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Lining up runway " << runway->getName() << " and wait" << plane->getCallsign();
}

void clearedForTakeOffMessage(Airplane* plane, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", runway " << runway->getName() << " cleared for take-off.\n";
}
void clearedForTakeOffConfirmation(Airplane* plane, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Runway " << runway->getName() << "cleared for take-off, " << plane->getCallsign() << ".\n";
}


//Taxiing
void toHoldingPointMessage(Airplane* plane, const string &taxiCrossing, const string &taxiPoint, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", taxi to holding point " << taxiCrossing  << " via " << taxiPoint << ".\n";
}
void toHoldingPointConfirmation(Airplane* plane, const string &taxiCrossing, const string &taxiPoint, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Taxi to holding point " << taxiCrossing << " via " << taxiPoint << ", " << plane->getCallsign() << ".\n";
}

void toRunwayMessage(Airplane* plane, Runway* runway, const string &taxiPoint, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", taxi to runway " << runway->getName() << " via " << taxiPoint << ".\n";
}
void toRunwayConfirmation(Airplane* plane, Runway* runway, const string &taxiPoint, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Taxi to runway " << runway->getName() << " via " << taxiPoint << ", " << plane->getCallsign() << ".\n";
}

void toGateMessage(Airplane* plane, const int &gateIndex,  const string &taxiPoint, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", taxi to gate " << gateIndex << " via " << taxiPoint << ".\n";
}
void toGateConfirmation(Airplane* plane, const int &gateIndex,  const string &taxiPoint, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Taxi to gate " << gateIndex << " via " << taxiPoint << ", " << plane->getCallsign() << ".\n";
}

void clearedToCrossRequest(Airplane* plane, const string &taxiCrossing, const string &time ){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << plane->getAirport()->getCallsign() << ", " << plane->getCallsign() << ", holding short at  " << taxiCrossing << ".\n";
}
void clearedToCrossMessage(Airplane* plane, const string &taxiCrossing, const string &time ){
    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << plane->getCallsign() << ", cleared to cross " << taxiCrossing << ".\n";
}
void clearedToCrossConfirmation(Airplane* plane, const string &taxiCrossing, const string &time ){
    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Cleared to cross runway " << taxiCrossing << ".\n" ;
}


//Emergency
void EmergencyAbove3000ftRequest(Airplane* plane, Airport* airport, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]"
                 << "$ Mayday, mayday, mayday, " << airport->getCallsign() << ", " << plane->getCallsign() << ", out of fuel, request immidiate landing, "
                 << plane->getPassengers() << " passengers on board.\n";
}
void EmergencyAbove3000ftMessage(Airplane* plane, Runway* runway, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]"
                 << "$ " << plane->getCallsign() << ", roger mayday, squawk seven seven zero zero, cleared ILS landing runway " << runway->getName() << ".\n";
}
void EmergencyBelow3000ftRequest(Airplane* plane, Airport* airport, const string &time){
    gOutputCommunicationLog << "[" << time << "][AIR]"
                 << "$ Mayday, mayday, mayday, " << airport->getCallsign() << ", " << plane->getCallsign() << ", out of fuel, performing emergency landing, "
                 << plane->getPassengers() << " passengers on board.\n";
}
void EmergencyBelow3000ftMessage(Airplane* plane, const string &time){
    gOutputCommunicationLog << "[" << time << "][ATC]"
                 << "$ " << plane->getCallsign() << ", roger mayday, squawk seven seven zero zero, emergency personal on standby, good luck!\n";
}







