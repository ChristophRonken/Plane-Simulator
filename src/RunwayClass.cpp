//
// Created by oliviervh on 01.03.18.
//

#include "RunwayClass.h"
#include "AirportHandler.h"

const string &Runway::getName() const {
    return name;
}

void Runway::setName(const string &name) {
    Runway::name = name;
    ENSURE(Runway::getName() == name, "name set");
}

Airport *Runway::getAirport() const {
    return airPort;
}

void Runway::setAirport(Airport *Port) {
    Runway::airPort = Port;
    ENSURE(Runway::getAirport() == Port, "setAirport set");
}

bool Runway::isOccupied() const {
    return occupied;
}

void Runway::setOccupied(bool occupied) {
    Runway::occupied = occupied;
    ENSURE(Runway::isOccupied() == occupied, "occupied set");
}

Runway::Runway(const string &name, Airport *airPort) : name(name), airPort(airPort) {
    occupied = false;
    Runway::length = 0;

    holdingShortOccupied = false;
    waitingOnRunway = false;

}

Runway::Runway() {
    Runway::occupied = false;
    Runway::length = 0;
    self = this;
    holdingShortOccupied = false;
    waitingOnRunway = false;
}

const string &Runway::getType() const {
    return type;
}

void Runway::setType(const string &type) {
    REQUIRE(type == "grass" || type == "asphalt", "valid runway type");
    Runway::type = type;
    ENSURE(Runway::getType() == type, "type set");
}

int Runway::getLength() const {
    return length;
}

void Runway::setLength(int length) {
    Runway::length = length;
    ENSURE(Runway::getLength() == length, "lenght set");
}

void Runway::setVar(string Type, string Value) {



    if (Type == "name"){
        Runway::setName(Value);
        return ;
    }

    else if (Type == "type"){
        Runway::setType(Value);
        return;
    }

    else if (Type == "length"){

        int i;
        istringstream(Value) >> i;
        Runway::setLength(i);

        return;
    }

}

void Runway::setTaxiRoute(TaxiRoute* taxi){
    Runway::taxiRoute = taxi;
    ENSURE(Runway::getTaxiRoute() == taxi, "taxiroute set");
}

TaxiRoute* Runway::getTaxiRoute(){

    return Runway::taxiRoute;
}

void Runway::setHoldingShortOccupied(bool boolean){
    Runway::holdingShortOccupied = boolean;
    ENSURE(Runway::getHoldingShortOccupied() == boolean, "holding short occupied set");
}

void Runway::setWaitingOnRunway(bool boolean){
    Runway::waitingOnRunway = boolean;
    ENSURE(Runway::getWaitingOnRunway() == boolean, "wayting on runway set");
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

void Runway::setCrossing(bool cross){
    Runway::crossing = cross;
    ENSURE(Runway::getCrossing() == cross, "crossing set");
}

bool Runway::getPermissionToCross(){
    return Runway::permissiontocross;
}

void Runway::setPermissionToCross(bool cross){
    Runway::permissiontocross = cross;
    ENSURE(Runway::getPermissionToCross() == cross, "permission to cross set");
}

bool Runway::propperlyInitialised() {
    return (this == self);
}

bool Runway::isValid() {
    if (taxiRoute == NULL){
        return false;

    }

    return !(name.empty() || type.empty() || length == 0 || !taxiRoute->isValid() || !propperlyInitialised());
}

bool Runway::getonItsWay(){
    return Runway::onItsWay;
}

void Runway::setonItsWay(bool onitsway){
    Runway::onItsWay = onitsway;
    ENSURE(Runway::getonItsWay() == onitsway, "on its way set");
}