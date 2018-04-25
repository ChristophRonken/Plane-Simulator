//
// Created by oliviervh on 01.03.18.
//



#include "MessageSystem.h"

std::ofstream OutputStream("Log.txt");

void actionMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[;m--Action:\t\033[0m\033[0;m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");

}

void notificationMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[1;4;34m--Note:\t\t\033[0m\033[1;34m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");
}

void errorMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[1;4;31m--Error:\t\033[0m\033[1;31m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");

};

void succesMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[1;4;33m--Succes:\t\033[0m\033[1;33m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");
}

void inputMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[1;4;32m--Input:\t\033[0m\033[1;32m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");
}

string intToString(int i){

    stringstream ss;
    ss << i;
    string str = ss.str();
    return str;

};

ofstream * getText(){

    return &OutputStream;
};

/*
 * Landing messages
 */

void initialCommunicationMessage(Airplane* Plane, Airport* Port, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ " << Port->getCallsign() << ", " << Plane->getCallsign() << ", arriving at " << Port->getName() << ".\n";

};

void descendTo5000ftMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$" << Plane->getCallsign() << ", radar contact, descend and maintain five thousand feet, squawk " << Plane->getSquawkCode() << ".\n";


};

void descendTo5000ftConfirmation(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Descend and maintain five thousand feet, squawking " << Plane->getSquawkCode() << ", " << Plane->getCallsign() << ".\n";

};


void waitBeforeDescendMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", hold south on the one eighty radial, expect further clearance at " << time << ".\n";




};

void waitBeforeDescendConfirmation(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Holding south on the one eighty radial, " << Plane->getCallsign() << ".\n";


};


void descendTo3000ftMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$" << Plane->getCallsign() << ", radar contact, descend and maintain three thousand feet.\n";


};

void descendTo3000ftConfirmation(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Descend and maintain five thousand feet, " << Plane->getCallsign() << ".\n";

};


void finalApproachMessage(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$" << Plane->getCallsign() << ", cleared ILS approach runway" << Runw->getName() << ".\n";


};

void finalApproachConfirmation(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Cleared ILS approach runway " << Runw->getName() << ", " << Plane->getCallsign() << ".\n";

};


void afterLandingMessage(Airplane* Plane, Airport* Port, Runway* Runw, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ " << Port->getCallsign() << ", " << Plane->getCallsign() << ", runway " << Runw->getName() << "vacated.\n";
    // send taxi instructions afterwards.

};

/*
 * Take off messages
 */

void IFRRequest(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ " << Plane->getAirport()->getCallsign() << ", " << Plane->getCallsign() << ", requesting IFR clearancy to " << Plane->getDestination() << ".\n";


};

void IFRMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", " << Plane->getAirport()->getCallsign() << ", cleared to " << Plane->getDestination() << ", maintain five thousand, "
                    "expect flight level one zero zero - ten minutes after departure, squawk " << Plane->getSquawkCode() << ".\n";

};

void IFRConfirmation(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "Cleared to " << Plane->getDestination() << ", initial altitude five thousand, expecting one zero zero in ten, squawking "
                 << Plane->getSquawkCode() << ", " << Plane->getCallsign() << ".\n";

};


void pushbackRequest(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ " << Plane->getAirport()->getCallsign() << ", " << Plane->getCallsign() << " at gate " << Plane->getGate() << ", requesting pushback.\n";

};

void pushbackMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", " << Plane->getAirport()->getCallsign() << ", pushback approved.\n";

};

void pushbackConfirmation(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Pushback approved, " << Plane->getCallsign() << ".\n";

};


void readyToTaxiMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ " << Plane->getCallsign() << " is ready to taxi.\n";

    // Taxi instructions afterwards

};


void holdingShortAtRunway(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ " << Plane->getAirport()->getCallsign() << ", " << Plane->getCallsign() << ", holding short at " << Runw->getName() << ".\n";

};


void waitAtRunwayMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", hold position.\n";
};

void waitAtRunwayConfirmation(Airplane* Plane, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Holding position, " << Plane->getCallsign() << ".\n";

};


void lineUpRunwayMessage(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", line-up runway " << Runw->getName() << " and wait.\n";

};

void lineUpRunwayConfirmation(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Lining up runway " << Runw->getName() << " and wait" << Plane->getCallsign();

};


void clearedForTakeOffMessage(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", runway " << Runw->getName() << " cleared for take-off.\n";
};

void clearedForTakeOffConfirmation(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Runway " << Runw->getName() << "cleared for take-off, " << Plane->getCallsign() << ".\n";

};


/*
 * Taxiing
 */

void toHoldingPointMessage(Airplane* Plane, Runway* Runw, string taxiPoint, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", taxi to holding point " << Runw->getName() << " via " << taxiPoint << ".\n";

};

void toHoldingPointConfirmation(Airplane* Plane, Runway* Runw, string taxiPoint, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Taxi to holding point " << Runw->getName() << " via " << taxiPoint << ", " << Plane->getCallsign() << ".\n";

};


void toRunwayMessage(Airplane* Plane, Runway* Runw, string taxiPoint, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", taxi to runway " << Runw->getName() << " via " << taxiPoint << ".\n";
};

void toRunwayConfirmation(Airplane* Plane, Runway* Runw, string taxiPoint, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Taxi to runway " << Runw->getName() << " via " << taxiPoint << ", " << Plane->getCallsign() << ".\n";

};


void toGateMessage(Airplane* Plane, int gateIndex,  string taxiPoint, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", taxi to gate " << gateIndex << " via " << taxiPoint << ".\n";

};

void toGateConfirmation(Airplane* Plane, int gateIndex,  string taxiPoint, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ Taxi to gate " << gateIndex << " via " << taxiPoint << ", " << Plane->getCallsign() << ".\n";

};


void clearedToCrossMessage(Airplane* Plane, Runway* Runw, string time ){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", cleared to cross " << Runw->getName() << ".\n";

};

void clearedToCrossConfirmation(Airplane* Plane, Runway* Runw, string time ){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ Cleared to cross runway " << Runw->getName() << ".\n" ;

};


/*
 * Emergency
 */

void EmergencyAbove3000ftRequest(Airplane* Plane, Airport* Port, string time){

    OutputStream << "[" << time << "][AIR]"
                 << "$ Mayday, mayday, mayday, " << Port->getCallsign() << ", " << Plane->getCallsign() << ", out of fuel, request immidiate landing, "
                 << Plane->getPassengers() << " passengers on board.\n";

};

void EmergencyAbove3000ftMessage(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][ATC]"
                 << "$ " << Plane->getCallsign() << ", roger mayday, squawk seven seven zero zero, cleared ILS landing runway " << Runw->getName() << ".\n";

};


void EmergencyBelow3000ftRequest(Airplane* Plane, Airport* Port, string time){

    OutputStream << "[" << time << "][AIR]"
                 << "$ Mayday, mayday, mayday, " << Port->getCallsign() << ", " << Plane->getCallsign() << ", out of fuel, performing emergency landing, "
                 << Plane->getPassengers() << " passengers on board.\n";

};

void EmergencyBelow3000ftMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]"
                 << "$ " << Plane->getCallsign() << ", roger mayday, squawk seven seven zero zero, emergency personal on standby, good luck!\n";

};
