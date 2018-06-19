//
// Created by oliviervh on 01.03.18.
//

#include "Airport.h"

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
    ENSURE(Airport::getName() == name, "Airport name set");
}

const string &Airport::getIata() const {
    return iata;
}
void Airport::setIata(const string &iata) {
    Airport::iata = iata;
    ENSURE(Airport::getIata() == iata, "Airport iata set");
}

const string &Airport::getCallsign() const {
    return Airport::callsign;
}
void Airport::setCallsign(const string &callsign) {
    Airport::callsign = callsign;
    ENSURE(Airport::getCallsign() == callsign, "Airport callsign set");
}

int Airport::getGates() const {
    return gates;
}
void Airport::setGates(int gates) {
    Airport::gates = gates;
    Airport::gatesOccupied.resize(Airport::gates, false);
    ENSURE(Airport::getGates() == gates, "Gates set");
    ENSURE(Airport::getGatesOccupied().size() == unsigned(Airport::getGates()), "Added new gates");
}

const vector<Runway *> &Airport::getRunways() const {
    return Airport::runways;
}
void Airport::setRunways(const vector<Runway *> &runways) {

    REQUIRE(validRunways(runways), "valid runways");

    Airport::runways = runways;

    ENSURE(Airport::getRunways() == runways, "Runways set");
}

const vector<bool> &Airport::getGatesOccupied() const {
    return Airport::gatesOccupied;
}
void Airport::setGatesOccupied(const vector<bool> &gatesOccupied) {
    Airport::gatesOccupied = gatesOccupied;
    ENSURE(Airport::getGatesOccupied() == gatesOccupied, "Set GatesOccupied");

}

Airplane* Airport::getWait5000(){
    return Airport::wait5000;
}
void Airport::setWait5000(Airplane* plane){
    Airport::wait5000 = plane;
    ENSURE(Airport::getWait5000() == plane, "wait 5000 set");
}

Airplane* Airport::getWait3000(){
    return Airport::wait3000;
}
void Airport::setWait3000(Airplane* plane){
    Airport::wait3000 = plane;
    ENSURE(Airport::getWait3000() == plane, "wait 3000 set");
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

    ENSURE(Airport::getGateOccupied(i) == occ, "gate set");

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

Runway* Airport::getRunway(const string &name){
    for (unsigned int i=0; i<Airport::runways.size(); i++){
        if (Airport::runways[i]->getName() == name){
            return Airport::runways[i];
        };
    }
    return NULL;

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

    ENSURE(Airport::runwayExists(runway->getName()), "runway added");

}
void Airport::removeRunway(const string &name) {

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

bool Airport::runwayExists(const string &name) {
    if (Airport::runways.empty()){
        return false;
    }
    for (unsigned int i = 0; i < Airport::runways.size(); i++){
        if (Airport::runways[i]->getName() == name){
            return true;
        }
    }

    return false;
}


//output
string Airport::getInfo() {

    string s;
    s += "\nAirport:\t" + Airport::name + " (" + Airport::iata + ")\n"
         + "->callsign:\t" + Airport::callsign + "\n"
         + "->gates:\t" + intToString(Airport::gates) + "\n"
         + "->runways:\t" + intToString(static_cast<int>(Airport::runways.size())) + "\n";

    return s;
}

bool Airport::properlyInitialised() {
    return (this == Airport::self);
}

bool Airport::isValid() {
    return !(!Airport::properlyInitialised() || Airport::name.empty() || Airport::iata.empty() || Airport::callsign.empty() || Airport::gates == 0);
}

bool Airport::validRunways(vector<Runway *> runways) {
    vector<string> names;
    for (unsigned int i = 0; i< runways.size(); i++){
        string name = runways[i]->getName();
        if (!(find(names.begin(), names.end(), name) == names.end() && name != "")){
            return false;
        }

        if (runways[i]->getType() != "grass" && runways[i]->getType() != "asphalt"){
            return false;

        }

        names.push_back(name);
    }

    return true;
}
