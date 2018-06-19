//
// Created by oliviervh on 01.03.18.
//

#include "RunwayClass.h"
#include "AirportHandler.h"

const string &Runway::getName() const {
    return Runway::name;
}

void Runway::setName(const string &name) {
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::name = name;
    ENSURE(Runway::getName() == name, "name set");
}

Airport *Runway::getAirport() const {
    return Runway::airport;
}

void Runway::setAirport(Airport *airport) {
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::airport = airport;
    ENSURE(Runway::getAirport() == airport, "setAirport set");
}

bool Runway::isOccupied() const {
    return Runway::occupied;
}

void Runway::setOccupied(bool occupied) {
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::occupied = occupied;
    ENSURE(Runway::isOccupied() == occupied, "occupied set");
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
    REQUIRE(properlyInitialised(), "properly initialised");
    REQUIRE(type == "grass" || type == "asphalt", "valid runway type");
    Runway::type = type;
    ENSURE(Runway::getType() == type, "type set");
}

int Runway::getLength() const {
    return Runway::length;
}

void Runway::setLength(int length) {
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::length = length;
    ENSURE(Runway::getLength() == length, "lenght set");
}

void Runway::setTaxiRoute(TaxiRoute* taxi){
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::taxiRoute = taxi;
    ENSURE(Runway::getTaxiRoute() == taxi, "taxiroute set");
}

TaxiRoute* Runway::getTaxiRoute(){
    REQUIRE(properlyInitialised(), "properly initialised");
    return Runway::taxiRoute;
}

void Runway::setHoldingShortOccupied(bool holdingShortOccupied){
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::holdingShortOccupied = holdingShortOccupied;
    ENSURE(Runway::getHoldingShortOccupied() == holdingShortOccupied, "holding short occupied set");
}

void Runway::setWaitingOnRunway(bool waitingOnRunway){
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::waitingOnRunway = waitingOnRunway;
    ENSURE(Runway::getWaitingOnRunway() == waitingOnRunway, "wayting on runway set");
}

bool Runway::getHoldingShortOccupied(){
    REQUIRE(properlyInitialised(), "properly initialised");
    return Runway::holdingShortOccupied;
}

bool Runway::getWaitingOnRunway(){
    REQUIRE(properlyInitialised(), "properly initialised");
    return Runway::waitingOnRunway;
}

bool Runway::getCrossing(){
    REQUIRE(properlyInitialised(), "properly initialised");
    return Runway::crossing;
}

void Runway::setCrossing(bool crossing){
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::crossing = crossing;
    ENSURE(Runway::getCrossing() == crossing, "crossing set");
}

bool Runway::getPermissionToCross(){
    REQUIRE(properlyInitialised(), "properly initialised");
    return Runway::permissionToCross;
}

void Runway::setPermissionToCross(bool permissionToCross){
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::permissionToCross = permissionToCross;
    ENSURE(Runway::getPermissionToCross() == permissionToCross, "permission to cross set");
}

bool Runway::properlyInitialised() {
    return (this == Runway::self);
}

bool Runway::isValid() {
    if (Runway::taxiRoute == NULL){
        return false;

    }

    return !(Runway::name.empty() || Runway::type.empty() || Runway::length == 0 || !Runway::taxiRoute->isValid() || !Runway::properlyInitialised());
}

bool Runway::getOnItsWay(){
    REQUIRE(properlyInitialised(), "properly initialised");
    return Runway::onItsWay;
}

void Runway::setOnItsWay(bool onItsWay){
    REQUIRE(properlyInitialised(), "properly initialised");
    Runway::onItsWay = onItsWay;
    ENSURE(Runway::getOnItsWay() == onItsWay, "on its way set");
}