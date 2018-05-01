//
// Created by oliviervh on 01.03.18.
//

#include "AirportClass.h"
#include <algorithm>

Airport::Airport() {
    Airport::name = "";
    Airport::iata = "";
    Airport::callsign = "";
    Airport::gates = 0;
    Airport::self = this;
    vector<bool> gatesOccupied(0);
    Airport::gatesOccupied = gatesOccupied;
    Airport::wait5000 = NULL;
    Airport::wait3000 = NULL;
    vector<Runway*> runways(0);
    Airport::runways = runways;
}

Airport::Airport(const string &name, const string &iata, const string &callsign, int gates){
    Airport::name = name;
    Airport::iata = iata;
    Airport::callsign = callsign;
    Airport::gates = gates;
    Airport::self = this;
    vector<bool> gatesOccupied(0);
    Airport::gatesOccupied = gatesOccupied;
    Airport::wait5000 = NULL;
    Airport::wait3000 = NULL;
    vector<Runway*> runways(0);
    Airport::runways = runways;


};

Airport::~Airport() {

    for (unsigned int i = 0; i < Airport::runways.size(); i++){

        delete Airport::runways[i];

    }
}

const string &Airport::getName() const {
    return Airport::name;
}
void Airport::setName(const string &name) {
    Airport::name = name;
    ENSURE(Airport::name == name, "Airport name set");
}

const string &Airport::getIata() const {
    return iata;
}
void Airport::setIata(const string &iata) {
    Airport::iata = iata;
    ENSURE(Airport::iata == iata, "Airport iata set");
}

const string &Airport::getCallsign() const {
    return Airport::callsign;
}
void Airport::setCallsign(const string &callsign) {
    Airport::callsign = callsign;
    ENSURE(Airport::name == name, "Airport name set");
}

int Airport::getGates() const {
    return gates;
}
void Airport::setGates(int gates) {
    Airport::gates = gates;
    Airport::gatesOccupied.resize(Airport::gates, false);
    ENSURE(Airport::gates == gates, "Gates set");
    ENSURE(Airport::gatesOccupied.size() == unsigned(Airport::gates), "Added new gates");
}

const vector<Runway *> &Airport::getRunways() const {
    return Airport::runways;
}
void Airport::setRunways(const vector<Runway *> &runways) {
    for (int i=0; i< (signed) runways.size(); i++){
        Airport::addRunway(runways[i]);
    }
    ENSURE(Airport::runways == runways, "Runways set");
}

const vector<bool> &Airport::getGatesOccupied() const {
    return Airport::gatesOccupied;
}
void Airport::setGatesOccupied(const vector<bool> &gatesOccupied) {
    Airport::gatesOccupied = gatesOccupied;
    ENSURE(Airport::gatesOccupied == gatesOccupied, "Set GatesOccupied");

}

Airplane* Airport::getWait5000(){
    return Airport::wait5000;
}
void Airport::setWait5000(Airplane* plane){
    Airport::wait5000 = plane;
    ENSURE(Airport::wait5000 == plane, "wait 5000 set");
}

Airplane* Airport::getWait3000(){
    return Airport::wait3000;
}
void Airport::setWait3000(Airplane* plane){
    Airport::wait3000 = plane;
    ENSURE(Airport::wait3000 == plane, "wait 3000 set");
}

bool Airport::getGateOccupied(int i) {

    REQUIRE(Airport::validGateIndex(i), "Valid gate index");

    return Airport::gatesOccupied[i];

}
void Airport::setGateOccupied(int i, bool occ) {
    REQUIRE(Airport::validGateIndex(i), "Valid gate index");

    if (i == -1){
        i = Airport::getFreeGates()[0];
    }
    Airport::gatesOccupied[i] = occ;
    if (!occ){
        logMessage("Gate ("  + intToString(i) + ") is now unoccupied");

    }

    ENSURE(Airport::gatesOccupied[i] == occ, "gate set");

}

vector<int> Airport::getFreeGates() {
    vector<int> gates;

    for (unsigned int i = 0; i < Airport::gatesOccupied.size(); i++){
        if (!Airport::gatesOccupied[i]){
            gates.push_back(i);
        }
    }

    ENSURE(&gates != NULL, "Gates exists");

    return gates;
}

vector<int> Airport::getFreeRunways() {
    vector<int> runways;

    for (unsigned int i = 0; i < Airport::runways.size(); i++){
        if (!Airport::runways[i]->isOccupied()){
            runways.push_back(i);

        }

    }

    ENSURE(&runways != NULL, "RW exists");

    return runways;
}

Runway* Airport::getRunway(string name){
    for (unsigned int i=0; i<Airport::runways.size(); i++){
        if (Airport::runways[i]->getName() == name){
            return Airport::runways[i];
        };
    }
    return NULL;

}
void Airport::setVar(string type, string value) {
    if (type == "name"){
        Airport::setName(value);
        return;
    }

    else if (type == "iata"){
        Airport::setIata(value);
        return;
    }

    else if (type == "callsign"){
        Airport::setCallsign(value);
        return;
    }

    else if (type == "gates"){
        if (isNumber(value)){
            int i;
            istringstream(value) >> i;
            Airport::setGates(i);
        }
        return;

    }

    else{
        ENSURE(false, "Invalid input type");

    }

}


//add remove
void Airport::addRunway(Runway *runway) {

    REQUIRE(!runway->getName().empty(), "Runway bad name");
    REQUIRE(runway->getType() == "asphalt" or runway->getType() == "grass", "Runway bad type");
    REQUIRE(runway->getLength() > 0, "Runway bad length");
    REQUIRE(!Airport::runwayExists(runway->getName()), "Runway doesn't exist yet");

    runway->setAirport(this);
    Airport::runways.push_back(runway);

    string s;
    s = "Runway added (" + runway->getName() + ") to airport (" + this->getName() + ")";
    //logMessage(s);

}
void Airport::removeRunway(string name) {

    REQUIRE(Airport::runwayExists(name) && !name.empty(), "Runway exists");

    for (unsigned int i = 0; i < Airport::runways.size(); i++){
        if (Airport::runways[i]->getName() == name){
            Airport::runways[i]->setAirport(NULL);
            string t = Airport::runways[i]->getName();
            delete Airport::runways[i];
            Airport::runways[i] = Airport::runways[Airport::runways.size()-1];
            Airport::runways.resize(Airport::runways.size()-1);

            logMessage("Runway Deleted (" + t + ")" );
            return;
        }
    }

    ENSURE(!Airport::runwayExists(name), "wait 5000 set");

}


//checks
bool Airport::validGateIndex(int i) {

    if (i != -1) {
        return Airport::gates > i && i >= 0;
    }else{
        return (!Airport::getFreeGates().empty());

    }
}
bool Airport::runwayExists(string name) {
    for (unsigned int i = 0; i < Airport::runways.size(); i++){
        if (Airport::runways[i]->getName() == name){
            return true;
        }
    }

    return false;
}


//output
void Airport::printInfo() {

    cout << Airport::getInfo();

}
string Airport::getInfo() {

    string s;
    s += "\nAirport:\t" + Airport::name + " (" + Airport::iata + ")\n"
         + "->callsign:\t" + Airport::callsign + "\n"
         + "->gates:\t" + intToString(Airport::gates) + "\n"
         + "->runways:\t" + intToString(static_cast<int>(Airport::runways.size())) + "\n";

    return s;
}

bool Airport::propperlyInitialised() {
    return (this == Airport::self);
}

bool Airport::isValid() {
    return !(!Airport::propperlyInitialised() || Airport::name.empty() || Airport::iata.empty() || Airport::callsign.empty() || Airport::gates == 0);
}
