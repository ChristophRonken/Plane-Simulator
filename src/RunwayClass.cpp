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

}

Airport *Runway::getAirport() const {
    return airPort;
}

void Runway::setAirport(Airport *Port) {
    Runway::airPort = Port;
}

bool Runway::isOccupied() const {
    return occupied;
}

void Runway::setOccupied(bool occupied) {
    Runway::occupied = occupied;
}

Runway::Runway(const string &name, Airport *airPort) : name(name), airPort(airPort) {
    occupied = false;
    Runway::length = 0;
}

Runway::Runway() {
    Runway::occupied = false;
    Runway::length = 0;
    self = this;
}

const string &Runway::getType() const {
    return type;
}

void Runway::setType(const string &type) {
    REQUIRE(type == "grass" || type == "asphalt", "valid runway type");
    Runway::type = type;
}

int Runway::getLength() const {
    return length;
}

void Runway::setLength(int length) {
    Runway::length = length;
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
        if (is_number(Value)) {
            int i;
            istringstream(Value) >> i;
            Runway::setLength(i);
        }
        return;
    }

}

void Runway::setTaxiRoute(TaxiRoute* taxi){
    Runway::taxiRoute = taxi;
}

TaxiRoute* Runway::getTaxiRoute(){

    return Runway::taxiRoute;
}

void Runway::setHoldingShortOccupied(bool boolean){
    Runway::holdingShortOccupied = boolean;
}

void Runway::setWaitingOnRunway(bool boolean){
    Runway::wachtoprunway = boolean;
}

bool Runway::getHoldingShortOccupied(){
    return Runway::holdingShortOccupied;
}

bool Runway::getWaitingOnRunway(){
    return Runway::wachtoprunway;
}

bool Runway::getCrossing(){
    return Runway::crossing;
}

void Runway::setCrossing(bool cross){
    Runway::crossing = cross;
}

bool Runway::getPermissionToCross(){
    return Runway::permissiontocross;
}

void Runway::setPermissionToCross(bool cross){
    Runway::permissiontocross = cross;
}

bool Runway::propperlyInitialised() {
    return (this == self);
}

bool Runway::isValid() {
    if (taxiRoute == NULL){
        return false;

    }

    return !(name.empty() || type.empty() || length == 0 || taxiRoute->isValid() || !propperlyInitialised());
}
