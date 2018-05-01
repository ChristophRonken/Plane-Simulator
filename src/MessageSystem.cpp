//
// Created by oliviervh on 01.03.18.
//



#include "MessageSystem.h"

std::ofstream gOutputCommunicationLog("CommunicationLog.txt");
std::ofstream gOutputLog("Log.txt");


ofstream * getCommunicationLogFile(){

    return &gOutputCommunicationLog;
};

ofstream * getLogFile(){

    return &gOutputCommunicationLog;
};

ofstream* openNewLogFile(const string &name){
    gOutputLog.open(name.c_str());
    return &gOutputLog;

};

ofstream* openNewCommunicationLogFile(const string &name){

    gOutputCommunicationLog.open(name.c_str());
    return &gOutputCommunicationLog;

};

void closeLogFile(){

    gOutputLog.close();

};

void closeCommunicationLogFile(){

    gOutputCommunicationLog.close();

};


// Default Log Messaging
void logMessage(const string &str){
    gOutputLog << str << endl;

};



//Landing messages
void initialCommunicationMessage(Airplane* airplane, Airport* airport, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airport->getCallsign() << ", " << airplane->getCallsign() << ", arriving at " << airport->getName() << ".\n";

};

void descendTo5000ftMessage(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$" << airplane->getCallsign() << ", radar contact, descend and maintain five thousand feet, squawk " << airplane->getSquawkCode() << ".\n";


};
void descendTo5000ftConfirmation(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Descend and maintain five thousand feet, squawking " << airplane->getSquawkCode() << ", " << airplane->getCallsign() << ".\n";

};

void waitBeforeDescendMessage(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", hold south on the one eighty radial, expect further clearance at " << time << ".\n";




};
void waitBeforeDescendConfirmation(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Holding south on the one eighty radial, " << airplane->getCallsign() << ".\n";


};

void descendTo3000ftMessage(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$" << airplane->getCallsign() << ", radar contact, descend and maintain three thousand feet.\n";


};
void descendTo3000ftConfirmation(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Descend and maintain five thousand feet, " << airplane->getCallsign() << ".\n";

};


void finalApproachMessage(Airplane* airplane, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$" << airplane->getCallsign() << ", cleared ILS approach runway" << runway->getName() << ".\n";


};
void finalApproachConfirmation(Airplane* airplane, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Cleared ILS approach runway " << runway->getName() << ", " << airplane->getCallsign() << ".\n";

};

void afterLandingMessage(Airplane* airplane, Airport* airport, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airport->getCallsign() << ", " << airplane->getCallsign() << ", runway " << runway->getName() << "vacated.\n";

};


//Take off messages
void IFRRequest(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airplane->getAirport()->getCallsign() << ", " << airplane->getCallsign() << ", requesting IFR clearancy to " << airplane->getDestination() << ".\n";


};
void IFRMessage(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", " << airplane->getAirport()->getCallsign() << ", cleared to " << airplane->getDestination() << ", maintain five thousand, "
                    "expect flight level one zero zero - ten minutes after departure, squawk " << airplane->getSquawkCode() << ".\n";

};
void IFRConfirmation(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "Cleared to " << airplane->getDestination() << ", initial altitude five thousand, expecting one zero zero in ten, squawking "
                 << airplane->getSquawkCode() << ", " << airplane->getCallsign() << ".\n";

};

void pushbackRequest(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airplane->getAirport()->getCallsign() << ", " << airplane->getCallsign() << " at gate " << airplane->getGate() << ", requesting pushback.\n";

};
void pushbackMessage(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", " << airplane->getAirport()->getCallsign() << ", pushback approved.\n";

};
void pushbackConfirmation(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Pushback approved, " << airplane->getCallsign() << ".\n";

};

void readyToTaxiMessage(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airplane->getCallsign() << " is ready to taxi.\n";

};

void holdingShortAtRunway(Airplane* airplane, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airplane->getAirport()->getCallsign() << ", " << airplane->getCallsign() << ", holding short at " << runway->getName() << ".\n";

};

void waitAtRunwayMessage(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", hold position.\n";
};
void waitAtRunwayConfirmation(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Holding position, " << airplane->getCallsign() << ".\n";

};

void lineUpRunwayMessage(Airplane* airplane, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", line-up runway " << runway->getName() << " and wait.\n";

};
void lineUpRunwayConfirmation(Airplane* airplane, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Lining up runway " << runway->getName() << " and wait" << airplane->getCallsign();

};

void clearedForTakeOffMessage(Airplane* airplane, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", runway " << runway->getName() << " cleared for take-off.\n";
};
void clearedForTakeOffConfirmation(Airplane* airplane, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Runway " << runway->getName() << "cleared for take-off, " << airplane->getCallsign() << ".\n";

};


//Taxiing
void toHoldingPointMessage(Airplane* airplane, const string &taxiCrossing, const string &taxiPoint, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", taxi to holding point " << taxiCrossing  << " via " << taxiPoint << ".\n";

};
void toHoldingPointConfirmation(Airplane* airplane, const string &taxiCrossing, const string &taxiPoint, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Taxi to holding point " << taxiCrossing << " via " << taxiPoint << ", " << airplane->getCallsign() << ".\n";

};

void toRunwayMessage(Airplane* airplane, Runway* runway, const string &taxiPoint, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", taxi to runway " << runway->getName() << " via " << taxiPoint << ".\n";
};
void toRunwayConfirmation(Airplane* airplane, Runway* runway, const string &taxiPoint, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Taxi to runway " << runway->getName() << " via " << taxiPoint << ", " << airplane->getCallsign() << ".\n";

};

void toGateMessage(Airplane* airplane, int gateIndex,  const string &taxiPoint, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", taxi to gate " << gateIndex << " via " << taxiPoint << ".\n";

};
void toGateConfirmation(Airplane* airplane, int gateIndex,  const string &taxiPoint, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Taxi to gate " << gateIndex << " via " << taxiPoint << ", " << airplane->getCallsign() << ".\n";

};

void clearedToCrossRequest(Airplane* airplane, const string &taxiCrossing, const string &time ){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ " << airplane->getAirport()->getCallsign() << ", " << airplane->getCallsign() << ", holding short at  " << taxiCrossing << ".\n";

};
void clearedToCrossMessage(Airplane* airplane, const string &taxiCrossing, const string &time ){

    gOutputCommunicationLog << "[" << time << "][ATC]\n"
                 << "$ " << airplane->getCallsign() << ", cleared to cross " << taxiCrossing << ".\n";

};
void clearedToCrossConfirmation(const string &taxiCrossing, const string &time ){

    gOutputCommunicationLog << "[" << time << "][AIR]\n"
                 << "$ Cleared to cross runway " << taxiCrossing << ".\n" ;

};


//Emergency
void EmergencyAbove3000ftRequest(Airplane* airplane, Airport* airport, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]"
                 << "$ Mayday, mayday, mayday, " << airport->getCallsign() << ", " << airplane->getCallsign() << ", out of fuel, request immidiate landing, "
                 << airplane->getPassengers() << " passengers on board.\n";

};
void EmergencyAbove3000ftMessage(Airplane* airplane, Runway* runway, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]"
                 << "$ " << airplane->getCallsign() << ", roger mayday, squawk seven seven zero zero, cleared ILS landing runway " << runway->getName() << ".\n";

};
void EmergencyBelow3000ftRequest(Airplane* airplane, Airport* airport, const string &time){

    gOutputCommunicationLog << "[" << time << "][AIR]"
                 << "$ Mayday, mayday, mayday, " << airport->getCallsign() << ", " << airplane->getCallsign() << ", out of fuel, performing emergency landing, "
                 << airplane->getPassengers() << " passengers on board.\n";

};
void EmergencyBelow3000ftMessage(Airplane* airplane, const string &time){

    gOutputCommunicationLog << "[" << time << "][ATC]"
                 << "$ " << airplane->getCallsign() << ", roger mayday, squawk seven seven zero zero, emergency personal on standby, good luck!\n";

};







