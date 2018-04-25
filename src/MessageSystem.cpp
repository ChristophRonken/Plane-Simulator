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


void initialCommunicationMessage(Airplane* Plane, Airport* Port, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ " << Port->getCallsign() << ", " << Plane->getCallsign() << ", arriving at " << Port->getName() << ".\n";

};

void waitBeforeDescendMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$ " << Plane->getCallsign() << ", hold south on the one eighty radial, expect further clearance at " << time << ".\n"
                 << "[" << time << "][AIR]\n"
                 << "$ Holding south on the one eighty radial, " << Plane->getCallsign() << ".\n";



};

void descendTo5000ftMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$" << Plane->getCallsign() << ", radar contact, descend and maintain five thousand feet, squawk " << Plane->getSquawkCode() << ".\n"
                 << "[" << time << "][AIR]\n"
                 << "$ Descend and maintain five thousand feet, squawking " << Plane->getSquawkCode() << ", " << Plane->getCallsign() << ".\n";

};

void descendTo3000ftMessage(Airplane* Plane, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$" << Plane->getCallsign() << ", radar contact, descend and maintain three thousand feet.\n"
                 << "[" << time << "][AIR]\n"
                 << "$ Descend and maintain five thousand feet, " << Plane->getCallsign() << ".\n";

};

void finalApproachMessage(Airplane* Plane, Runway* Runw, string time){

    OutputStream << "[" << time << "][ATC]\n"
                 << "$" << Plane->getCallsign() << ", cleared ILS approach runway" << Runw->getName() << ".\n"
                 << "[" << time << "][AIR]\n"
                 << "$ Cleared ILS approach runway " << Runw->getName() << ", " << Plane->getCallsign() << ".\n";

};

void afterLandingMessage(Airplane* Plane, Airport* Port, Runway* Runw, string time){

    OutputStream << "[" << time << "][AIR]\n"
                 << "$ " << Port->getCallsign() << ", " << Plane->getCallsign() << ", runway " << Runw->getName() << "vacated.\n";
    // send taxi instructions afterwards.

};