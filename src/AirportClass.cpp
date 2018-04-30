// author: Ronken Christoph & Van Hautte Olivier
// date: 02/05/2018
// version: 2.0

#include "AirportClass.h"
#include <algorithm>

Airport::Airport() {
    Airport::self = this;
    Airport::name = "";
    Airport::iata = "";
    Airport::callsign = "";
    Airport::gates = 0;
    vector<bool> occupiedGates(0);
    Airport::gatesOccupied = occupiedGates;
    Airport::wait5000 = NULL;
    Airport::wait3000 = NULL;
    vector<Runway*> runways(0);
    Airport::runways = runways;
}

Airport::Airport(const string &name, const string &iata, const string &callsign, int &gates){
    Airport::self = this;
    Airport::name = name;
    Airport::iata = iata;
    Airport::callsign = callsign;
    Airport::gates = gates;
    vector<bool> gatesOccupied(gates);
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


//getters & setters
const string &Airport::getName() const {
    return Airport::name;
}
void Airport::setName(const string &name) {
    Airport::name = name;
    ENSURE(Airport::name == name, "Airport name set");
}

const string &Airport::getIata() const {
    return Airport::iata;
}
void Airport::setIata(const string &iata) {
    Airport::iata = iata;
    ENSURE(Airport::iata == iata, "Airport iata set");
}

const string &Airport::getCallsign() const {
    return callsign;
}
void Airport::setCallsign(const string &callsign) {
    Airport::callsign = callsign;
    ENSURE(Airport::name == name, "Airport name set");

}

int Airport::getGates() const {
    return gates;
}
void Airport::setGates(int &gates) {
    Airport::gates = gates;
    Airport::gatesOccupied.resize(gates, false);
    ENSURE(Airport::gates == gates, "Gates set");
    ENSURE(Airport::gatesOccupied.size() == (unsigned)gates, "Added new gates");
}

const vector<Runway *> &Airport::getRunways() const {
    return Airport::runways;
}
void Airport::setRunways(const vector<Runway *> &runways) {
    for (unsigned int i = 0; i < runways.size(); i++){
        Airport::addRunway(runways[i]);
    }
}

const vector<bool> &Airport::getGatesOccupied() const {
    return Airport::gatesOccupied;
}
void Airport::setGatesOccupied(const vector<bool> &gatesOccupied) {
    Airport::gatesOccupied = gatesOccupied;
    ENSURE(Airport::gatesOccupied == gatesOccupied, "Set gatesOccupied");
}

Airplane* Airport::getWait5000(){
    return Airport::wait5000;
}
void Airport::setWait5000(Airplane* plane){
    Airport::wait5000 = plane;
}

Airplane* Airport::getWait3000(){
    return Airport::wait3000;
}
void Airport::setWait3000(Airplane* plane){
    Airport::wait3000 = plane;
}

bool Airport::getGateOccupied(const int &i) {
    REQUIRE(validGateIndex(i), "Valid gate index");
    return Airport::gatesOccupied[i];
}
void Airport::setGateOccupied(const int &i, const bool &occ) {
    REQUIRE(validGateIndex(i), "Valid gate index");
    int gateIndex;

    if (i == -1){
        gateIndex = Airport::getFreeGates()[0];
    }
    else {
        gateIndex = i;
    }

    Airport::gatesOccupied[gateIndex] = occ;

    if (!occ){
        logMessage("Gate ("  + intToString(gateIndex) + ") is now unoccupied");
    }
}

vector<int> Airport::getFreeGates() {
    vector<int> freeGates;

    for (unsigned int i = 0; i < Airport::gatesOccupied.size(); i++){
        if (!Airport::gatesOccupied[i]){
            freeGates.push_back(i);
        }
    }

    ENSURE(&freeGates != NULL, "Gates exists");
    return freeGates;
}

vector<int> Airport::getFreeRunways() {
    vector<int> freeRunways;

    for (unsigned int i = 0; i < Airport::runways.size(); i++){
        if (!Airport::runways[i]->isOccupied()){
            freeRunways.push_back(i);
        }
    }

    ENSURE(&freeRunways != NULL, "RW exists");

    return freeRunways;
}

Runway* Airport::getRunway(const string &name){
    REQUIRE(runwayExists(name), "runway with given name doesn't exist");
    for (unsigned int i=0; i<Airport::getRunways().size(); i++){
        if (Airport::getRunways()[i]->getName() == name){
            return Airport::getRunways()[i];
        };
    }
    return NULL;
}

void Airport::setVar(const string &type, const string &value) {
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
        ENSURE(false, "Invalid input Type");
    }
}


//add remove
void Airport::addRunway(Runway *runway) {

    REQUIRE(!runway->getName().empty(), "Runway bad name");
    REQUIRE(runway->getType() == "asphalt" or runway->getType() == "grass", "Runway bad type");
    REQUIRE(runway->getLength() > 0, "Runway bad length");
    REQUIRE(!runwayExists(runway->getName()), "Runway doesn't exist yet");

    runway->setAirport(this);
    Airport::runways.push_back(runway);

    string s;
    s = "Runway added (" + runway->getName() + ") to airport (" + this->getName() + ")";
    //logMessage(s);
}
void Airport::removeRunway(const string &name) {

    REQUIRE(runwayExists(name) && name != "", "Runway exists");

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
}


//checks
bool Airport::validGateIndex(const int &i) {
    if (i != -1) {
        return Airport::getGates() > i && i >= 0;
    }
    else {
        return !Airport::getFreeGates().empty();
    }
}
bool Airport::runwayExists(const string &name) {
    for (unsigned int i = 0; i < Airport::runways.size(); i++){
        if (Airport::runways[i]->getName() == name){
            return true;
        }
    }
    return false;
}
bool Airport::properlyInitialised() {
    return (this == Airport::self);
}
bool Airport::isValid() {
    return !(!Airport::properlyInitialised() || Airport::name.empty() || Airport::iata.empty() || Airport::callsign.empty() || Airport::gates == 0);
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


