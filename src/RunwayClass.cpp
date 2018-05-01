//
// Created by oliviervh on 01.03.18.
//

#include "RunwayClass.h"
#include "AirportHandler.h"

const string &Runway::getName() const {
    return Runway::name;
}

void Runway::setName(const string &name) {
    Runway::name = name;
    ENSURE(Runway::name == name, "name set");
}

Airport *Runway::getAirport() const {
    return Runway::airport;
}

void Runway::setAirport(Airport *airport) {
    Runway::airport = airport;
    ENSURE(Runway::airport == airport, "setAirport set");
}

bool Runway::isOccupied() const {
    return Runway::occupied;
}

void Runway::setOccupied(bool occupied) {
    Runway::occupied = occupied;
    ENSURE(Runway::occupied == occupied, "occupied set");
}

Runway::Runway(const string &name, Airport *airport){
    Runway::self = this;
    Runway::name = name;
    Runway::occupied = false;
    Runway::length = 0;
    Runway::holdingShortOccupied = false;
    Runway::waitingOnRunway = false;
    Runway::airport = airport;
    Runway::taxiRoute = NULL;
    Runway::permissionToCross = true;
    Runway::crossing = false;
    Runway::onItsWay = false;

}

Runway::Runway() {
    Runway::self = this;
    Runway::name = "";
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

const string &Runway::getType() const {
    return Runway::type;
}

void Runway::setType(const string &type) {
    REQUIRE(type == "grass" || type == "asphalt", "valid runway type");
    Runway::type = type;
    ENSURE(Runway::type == type, "type set");
}

int Runway::getLength() const {
    return Runway::length;
}

void Runway::setLength(int length) {
    Runway::length = length;
    ENSURE(Runway::length == length, "lenght set");
}

void Runway::setVar(string type, string value) {

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

void Runway::setTaxiRoute(TaxiRoute* taxi){
    Runway::taxiRoute = taxi;
    ENSURE(Runway::taxiRoute == taxi, "taxiroute set");
}

TaxiRoute* Runway::getTaxiRoute(){

    return Runway::taxiRoute;
}

void Runway::setHoldingShortOccupied(bool holdingShortOccupied){
    Runway::holdingShortOccupied = holdingShortOccupied;
    ENSURE(Runway::holdingShortOccupied == holdingShortOccupied, "holding short occupied set");
}

void Runway::setWaitingOnRunway(bool waitingOnRunway){
    Runway::waitingOnRunway = waitingOnRunway;
    ENSURE(Runway::waitingOnRunway == waitingOnRunway, "wayting on runway set");
}

bool Runway::getHoldingShortOccupied(){
    return Runway::holdingShortOccupied;
}

bool Runway::getWaitingOnRunway(){
    return Runway::waitingOnRunway;
}

bool Runway::getCrossing(){
    return Runway::crossing;
}

void Runway::setCrossing(bool crossing){
    Runway::crossing = crossing;
    ENSURE(Runway::crossing == crossing, "crossing set");
}

bool Runway::getPermissionToCross(){
    return Runway::permissionToCross;
}

void Runway::setPermissionToCross(bool permissionToCross){
    Runway::permissionToCross = permissionToCross;
    ENSURE(Runway::permissionToCross == permissionToCross, "permission to cross set");
}

bool Runway::propperlyInitialised() {
    return (this == Runway::self);
}

bool Runway::isValid() {
    if (Runway::taxiRoute == NULL){
        return false;

    }

    return !(Runway::name.empty() || Runway::type.empty() || Runway::length == 0 || !Runway::taxiRoute->isValid() || !Runway::propperlyInitialised());
}

bool Runway::getonItsWay(){
    return Runway::onItsWay;
}

void Runway::setonItsWay(bool onitsway){
    Runway::onItsWay = onitsway;
    ENSURE(Runway::onItsWay == onitsway, "on its way set");
}