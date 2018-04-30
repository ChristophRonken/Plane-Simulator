// author: Ronken Christoph & Van Hautte Olivier
// date: 02/05/2018
// version: 2.0

#include "RunwayClass.h"
#include "AirportHandler.h"

Runway::Runway(const string &name, Airport *airport){
    Runway::self = this;
    Runway::name = name;
    Runway::airport = airport;
    Runway::occupied = false;
    Runway::length = 0;
    Runway::holdingShortOccupied = false;
    Runway::waitingOnRunway = false;
    Runway::airport = NULL;
    Runway::taxiRoute = NULL;
    Runway::permissionToCross = true;
    Runway::crossing = false;
    Runway::onItsWay = false;
}

Runway::Runway() {
    Runway::self = this;
    Runway::name = "";
    Runway::airport = NULL;
    Runway::occupied = false;
    Runway::length = 0;
    Runway::holdingShortOccupied = false;
    Runway::waitingOnRunway = false;
    Runway::airport = NULL;
    Runway::taxiRoute = NULL;
    Runway::permissionToCross = true;
    Runway::crossing = false;
    Runway::onItsWay = false;
}


//getters & setters
const string &Runway::getName() const {
    return Runway::name;
}
void Runway::setName(const string &name) {
    Runway::name = name;

}

Airport *Runway::getAirport() const {
    return Runway::airport;
}
void Runway::setAirport(Airport *airport) {
    Runway::airport = airport;
}

bool Runway::isOccupied() const {
    return occupied;
}
void Runway::setOccupied(const bool &occupied) {
    Runway::occupied = occupied;
}

const string &Runway::getType() const {
    return Runway::type;
}
void Runway::setType(const string &type) {
    REQUIRE(type == "grass" || type == "asphalt", "valid runway type");
    Runway::type = type;
}

int Runway::getLength() const {
    return Runway::length;
}
void Runway::setLength(const int &length) {
    Runway::length = length;
}

void Runway::setVar(const string &type, const string &value) {
    if (type == "name"){
        Runway::name = value;
        return ;
    }
    else if (type == "type"){
        Runway::type = value;
        return;
    }
    else if (type == "length"){
        int i;
        istringstream(value) >> i;
        Runway::length = i;
        return;
    }
}

TaxiRoute* Runway::getTaxiRoute(){
    return Runway::taxiRoute;
}
void Runway::setTaxiRoute(TaxiRoute* taxi){
    Runway::taxiRoute = taxi;
}

bool Runway::getHoldingShortOccupied(){
    return Runway::holdingShortOccupied;
}
void Runway::setHoldingShortOccupied(const bool &holdingShortOccupied){
    Runway::holdingShortOccupied = holdingShortOccupied;
}

bool Runway::getWaitingOnRunway(){
    return Runway::waitingOnRunway;
}
void Runway::setWaitingOnRunway(const bool &waitingOnRunway){
    Runway::waitingOnRunway = waitingOnRunway;
}

bool Runway::getCrossing(){
    return Runway::crossing;
}
void Runway::setCrossing(const bool &crossing){
    Runway::crossing = crossing;
}

bool Runway::getPermissionToCross(){
    return Runway::permissionToCross;
}
void Runway::setPermissionToCross(const bool &permissionToCross){
    Runway::permissionToCross = permissionToCross;
}

bool Runway::getonItsWay(){
    return Runway::onItsWay;
}
void Runway::setonItsWay(const bool &onItsWay){
    Runway::onItsWay = onItsWay;
}


//checks
bool Runway::propperlyInitialised() {
    return (this == Runway::self);
}
bool Runway::isValid() {
    if (Runway::taxiRoute == NULL){
        return false;

    }
    return !(Runway::name.empty() || Runway::type.empty() || Runway::length == 0 || !Runway::taxiRoute->isValid() || !Runway::propperlyInitialised());
}

