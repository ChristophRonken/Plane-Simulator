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
    if (!occupied){
        notificationMessage("Runway ("  + getName() + ") is now unoccupied");

    }

}

Runway::Runway(const string &name, Airport *airPort) : name(name), airPort(airPort) {
    occupied = false;
    Runway::length = 0;
}

Runway::Runway() {
    Runway::occupied = false;
    Runway::length = 0;
}

const string &Runway::getType() const {
    return type;
}

void Runway::setType(const string &type) {
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
        int i;
        istringstream(Value) >> i;
        Runway::setLength(i);
        return;
    }

    else {
        REQUIRE(false, "Valid Type");
    }
}

void Runway::setTaxiRoute(TaxiRoute* taxi){
    Runway::taxiroute = taxi;
}

TaxiRoute* Runway::getTaxiRoute(){

    return Runway::taxiroute;
}

void Runway::setWachtaanRunway(bool boolean){
    Runway::wachtaanrunway = boolean;
}

void Runway::setWachtopRunway(bool boolean){
    Runway::wachtoprunway = boolean;
}

bool Runway::getWachtaanRunway(){
    return Runway::wachtaanrunway;
}

bool Runway::getWachtopRunway(){
    return Runway::wachtoprunway;
}