//
// Created by oliviervh on 01.03.18.
//

#include "AirplaneClass.h"
#include <string>
#include <cstdlib>

string gTime;
int gTimePassed;
int gStartingTime;


Airplane::Airplane(string type) : type(type) {
    Airplane::self = this;
    Airplane::number = "";
    Airplane::callsign = "";
    Airplane::model = "";
    Airplane::state = init;
    Airplane::engine = "";
    Airplane::size = "";
    Airplane::squawkCode = 0;
    Airplane::airport = NULL;
    Airplane::runway = NULL;
    Airplane::attemptRunway = NULL;
    Airplane::gate = -1;
    Airplane::fuel = 0;
    Airplane::fuelCapacity = 0;
    Airplane::passengers = 0;
    Airplane::passengerCapacity = 0;
    Airplane::height = 0;
    Airplane::operationTime = 0;
    Airplane::attemptGate = -1;
    Airplane::crossingIndex = 0;
    Airplane::currentTask = "";
    Airplane::flightPlan = NULL;
    Airplane::taxiRoute = NULL;
    Airplane::taxiPoint = "";
    Airplane::taxiCrossing = "";
    Airplane::technicalChecked = false;
    Airplane::alreadyLinedUp = false;
    Airplane::permissionToTakeOff = false;
    Airplane::waitAtRunway = false;
    Airplane::waitOnRunway = false;
    Airplane::simulationFinished = false;

}

//getters & setters

bool Airplane::getTechnicalChecked() const{
    return Airplane::technicalChecked;
}
void Airplane::setTechnicalChecked(bool technicalChecked) {
    Airplane::technicalChecked = technicalChecked;
    ENSURE(Airplane::technicalChecked == technicalChecked, "technicalChecked set");

}

const string &Airplane::getNumber() const {
    return Airplane::number;
}
void Airplane::setNumber(const string &number) {
    Airplane::number = number;
    ENSURE(Airplane::number == number, "number set");

}

const string &Airplane::getCallsign() const {
    return Airplane::callsign;
}
void Airplane::setCallsign(const string &callsign) {
    Airplane::callsign = callsign;
    ENSURE(Airplane::callsign == callsign, "callsign set");
}

const string &Airplane::getModel() const {
    return Airplane::model;
}
void Airplane::setModel(const string &model) {
    Airplane::model = model;
    ENSURE(Airplane::model == model, "model set");
}

const EState &Airplane::getState() const {
    return Airplane::state;
}
void Airplane::setState(const EState &state) {
    Airplane::state = state;
    ENSURE(Airplane::state == state, "state set");
}

int Airplane::getFuel() const {
    return Airplane::fuel;
}
void Airplane::setFuel(int fuel) {
    Airplane::fuel = fuel;
    ENSURE(Airplane::fuel == fuel, "fuel set");
}

int Airplane::getHeight() const {
    return Airplane::height;
}
void Airplane::setHeight(int height) {
    Airplane::height = height;
    ENSURE(Airplane::height == height, "height set");
}

int Airplane::getFuelCapacity() const {
    return Airplane::fuelCapacity;
}
void Airplane::setFuelCapacity(int fuelCapacity) {
    Airplane::fuelCapacity = fuelCapacity;
    ENSURE(Airplane::fuelCapacity == fuelCapacity, "fuel capacity set");
}

int Airplane::getPassengers() const {
    return Airplane::passengers;
}
void Airplane::setPassengers(int passengers) {
    Airplane::passengers = passengers;
    ENSURE(Airplane::passengers == passengers, "passengers set");
}

int Airplane::getPassengerCapacity() const {
    return Airplane::passengerCapacity;
}
void Airplane::setPassengerCapacity(int passengerCapacity) {
    Airplane::passengerCapacity = passengerCapacity;
    ENSURE(Airplane::passengerCapacity == passengerCapacity, "passenger capacity set");
}

Airport *Airplane::getAirport() const {
    return Airplane::airport;
}
void Airplane::setAirport(Airport *airport){
    Airplane::airport = airport;
    ENSURE(Airplane::airport == airport, "airport set");

}

const string &Airplane::getType() const {
    return Airplane::type;
}


const string &Airplane::getEngine() const {
    return Airplane::engine;
}
void Airplane::setEngine(const string &engine) {
    REQUIRE(Airplane::validEngineType(engine), "valid Engine");
    Airplane::engine = engine;
    ENSURE(Airplane::engine == engine, "engine set");

}

const string &Airplane::getSize() const {
    return Airplane::size;
}
void Airplane::setSize(const string &size) {
    REQUIRE(Airplane::validSize(size), "valid size");
    Airplane::size = size;
    ENSURE(Airplane::size == size, "size set");
}

int Airplane::getOperationTime() const {
    return Airplane::operationTime;
}
void Airplane::setOperationTime(int operationTime) {
    Airplane::operationTime = operationTime;
    ENSURE(Airplane::operationTime == operationTime, "operation time set");
}

Runway *Airplane::getRunway() const {
    return Airplane::runway;
}
void Airplane::setRunway(Runway *runway) {
    Airplane::runway = runway;
    ENSURE(Airplane::runway == runway, "runway set");

}

int Airplane::getGate() const {
    return Airplane::gate;
}
void Airplane::setGate(int gate) {
    REQUIRE(gate == -1 || Airplane::atAirport(), "at Airport");
    REQUIRE(Airplane::validGate(gate), "validGate");
    Airplane::gate = gate;
    ENSURE(Airplane::gate == gate, "gate set");
}

Runway *Airplane::getAttemptRunway() const {
    return Airplane::attemptRunway;
}
void Airplane::setAttemptRunway(Runway * attemptRunway) {
    Airplane::attemptRunway = attemptRunway;
    ENSURE(Airplane::attemptRunway == attemptRunway, "attempt runway set");
}

FlightPlan *Airplane::getFlightPlan() const {
    return Airplane::flightPlan;
}
void Airplane::setFlightPlan(FlightPlan *flightPlan) {
    Airplane::flightPlan = flightPlan;
    ENSURE(Airplane::flightPlan == flightPlan , "flight plan set");
}

TaxiRoute *Airplane::getTaxiRoute() const {
    return Airplane::taxiRoute;
}
void Airplane::setTaxiRoute(TaxiRoute *taxiRoute) {
    Airplane::taxiRoute = taxiRoute;
    ENSURE(Airplane::taxiRoute == taxiRoute, "taxiroute set");
}

const string &Airplane::getTaxiPoint() const {
    return Airplane::taxiPoint;
}
void Airplane::setTaxiPoint(const string &taxiPoint) {
    Airplane::taxiPoint = taxiPoint;
    ENSURE(Airplane::taxiPoint == taxiPoint, "taxi point set");
}

const string &Airplane::getTaxiCrossing() const {
    return Airplane::taxiCrossing;
}
void Airplane::setTaxiCrossing(const string &taxiCrossing) {
    Airplane::taxiCrossing = taxiCrossing;
    ENSURE(Airplane::taxiCrossing == taxiCrossing, "taxi crossing set");
}

void Airplane::setSquawkCode(int code){

    int index = 0;

    if (code == 0){
        if (Airplane::type == "private"){
            if (Airplane::size == "small"){
                index = privateSmallSquawk;

            }else{
                index = privateMediumSquawk;

            }
        }
        if (Airplane::type == "airline"){
            if (Airplane::size == "medium"){
                if (Airplane::engine == "propeller"){
                    index = airlineMediumPropellerSquawk;

                }else{
                    index = airlineMediumJetSquawk;

                }

            }else{
                index = airlineLargeSquawk;

            }
        }
        if (Airplane::type == "military"){
            index = militarySquawk;

        }
        if (Airplane::type == "emergency"){
            index = emegencySquawk;

        }

        if (index == privateSmallSquawk) {
            Airplane::squawkCode = 0000001;

        }else{
            int code = 1000*index;
            Airplane::squawkCode = code;

        }

    }else{
        Airplane::squawkCode = 1;

    }

    ENSURE(Airplane::getSquawkCode() != 0 , "squawkCode set");
}
int Airplane::getSquawkCode() const {
    return Airplane::squawkCode;
}



void setTime(const string &time){
    gTime = time;
    ENSURE(gTime == time , "gTime set");
};
const string &getTime(){
    return gTime;

};

void setTimePassed(int time){
    gTimePassed = time;
    ENSURE(gTimePassed == time, "passed time set");

}
int getTimePassed(){
    return gTimePassed;

}

void setStartingTime(int time){
    gStartingTime = time;
    ENSURE(gStartingTime == time , "starting time set");

}
int getStartingTime(){
    return gStartingTime;

}

const string &Airplane::getDestination() {
    REQUIRE(Airplane::getFlightPlan() != NULL, "has a flightPlan");
    return Airplane::flightPlan->getDestination();
}


bool Airplane::getSimulationFinished(){
    return Airplane::simulationFinished;
}
void Airplane::setSimulationFinished(bool finished){
    Airplane::simulationFinished = finished;
    ENSURE(Airplane::simulationFinished == finished , "simulation finished set");
}

const string &Airplane::getCurrentTask() const {
    return Airplane::currentTask;
}
void Airplane::setCurrentTask(const string &currentTask) {
    Airplane::currentTask = currentTask;
    ENSURE(Airplane::currentTask == currentTask , "currentTask set");
}


//checks
bool Airplane::validLandingSpot(Airport *airport, Runway *runway) {

    if (airport == NULL){
        return false;
    }

    Airplane::airport = airport;

    if (runway == NULL) {
        return Airplane::validRunway(runway);
    }
    else {
        return Airplane::validRunway(runway) && !runway->isOccupied();
    }
}

bool Airplane::validGate(int gate) {

    if (gate == -1){
        return true;

    }
    if (!(gate >= 0 && gate < Airplane::airport->getGates())){
        return false;
    }
    return !Airplane::airport->getGateOccupied(gate) || Airplane::attemptGate == gate;

}

bool Airplane::validRunway(Runway* runway){

    if (runway == NULL){
        vector<int> runways = Airplane::airport->getFreeRunways();
        for (int i = 0; (unsigned)i<runways.size(); i++){
            Runway *runway = Airplane::airport->getRunways()[runways[i]];
            if (Airplane::size == "small"){
                if (Airplane::engine == "propeller"){
                    if (runway->getLength() >= kRunwayLengthA){
                        return true;
                    }
                    continue;
                }
                else if (Airplane::engine == "jet"){
                    if (runway->getLength() >= kRunwayLengthB && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (Airplane::size == "medium"){
                if (Airplane::engine == "propeller"){
                    if (runway->getLength() >= kRunwayLengthB && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (Airplane::engine == "jet"){
                    if (runway->getLength() >= kRunwayLengthD && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (Airplane::size == "large"){
                if (Airplane::engine == "propeller"){
                    if (runway->getLength() >= kRunwayLengthC && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (Airplane::engine == "jet"){
                    if (runway->getLength() >= kRunwayLengthE && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
        }
        return false;
    }
    else if (Airplane::size == "small"){
        if (Airplane::engine == "propeller"){
            if (runway->getLength() >= kRunwayLengthA){
                return true;
            }
            else{
                return false;
            }
        }
        else if (Airplane::engine == "jet"){
            if (runway->getLength() >= kRunwayLengthB && runway->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (Airplane::size == "medium"){
        if (Airplane::engine == "propeller"){
            if (runway->getLength() >= kRunwayLengthB && runway->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
        else if (Airplane::engine == "jet"){
            if (runway->getLength() >= kRunwayLengthD && runway->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (Airplane::size == "large"){
        if (Airplane::engine == "propeller"){
            if (runway->getLength() >= kRunwayLengthC && runway->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
        else if (Airplane::engine == "jet"){
            if (runway->getLength() >= kRunwayLengthB && runway->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
    }
    return false;
}

bool Airplane::validEngineType(const string &engine) {
    return true;
}

bool Airplane::validSize(const string &size) {
    return true;
}

bool Airplane::atAirport() {

    return (Airplane::airport != NULL);

}

bool Airplane::atGate() {

    return Airplane::gate >= 0;

}

bool Airplane::readyForTakeOff() {
    return (Airplane::isReadyForDeparture() && Airplane::airport != NULL && Airplane::runway != NULL && Airplane::state == holdingpointCMS);
}

bool Airplane::permissionToDescend(int height, Airport* airport, Runway* runway){
    if (height == Airplane::kHeightLevelA){
        if (airport->getWait5000() == NULL){
            airport->setWait5000(this);
            return true;
        }
        else{
            return false;
        }
    }
    else if (height == Airplane::kHeightLevelB){
        if (airport->getWait3000() == NULL){
            airport->setWait5000(NULL);
            airport->setWait3000(this);
            return true;
        }
        else{
            return false;
        }
    }
    else if (height == Airplane::kHeightLevelC){
        if (runway->isOccupied()){

            return false;
        }
        else{
            if (validRunway(runway)) { ;
                airport->setWait3000(NULL);
                return true;
            }else{
                return false;

            }
        }
    }
    else {
        return true;
    }
}

bool Airplane::isReadyForDeparture() const {

    if (Airplane::passengers == Airplane::passengerCapacity){
        if (Airplane::fuel == Airplane::fuelCapacity){
            return true;
        }
    }
    return false;

}

bool Airplane::properlyInitialised() {
    return (Airplane::self == this);
}

bool Airplane::isValid() {

    if (Airplane::size.empty() || Airplane::fuel == 0 || Airplane::model.empty() || Airplane::number.empty()
        || Airplane::callsign.empty() || (Airplane::state !=  incoming && Airplane::state != gTechnicalCheck)|| Airplane::engine.empty()){
        return false;
    }

    return (validSize(Airplane::size) && validEngineType(Airplane::engine) && Airplane::properlyInitialised());

}


// functies
void Airplane::pushBack() {
    REQUIRE(Airplane::getCurrentTask() == "IFR" || Airplane::getCurrentTask() == "pushback"
            || Airplane::getCurrentTask() == "request taxi", "correct state");
    REQUIRE(Airplane::atAirport(), "At airport");
    REQUIRE(Airplane::validRunway(), "Valid runway");
    REQUIRE(Airplane::flightPlan != NULL, "flightplan assigned");

    string tijd = getTime();

    if (Airplane::currentTask == "IFR") {

        if (Airplane::state == ifr) {

            if (Airplane::attemptRunway == NULL) {
                Airplane::airport->getFreeRunways();
                for (unsigned int i = 0; i < Airplane::airport->getFreeRunways().size(); i++) {
                    if (validRunway(Airplane::airport->getRunways()[i])) {
                        Airplane::attemptRunway = Airplane::airport->getRunways()[i];
                        break;
                    }
                }
                if (Airplane::attemptRunway == NULL){
                    return;
                }
            }
            Airplane::attemptRunway->setOnItsWay(true);
            IFRRequest(this, tijd);
            Airplane::state = ifrRMS;
            return;
        }
        if (Airplane::state == ifrRMS && runway == NULL) {
            runway = Airplane::attemptRunway;
        }
        if (Airplane::state == ifrRMS) {
            IFRMessage(this, tijd);
            Airplane::state = ifrMMS;
            return;
        }
        if (Airplane::state == ifrMMS) {
            IFRConfirmation(this, tijd);
            Airplane::currentTask = "pushback";
            Airplane::state = ifrCMS;
            return;
        }
    }
    else if (Airplane::currentTask == "pushback") {

        if (Airplane::state == ifrCMS) {
            pushbackRequest(this, tijd);
            Airplane::state = pushbackRMS;
            return;
        }

        if (Airplane::state == pushbackRMS) {
            pushbackMessage(this, tijd);
            Airplane::state = pushbackMMS;
            return;
        }

        if (Airplane::state == pushbackMMS) {
            pushbackConfirmation(this, tijd);
            Airplane::state = pushbackCMS;
            if (Airplane::getSize() == "small"){
                Airplane::operationTime = kSmall;
            }
            else if (Airplane::getSize() == "medium"){
                Airplane::operationTime = kMedium;
            }
            else if (Airplane::getSize() == "large"){
                Airplane::operationTime = kLarge;
            }
            Airplane::currentTask = "request taxi";
            return;
        }
    }

    else if(Airplane::currentTask == "request taxi") {
        Airplane::state = taxiRequest;
        Airplane::currentTask = "going to runway";
        readyToTaxiMessage(this, tijd);
        return;
    }
}

void Airplane::taxiToRunway(){
    REQUIRE(Airplane::getCurrentTask() == "going to runway", "correct state");
    REQUIRE(Airplane::getAttemptRunway() != NULL, "destination runway was set");

    if (Airplane::gate != -1){
        Airplane::airport->setGateOccupied(Airplane::gate, false);
        Airplane::gate = -1;
    }

    //REQUIRE((!Airplane::onItsWay && !runw->getOnItsWay()) || (Airplane::onItsWay && runw->getOnItsWay()), "no plane on its way");

    const string &tijd = getTime();
    Airplane::taxiRoute = attemptRunway->getTaxiRoute();

    if (Airplane::taxiPoint.empty() && Airplane::taxiCrossing.empty()){
        Airplane::taxiPoint = Airplane::attemptRunway->getTaxiRoute()->getTaxiPoints()[0];
        Airplane::state = onTaxiPoint;
        Airplane::operationTime = 1;
        Airplane::attemptRunway->setOnItsWay(true);
        return;
    }

    if (!Airplane::taxiPoint.empty()){
        if (Airplane::taxiPoint == Airplane::taxiRoute->getTaxiPoints()[crossingIndex]){
            if (unsigned(crossingIndex) == Airplane::taxiRoute->getTaxiPoints().size()-1){
                if (Airplane::state == onTaxiPoint){
                    toRunwayMessage(this, attemptRunway, taxiPoint, tijd);
                    Airplane::state = taxiPointMMS;
                    Airplane::operationTime = 1;
                    return;
                }
                else if (Airplane::state == taxiPointMMS){
                    toRunwayConfirmation(this, attemptRunway, Airplane::taxiPoint, tijd);
                    Airplane::state = taxiPointCMS;
                    setOperationTime(1);
                    return;
                }
                else if (Airplane::state == taxiPointCMS){
                    Airplane::runway = attemptRunway;

                    Airplane::state = onHoldingPoint;

                    Airplane::currentTask = "at holding point";
                    attemptRunway->setOnItsWay(false);

                    Airplane::operationTime = 1;
                    attemptRunway->setHoldingShortOccupied(true);
                    runway = attemptRunway;
                    Airplane::attemptRunway = NULL;
                    return;
                }
            }
            else if (Airplane::state == onTaxiPoint){
                toHoldingPointMessage(this, taxiRoute->getTaxiCrossings()[crossingIndex], taxiPoint, tijd);
                Airplane::airport->getRunway(taxiRoute->getTaxiCrossings()[crossingIndex])->setHoldingShortOccupied(true);
                Airplane::state = taxiPointMMS;
                Airplane::operationTime = 1;
                return;
            }
            else if (Airplane::state == taxiPointMMS){
                toHoldingPointConfirmation(this, taxiRoute->getTaxiCrossings()[crossingIndex], taxiPoint, tijd);
                Airplane::state = taxiPointCMS;
                Airplane::operationTime = 1;
                return;
            }
            else if (Airplane::state == taxiPointCMS){
                Airplane::taxiPoint = "";
                Airplane::taxiCrossing = Airplane::taxiRoute->getTaxiCrossings()[crossingIndex];
                Airplane::state = onTaxiCrossing;
                Airplane::operationTime = 5;
                return;
            }
        }
    }
    else if (!Airplane::taxiCrossing.empty()){
        if (Airplane::taxiCrossing == Airplane::taxiRoute->getTaxiCrossings()[crossingIndex]){
            if (Airplane::state == onTaxiCrossing) {
                Airplane::airport->getRunway(taxiRoute->getTaxiCrossings()[crossingIndex])->setHoldingShortOccupied(true);
                clearedToCrossRequest(this, taxiRoute->getTaxiCrossings()[crossingIndex], tijd);
                Airplane::state = taxiCrossingRMS;
                Airplane::operationTime = 1;
                return;
            }
            else  if (Airplane::state == taxiCrossingRMS) {
                if (!Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->getPermissionToCross()){
                    holdingShortAtRunway(this, airport->getRunway(taxiRoute->getTaxiCrossings()[crossingIndex]), tijd);
                    Airplane::operationTime = 1;
                    Airplane::state = onTaxiCrossing;
                    return;
                }
                clearedToCrossMessage(this, Airplane::taxiRoute->getTaxiCrossings()[crossingIndex], tijd);
                Airplane::state = taxiCrossingMMS;
                Airplane::operationTime = 1;
                return;
            }
            else  if (Airplane::state == taxiCrossingMMS) {
                clearedToCrossConfirmation(Airplane::taxiRoute->getTaxiCrossings()[crossingIndex], tijd);
                Airplane::state = taxiCrossingCMS;
                Airplane::operationTime = 1;
                return;
            }
            else if (Airplane::state == taxiCrossingCMS) {
                if (Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->getPermissionToCross()) {
                    Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->setPermissionToCross(false);
                    Airplane::state = taxiCrossingNF;
                    Airplane::setOperationTime(1);
                    return;
                } else {
                    Airplane::state = onTaxiCrossing;
                    Airplane::setOperationTime(1);
                    return;
                }
            }
            else if (Airplane::state == taxiCrossingNF){
                Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->setPermissionToCross(true);
                Airplane::airport->getRunway(taxiRoute->getTaxiCrossings()[crossingIndex])->setHoldingShortOccupied(false);
                Airplane::setTaxiPoint(taxiRoute->getTaxiPoints()[crossingIndex+1]);
                Airplane::state = onTaxiPoint;
                Airplane::setOperationTime(5);
                Airplane::taxiCrossing = "";
                crossingIndex += 1;
                return;

            }
        }

    }
}

void Airplane::taxiToGate(int gate) {

    REQUIRE(Airplane::currentTask == "going to gate", "correct task");
    REQUIRE(Airplane::validGate(gate), "valid gate number");

    if(Airplane::state == onRunway) {

        if (gate == -1) {
            Airplane::attemptGate = Airplane::airport->getFreeGates()[0];
        }
        else{
            Airplane::attemptGate = gate;
        }

        Airplane::airport->setGateOccupied(Airplane::attemptGate, true);
    }

    const string &tijd = getTime();

    if (Airplane::runway != NULL){
        Airplane::taxiRoute = Airplane::runway->getTaxiRoute();
        Airplane::runway->setOccupied(false);
        Airplane::runway->setPermissionToCross(true);
        Airplane::runway = NULL;
    }

    if (Airplane::taxiPoint.empty() && Airplane::taxiCrossing.empty() && Airplane::taxiPoint != "at last point" ){
        Airplane::state = onTaxiPoint;
        Airplane::taxiPoint = Airplane::taxiRoute->getTaxiPoints()[Airplane::taxiRoute->getTaxiPoints().size()-1];
        crossingIndex = Airplane::taxiRoute->getTaxiPoints().size()-1;
        return;
    }

    if (!Airplane::taxiPoint.empty()){
        if (Airplane::taxiPoint == Airplane::taxiRoute->getTaxiPoints()[crossingIndex]){
            if (crossingIndex == 0){
                if (Airplane::state == onTaxiPoint){
                    toGateMessage(this, Airplane::attemptGate, Airplane::taxiPoint, tijd);
                    Airplane::state = taxiPointMMS;
                    return;
                }
                else if (Airplane::state == taxiPointMMS){
                    toGateConfirmation(this, Airplane::attemptGate, Airplane::taxiPoint, tijd);
                    Airplane::state = taxiPointCMS;
                    return;
                }
                else if (Airplane::state == taxiPointCMS){
                    Airplane::operationTime = 1;
                    Airplane::currentTask = "exit passengers";
                    Airplane::state = inGate;
                    Airplane::setGate(attemptGate);
                    return;
                }
            }

            else if (Airplane::state == onTaxiPoint) {
                toHoldingPointMessage(this, Airplane::taxiRoute->getTaxiCrossings()[crossingIndex-1], Airplane::taxiPoint, tijd);
                Airplane::state = taxiPointMMS;
                return;
            }
            else  if (Airplane::state == taxiPointMMS) {
                toHoldingPointConfirmation(this, Airplane::taxiRoute->getTaxiCrossings()[crossingIndex-1], Airplane::taxiPoint, tijd);
                Airplane::state = taxiPointCMS;
                return;
            }
            else  if (Airplane::state == taxiPointCMS) {
                Airplane::taxiPoint = "";
                Airplane::state = onTaxiCrossing;
                Airplane::crossingIndex -= 1;

                if (crossingIndex != 0) {
                    Airplane::taxiCrossing = taxiRoute->getTaxiCrossings()[crossingIndex - 1];
                    Airplane::setGate(attemptGate);
                }
                Airplane::setOperationTime(5);

                return;
            }
        }
    }
    else if (!Airplane::taxiCrossing.empty()){
        if (Airplane::taxiCrossing == Airplane::taxiRoute->getTaxiCrossings()[crossingIndex]){
            if (Airplane::state == onTaxiCrossing) {
                Airplane::airport->getRunway(taxiRoute->getTaxiCrossings()[crossingIndex])->setHoldingShortOccupied(true);
                clearedToCrossRequest(this, Airplane::taxiRoute->getTaxiCrossings()[crossingIndex], tijd);
                Airplane::state = taxiCrossingRMS;
                Airplane::operationTime = 1;
                return;
            }
            else  if (Airplane::state == taxiCrossingRMS) {
                if (!Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->getPermissionToCross()){
                    holdingShortAtRunway(this, airport->getRunway(taxiRoute->getTaxiCrossings()[crossingIndex]), tijd);
                    Airplane::operationTime = 1;
                    Airplane::state = onTaxiCrossing;
                    return;
                }
                else {
                    clearedToCrossMessage(this, Airplane::taxiRoute->getTaxiCrossings()[crossingIndex], tijd);
                    Airplane::state = taxiCrossingMMS;
                    Airplane::operationTime = 1;
                    return;
                }
            }
            else  if (Airplane::state == taxiCrossingMMS) {
                clearedToCrossConfirmation(Airplane::taxiRoute->getTaxiCrossings()[crossingIndex], tijd);
                Airplane::state = taxiCrossingCMS;
                Airplane::operationTime = 1;
                return;
            }

            else if (Airplane::state == taxiCrossingCMS){
                if (Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->getPermissionToCross()){
                    Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->setPermissionToCross(false);
                    Airplane::state = taxiCrossingNF;
                    Airplane::setOperationTime(1);
                    crossingIndex -= 1;
                    return;
                } else {
                    Airplane::state = onTaxiCrossing;
                    Airplane::setOperationTime(1);
                    return;
                }
            }


            else if (Airplane::state == taxiCrossingNF){
                Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->setPermissionToCross(true);
                Airplane::airport->getRunway(taxiRoute->getTaxiCrossings()[crossingIndex])->setHoldingShortOccupied(false);
                Airplane::setTaxiPoint(taxiRoute->getTaxiPoints()[crossingIndex-1]);
                Airplane::state = onTaxiPoint;
                Airplane::setOperationTime(5);
                Airplane::taxiCrossing = "";
                return;
            }
        }
    }
}

void Airplane::emergencyLanding(Airport* airport){

    REQUIRE(Airplane::currentTask == "emergency crash" || Airplane::currentTask == "emergency landing" || Airplane::currentTask == "crash", "correct state");

    const string &tijd = getTime();
    if(Airplane::currentTask != "emergency crash" || currentTask != "emergency landing") {

        if (Airplane::state == outOfFuel) {
            if (Airplane::height >= Airplane::kHeightLevelC) {
                EmergencyAbove3000ftRequest(this, airport, tijd);
                Airplane::state = iEmergencyRMS;
                if (Airplane::getEngine() == "jet") {
                    Airplane::setHeight(Airplane::getHeight()-Airplane::kJetDescentionSpeed);
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::setHeight(Airplane::getHeight()-Airplane::kProprellerDescentionSpeed);
                }
                Airplane::operationTime = 1;
                return;
            } else {
                EmergencyBelow3000ftRequest(this, airport, tijd);
                Airplane::state = oEmergencyRMS;
                if (Airplane::getEngine() == "jet") {
                    Airplane::setHeight(Airplane::getHeight()-Airplane::kJetDescentionSpeed);
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::setHeight(Airplane::getHeight()-Airplane::kProprellerDescentionSpeed);
                }
                Airplane::operationTime = 1;
                return;
            }
        } else {
            if (Airplane::state == iEmergencyRMS) {
                EmergencyAbove3000ftMessage(this, Airplane::runway, tijd);
                Airplane::runway = airport->getRunways()[airport->getFreeRunways()[0]];
                airport->getRunways()[airport->getFreeRunways()[0]]->setOccupied(true);
                airport->getRunways()[airport->getFreeRunways()[0]]->setPermissionToCross(false);
                Airplane::currentTask = "emergency landing";
                if (Airplane::getEngine() == "jet") {
                    Airplane::operationTime = Airplane::getHeight() / Airplane::kJetDescentionSpeed;
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::operationTime = Airplane::getHeight() / Airplane::kProprellerDescentionSpeed;
                }
                Airplane::setHeight(0);
                Airplane::state = iEmergencyMMS;
            } else if (Airplane::state == oEmergencyRMS) {
                EmergencyBelow3000ftMessage(this, tijd);
                Airplane::currentTask = "emergency crash";
                if (Airplane::getEngine() == "jet") {

                    Airplane::operationTime = Airplane::getHeight() / Airplane::kJetDescentionSpeed;
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::operationTime = Airplane::getHeight() / Airplane::kProprellerDescentionSpeed;
                }
                if (Airplane::getHeight() == 0){
                    Airplane::operationTime = 1;
                }
                Airplane::setHeight(0);
                Airplane::state = oEmergencyMMS;
            }
            return;
        }
    }
    else{
        if (Airplane::state == iEmergencyMMS){
            Airplane::runway->setPermissionToCross(true);
            Airplane::state = eLanded;
            Airplane::currentTask = "exit passengers";
            return;
        }
        else if (Airplane::state == oEmergencyMMS){
            Airplane::state = simulationIsFinished;
            Airplane::currentTask = "Finished";
            return;
        }

    }
}

void Airplane::land(Airport *airport) {
    cout << "height: " << Airplane::getHeight() << endl;
    REQUIRE(Airplane::getCurrentTask() == "try to land" || Airplane::getCurrentTask() == "landing"
            || Airplane::getCurrentTask() == "descending to 5000ft."  || Airplane::getCurrentTask() == "descending to 3000ft."
            || Airplane::getCurrentTask() == "descending to 0ft.", "correct task");
    REQUIRE(Airplane::getHeight() == 0 || Airplane::getHeight() == kHeightLevelA || Airplane::getHeight() == kHeightLevelB
            || Airplane::getHeight() == kHeightLevelC, "correct height");

    const string &tijd = getTime();
    if (Airplane::currentTask != "landing") {
        if (Airplane::state == incoming) {

            Airplane::state = descending;

            initialCommunicationMessage(this, airport, tijd);
            Airplane::operationTime = 1;
            return;
        }

        logMessage(Airplane::number + " is approaching " + airport->getName() + " at " + intToString(height) + "ft.");
        if (Airplane::height == Airplane::kHeightLevelA) {
            if (Airplane::state == descending) {

                if (permissionToDescend(Airplane::height, airport, runway)) {
                    descendTo5000ftMessage(this, tijd);
                    Airplane::state = descendARMS;
                    Airplane::operationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    Airplane::state = descendWait;
                    Airplane::operationTime = 1;
                    return;
                }
            } else {
                if (Airplane::state == descendWait) {
                    waitBeforeDescendConfirmation(this, tijd);
                    Airplane::operationTime = 1;

                } else if (Airplane::state == descendARMS){
                    descendTo5000ftConfirmation(this, tijd);
                    Airplane::currentTask = "descending to 5000ft.";
                    airport->setWait5000(this);

                    if (Airplane::getEngine() == "jet") {
                        Airplane::operationTime = (Airplane::kHeightLevelA - Airplane::kHeightLevelB)/Airplane::kJetDescentionSpeed +1;

                    } else if (Airplane::getEngine() == "propeller") {
                        Airplane::operationTime = (Airplane::kHeightLevelA - Airplane::kHeightLevelB)/Airplane::kProprellerDescentionSpeed +1;

                    }
                }
                Airplane::state = descending;
                return;
            }
        }

        else if (Airplane::height == Airplane::kHeightLevelB) {
            if (Airplane::state == descending) {

                if (permissionToDescend(Airplane::height, airport, runway)) {
                    descendTo3000ftMessage(this, tijd);
                    Airplane::state = descendBRMS;
                    Airplane::operationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    Airplane::state = descendWait;
                    Airplane::operationTime = 1;
                    return;
                }
            } else {
                if (Airplane::state == descendWait) {
                    waitBeforeDescendConfirmation(this, tijd);
                    logMessage(Airplane::number + " is waiting at a height of " + intToString(height));
                    Airplane::operationTime = 1;
                    return;
                } else if (Airplane::state == descendBRMS){
                    descendTo3000ftConfirmation(this, tijd);
                    Airplane::currentTask = "descending to 3000ft.";

                    if (Airplane::getEngine() == "jet") {
                        Airplane::operationTime = (Airplane::kHeightLevelB - Airplane::kHeightLevelC)/Airplane::kProprellerDescentionSpeed -1;
                    } else if (Airplane::getEngine() == "propeller") {
                        Airplane::operationTime = (Airplane::kHeightLevelB - Airplane::kHeightLevelC) /
                                                  Airplane::kProprellerDescentionSpeed - 1;
                    }
                }
                Airplane::state = descending;
                return;
            }

            return;
        }

        else if (Airplane::height == Airplane::kHeightLevelC) {
            if (Airplane::state == descending) {

                if (attemptRunway == NULL) {
                    logMessage("Preparing airplane (" + Airplane::number + ") for landing in " + airport->getName());

                    vector<Runway*> runways = airport->getRunways();

                    for (unsigned int i = 0; i < runways.size(); i++) {
                        if (!runways[i]->isOccupied()) {
                            if (validRunway(runways[i])) {
                                Airplane::attemptRunway = runways[i];
                                break;

                            }
                        }
                    }

                }

                if (permissionToDescend(Airplane::height, airport, attemptRunway)) {
                    finalApproachMessage(this, attemptRunway, tijd);
                    attemptRunway->setOccupied(true);
                    attemptRunway->setPermissionToCross(false);
                    Airplane::state = descendCRMS;
                    Airplane::operationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    Airplane::state = descendWait;
                    Airplane::operationTime = 1;
                    return;
                }
            } else if (Airplane::state == descendWait) {
                    waitBeforeDescendConfirmation(this, tijd);
                    logMessage(Airplane::number + " is waiting at a height of " + intToString(Airplane::height));
                    Airplane::state = descending;
                    Airplane::operationTime = 1;
                    return;
            } else if (Airplane::state == descendCRMS){
                finalApproachConfirmation(this, attemptRunway, tijd);
                Airplane::state = onFinalApproach;
                Airplane::currentTask = "descending to 0ft.";
                if (Airplane::getEngine() == "jet") {
                    Airplane::operationTime = 1+Airplane::kHeightLevelC/Airplane::kJetDescentionSpeed;
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::operationTime = Airplane::kHeightLevelC/Airplane::kProprellerDescentionSpeed;
                }
                return;
            }

        } else if (Airplane::height == 0){
            Airplane::currentTask = "landing";
            Airplane::operationTime = 2;

            logMessage(Airplane::number + " is landing at Runway" + attemptRunway->getName());
            Airplane::setAirport(airport);
            logMessage("Airplane (" + Airplane::number + ") landed in " + airport->getIata());

            Airplane::setRunway(attemptRunway);
            logMessage("Airplane (" + Airplane::number + ") is now at runway " + runway->getName() + "\n");

            Airplane::state = landing;
            return;
        }
        return;
    }
    else {

        afterLandingMessage(this, Airplane::airport, Airplane::runway, tijd);
        Airplane::currentTask = "going to gate";
        Airplane::state = onRunway;
        Airplane::operationTime = 1;
        Airplane::attemptRunway = NULL;
        return;
    }

    ENSURE( Airplane::getState() == onRunway || Airplane::getRunway() != NULL, "Landed");
}

void Airplane::takeOff() {
    REQUIRE(Airplane::getCurrentTask() == "taking off" || Airplane::getCurrentTask() == "at holding point", "correct state");
    REQUIRE(Airplane::getHeight() == 0, "Plane not on ground");
    REQUIRE(Airplane::getRunway() != NULL, "at Runway");
    REQUIRE(Airplane::getAirport() != NULL, "at Airport");

    const string &tijd = getTime();

    if (Airplane::currentTask == "at holding point") {
        if (Airplane::state == onHoldingPoint) {
            holdingShortAtRunway(this, Airplane::runway, tijd);
            Airplane::state = holdingPointRMS;
            Airplane::setOperationTime(1);
            return;
        }

        if (Airplane::state == holdingPointRMS) {
            if (!Airplane::runway->isOccupied() && !Airplane::runway->getWaitingOnRunway() && !Airplane::runway->getHoldingShortOccupied() && !Airplane::runway->getCrossing()) {
                clearedForTakeOffMessage(this, Airplane::runway, tijd);
                Airplane::permissionToTakeOff = true;
                Airplane::state = holdingPointMMS;
                Airplane::runway->setWaitingOnRunway(true);
                Airplane::runway->setOccupied(true);
                Airplane::runway->setPermissionToCross(false);
                Airplane::runway->setHoldingShortOccupied(false);
                setOperationTime(1);
                return;
            } else if (!Airplane::runway->isOccupied() && !Airplane::runway->getWaitingOnRunway() && Airplane::runway->getHoldingShortOccupied() && !Airplane::runway->getCrossing() && Airplane::waitAtRunway) {
                clearedForTakeOffMessage(this, Airplane::runway, tijd);
                Airplane::permissionToTakeOff = true;
                Airplane::state = holdingPointMMS;
                Airplane::runway->setWaitingOnRunway(true);
                Airplane::runway->setOccupied(true);
                Airplane::runway->setPermissionToCross(false);
                Airplane::runway->setHoldingShortOccupied(false);
                setOperationTime(1);
                return;
            } else if (!Airplane::runway->isOccupied() && !Airplane::runway->getWaitingOnRunway() && !Airplane::runway->getHoldingShortOccupied() && Airplane::runway->getCrossing()) {
                lineUpRunwayMessage(this, Airplane::runway, tijd);
                Airplane::state = holdingPointMMS;
                Airplane::waitOnRunway = true;
                Airplane::runway->setWaitingOnRunway(true);
                Airplane::runway->setOccupied(true);
                Airplane::runway->setHoldingShortOccupied(false);
                setOperationTime(1);
                return;
            } else if (!Airplane::runway->isOccupied() && !Airplane::runway->getWaitingOnRunway() && Airplane::runway->getHoldingShortOccupied() && Airplane::runway->getCrossing() && Airplane::waitAtRunway) {
                lineUpRunwayMessage(this, Airplane::runway, tijd);
                Airplane::state = holdingPointMMS;
                Airplane::waitOnRunway = true;
                Airplane::waitAtRunway = false;
                Airplane::runway->setWaitingOnRunway(true);
                Airplane::runway->setOccupied(true);
                Airplane::runway->setHoldingShortOccupied(false);
                Airplane::setOperationTime(1);
                return;
            } else if (!Airplane::runway->getHoldingShortOccupied() || (Airplane::runway->getHoldingShortOccupied() && Airplane::waitAtRunway)) {
                waitAtRunwayMessage(this, tijd);
                Airplane::state = holdingPointMMS;
                Airplane::waitAtRunway = true;
                Airplane::runway->setHoldingShortOccupied(true);
                Airplane::setOperationTime(1);
                return;
            }
        }
        else if (Airplane::state == holdingPointMMS) {
            if (Airplane::permissionToTakeOff) {
                clearedForTakeOffConfirmation(this, Airplane::runway, tijd);
                Airplane::permissionToTakeOff = false;
                Airplane::currentTask == "taking off";
                Airplane::state = holdingpointCMS;
                if(!Airplane::alreadyLinedUp){
                    Airplane::setOperationTime(2);;
                }
                else{
                    Airplane::setOperationTime(1);
                }
                Airplane::alreadyLinedUp = false;
                Airplane::runway->setHoldingShortOccupied(false);
                return;
            }
            if (Airplane::waitOnRunway) {
                lineUpRunwayConfirmation(this, Airplane::runway, tijd);
                Airplane::alreadyLinedUp = true;
                Airplane::state = onHoldingPoint;
                Airplane::waitOnRunway = true;
                Airplane::setOperationTime(1);
                Airplane::runway->setHoldingShortOccupied(false);
                return;
            }
            if (Airplane::waitAtRunway) {
                waitAtRunwayConfirmation(this, tijd);
                Airplane::state = onHoldingPoint;
                Airplane::waitAtRunway = true;
                setOperationTime(1);
                return;
            }
        }
    }

    logMessage("Sending airplane " + Airplane::getNumber() + " for departure");

    logMessage("Airplane (" + Airplane::getNumber() + ") is taking off at " + Airplane::getAirport()->getName());

    Airplane::runway->setOccupied(false);
    Airplane::runway->setWaitingOnRunway(false);
    Airplane::runway->setPermissionToCross(true);
    Airplane::waitOnRunway = false;


    Airplane::state = ascending;

    if (Airplane::getEngine() == "propeller"){
        Airplane::operationTime = Airplane::kHeightLevelC;
        Airplane::height = Airplane::kProprellerAscentionSpeed;
    }
    else {
        Airplane::operationTime = Airplane::kHeightLevelC;
        Airplane::height = Airplane::kJetAscentionSpeed;
    }

    Airplane::operationTime = kHeightLevelA;
    Airplane::currentTask = "taking off";
    Airplane::setSimulationFinished(true);

    ENSURE(Airplane::getState() == ascending

           && Airplane::getHeight() != 0, "Airborne");

}

void Airplane::exitPlane(){
    REQUIRE(Airplane::getCurrentTask() == "exit passengers" , "correct task");
    REQUIRE(Airplane::atGate(), "at gate");
    Airplane::setTaxiPoint("");
    Airplane::setTaxiCrossing("");
    if (Airplane::passengers <= 0) {

        Airplane::passengers = 0;

        logMessage(intToString(Airplane::passengerCapacity) + " passengers exited " + Airplane::callsign + " at gate "
                   + intToString(Airplane::gate) + " of " + Airplane::airport->getName());

        if(Airplane::state == eUnboardingPassengers){
            Airplane::state = eTechnicalCheck;
        }
        else if(Airplane::state == gUnboardingPassengers){
            Airplane::state = gTechnicalCheck;

        }
        Airplane::currentTask = "technical check";
        return;
    }
    else {
        if (Airplane::state == eLanded){
            Airplane::state = eUnboardingPassengers;
        }
        else if (Airplane::state == inGate){
            Airplane::state = gUnboardingPassengers;
        }

        if (Airplane::size == "small"){
            Airplane::operationTime = kSmall*Airplane::kBoardingExitingTime;
            Airplane::passengers -= Airplane::passengerCapacity/(kSmall*Airplane::kBoardingExitingTime);
        }
        else if (size == "medium"){
                Airplane::operationTime = kMedium*Airplane::kBoardingExitingTime;
                Airplane::passengers -= Airplane::passengerCapacity/(kMedium*Airplane::kBoardingExitingTime);
        }
        else {
            Airplane::operationTime = kLarge*Airplane::kBoardingExitingTime;
            Airplane::passengers -= Airplane::passengerCapacity/(kLarge*Airplane::kBoardingExitingTime);
        }
    }
}

void Airplane::enterPlane(){
    REQUIRE(Airplane::getCurrentTask() == "board passengers", "correct state");
    REQUIRE(Airplane::atGate(), "at gate");


    if (Airplane::passengers >= Airplane::passengerCapacity) {

        Airplane::passengers = Airplane::passengerCapacity;

        logMessage(intToString(Airplane::passengerCapacity) + " passengers entered " + Airplane::callsign + " at gate "
                            + intToString(Airplane::gate) + " of " + Airplane::airport->getName());

        Airplane::state = ifr;
        Airplane::currentTask = "IFR";
        return;
    }else{
        if (Airplane::size == "small"){
            Airplane::operationTime = kSmall*Airplane::kBoardingExitingTime;
            Airplane::passengers += Airplane::passengerCapacity / (kSmall*Airplane::kBoardingExitingTime);
        }else {
            if (Airplane::size == "medium"){
                Airplane::operationTime = kMedium*Airplane::kBoardingExitingTime;
                Airplane::passengers += Airplane::passengerCapacity / (kMedium*Airplane::kBoardingExitingTime);

            }else{
                Airplane::operationTime = kLarge*Airplane::kBoardingExitingTime;
                Airplane::passengers += Airplane::passengerCapacity / (kLarge*Airplane::kBoardingExitingTime);

            }
        }
    }
}

void Airplane::technicalCheck(){
    REQUIRE(Airplane::getCurrentTask() == "technical check", "correct state");
    REQUIRE(Airplane::atGate(), "at gate");


    if (!Airplane::technicalChecked && Airplane::size != "small"){
        if (Airplane::getSize() == "medium") {
            Airplane::operationTime = kMedium-1;
        }
        else if (Airplane::getSize() == "large") {
            Airplane::operationTime = kLarge-1;
        }
        Airplane::technicalChecked = true;
        return;
    }
    Airplane::technicalChecked = false;
    logMessage(getNumber() + " has been checked for technical malfunction");
    if (Airplane::state == eTechnicalCheck){
        Airplane::state = eRefuel;
        Airplane::setOperationTime(ceil((Airplane::fuelCapacity - Airplane::fuel)/ Airplane::kFuelPerMinute));
        Airplane::currentTask = "refueling";
        return;

    }
    else if (Airplane::state == gTechnicalCheck){
        Airplane::state = gRefuel;
        Airplane::setOperationTime(ceil((Airplane::fuelCapacity - Airplane::fuel)/ Airplane::kFuelPerMinute));
        Airplane::currentTask = "refueling";
        return;

    }
}

void Airplane::refuel() {
    REQUIRE(Airplane::getCurrentTask() == "refueling", "correct state");
    REQUIRE(atGate(), "at gate");
    REQUIRE(Airplane::flightPlan != NULL, "flightplan assigned");


    logMessage(getNumber() + " has been refueled");

    if (Airplane::state == eRefuel) {
        Airplane::currentTask = "taxi to gate";
        Airplane::state = onRunway;
    }

    else {
        Airplane::state = boardPassengers;

        // << getTimePassed() << ", " << flightPlan->getDeparture() << endl;
        if (getTimePassed() > Airplane::flightPlan->getDeparture()) { ;
            Airplane::currentTask = "board passengers";

        }else{
            Airplane::currentTask = "idle";
            Airplane::operationTime = Airplane::flightPlan->getDeparture() - getTimePassed();
        }

    }
    Airplane::setFuel(Airplane::getFuelCapacity());
}

void Airplane::useFuel(){
    if (Airplane::size == "small"){
        if (Airplane::engine == "propeller"){
            Airplane::fuel -= 10;
        }
        else if (Airplane::engine == "jet"){
            Airplane::fuel -= 25;
        }
    }
    else if (Airplane::size == "medium"){
        if (Airplane::engine == "propeller"){
            Airplane::fuel -= 50;
        }
        else if (Airplane::engine == "jet"){
            Airplane::fuel -= 175;
        }
    }
    else if (Airplane::size == "large"){
        if (Airplane::engine == "propeller"){
            Airplane::fuel -= 100;
        }
        else if (Airplane::engine == "jet"){
            Airplane::fuel -= 250;
        }
    }
}

void Airplane::descend(Airport * airport) {

    if (Airplane::engine == "jet"){
        Airplane::height -= Airplane::kJetDescentionSpeed;


    }else{
        Airplane::height -= Airplane::kProprellerDescentionSpeed;

    }

    logMessage(Airplane::number + " is approaching " + airport->getName() + " at " + intToString(height) + "ft.");

}

void Airplane::ascend(Airport* airport) {

    if (Airplane::engine == "jet"){
        Airplane::height += Airplane::kJetAscentionSpeed;

    }
    else {
        Airplane::height += Airplane::kProprellerAscentionSpeed;

    }

    if (Airplane::height >= Airplane::kHeightLevelB){
        Airplane::state = simulationIsFinished;
        Airplane::currentTask = "finished";
        Airplane::setAirport(NULL);
        Airplane::setRunway(NULL);
    }

    logMessage(Airplane::number + " is leaving " + airport->getName() + " at " + intToString(Airplane::height) + "ft.");

}


//simulation
void Airplane::initSimulation(Airport *airport) {
    Airplane::setSimulationFinished(false);
    Airplane::waitOnRunway = false;
    Airplane::waitAtRunway = false;
    Airplane::technicalChecked = false;
    Airplane::alreadyLinedUp = false;

    Airplane::setSquawkCode();

    for (unsigned int i = 0; i < airport->getRunways().size(); i++) {
        airport->getRunways()[i]->setPermissionToCross(true);
        airport->getRunways()[i]->setOnItsWay(false);
        airport->getRunways()[i]->setWaitingOnRunway(false);
        airport->getRunways()[i]->setHoldingShortOccupied(false);
    }
    if (Airplane::flightPlan != NULL) {
        if (Airplane::getState() == incoming) {
            Airplane::setHeight(Airplane::kHeightLevelA);
            Airplane::operationTime = Airplane::flightPlan->getArrival();
            Airplane::currentTask = "try to land";


        }

        if (Airplane::getState() == gTechnicalCheck) {

            Airplane::setHeight(0);
            Airplane::setFuel(0);
            Airplane::setPassengers(0);

            Airplane::operationTime = Airplane::flightPlan->getDeparture();
            Airplane::currentTask = "technical check";

            Airplane::setAirport(airport);
            Airplane::setGate(airport->getFreeGates()[0]);
            airport->setGateOccupied(airport->getFreeGates()[0], true);

        }
    }else{
        Airplane::currentTask = "finished";

    }

}

void Airplane::execTask(Airport* airport) {
    Airplane::operationTime -= 1;
    if (Airplane::currentTask == "try to land" || Airplane::currentTask == "descending to 5000ft." || Airplane::currentTask == "descending to 3000ft." || Airplane::currentTask == "descending to 0ft." || Airplane::currentTask == "landing"){
        Airplane::land(airport);
    } else if (Airplane::currentTask == "emergency crash" || Airplane::currentTask == "emergency landing" || Airplane::currentTask == "crash"){
        emergencyLanding(airport);
    } else if(Airplane::currentTask == "IFR" || Airplane::currentTask == "pushback" || Airplane::currentTask == "request taxi"){
        Airplane::pushBack();
    } else if(Airplane::currentTask == "going to runway"){
        Airplane::taxiToRunway();
    } else if(Airplane::currentTask == "going to gate"){
        Airplane::taxiToGate();
    } else if(Airplane::currentTask == "taking off" || Airplane::currentTask == "at holding point"){
        Airplane::takeOff();
    } else if(Airplane::currentTask == "exit passengers"){
        Airplane::exitPlane();
    } else if(Airplane::currentTask == "board passengers"){
        Airplane::enterPlane();
    } else if(Airplane::currentTask == "technical check"){
        Airplane::technicalCheck();
    } else if(Airplane::currentTask == "refueling"){
        Airplane::refuel();
    }else if (Airplane::currentTask == "idle"){
        Airplane::currentTask = "board passengers";
    }
}

bool Airplane::notFinished() {
    return (Airplane::state != simulationIsFinished );

}

void Airplane::continueTask(Airport * airport) {

    if (Airplane::currentTask == "refueling"){
        if (Airplane::fuel + Airplane::kFuelPerMinute < Airplane::fuelCapacity) {
            Airplane::fuel += Airplane::kFuelPerMinute;

        }else{
            Airplane::fuel = Airplane::fuelCapacity;
            Airplane::operationTime = 1;

        }
        return;
    }

    if (Airplane::currentTask == "board passengers"){
        if (Airplane::size == "small") {
            if (Airplane::passengers + Airplane::passengerCapacity / (kSmall*Airplane::kBoardingExitingTime) <= Airplane::passengerCapacity) {
                Airplane::passengers += Airplane::passengerCapacity / (kSmall*Airplane::kBoardingExitingTime);
                return;
            }


        }else if (size == "medium"){
            if (Airplane::passengers + Airplane::passengerCapacity / (kMedium*Airplane::kBoardingExitingTime) <= Airplane::passengerCapacity) {
                Airplane::passengers += Airplane::passengerCapacity / (kMedium*Airplane::kBoardingExitingTime);
                return;
            }


        }else if (Airplane::size == "large"){
            if (Airplane::passengers + Airplane::passengerCapacity/(kLarge*Airplane::kBoardingExitingTime) <= Airplane::passengerCapacity) {
                Airplane::passengers += Airplane::passengerCapacity / (kLarge*Airplane::kBoardingExitingTime);
                return;
            }

        }
        Airplane::passengers = Airplane::passengerCapacity;
        Airplane::operationTime = 1;
    }

    if (Airplane::currentTask == "exit passengers"){
        if (Airplane::size == "small") {
            if (Airplane::passengers - Airplane::passengerCapacity / (kSmall*Airplane::kBoardingExitingTime) >= 0) {
                Airplane::passengers -= Airplane::passengerCapacity / (kSmall*Airplane::kBoardingExitingTime);
                return;
            }


        }else if (size == "medium"){
            if (Airplane::passengers - Airplane::passengerCapacity / (kMedium*Airplane::kBoardingExitingTime) >= 0) {
                Airplane::passengers -= Airplane::passengerCapacity / (kMedium*Airplane::kBoardingExitingTime);
            }


        }else if (size == "large"){
            if (Airplane::passengers - Airplane::passengerCapacity/(kLarge*Airplane::kBoardingExitingTime) >= 0) {
                Airplane::passengers -= Airplane::passengerCapacity / (kLarge*Airplane::kBoardingExitingTime);
                return;
            }

        }
        Airplane::passengers = 0;
        Airplane::operationTime = 1;

    }


    if (Airplane::currentTask == "taking off"){
        Airplane::ascend(airport);

    }

    if (Airplane::currentTask == "descending to 5000ft." || Airplane::currentTask == "descending to 3000ft." || Airplane::currentTask == "descending to 0ft."){
        Airplane::descend(airport);

    }



}


//Output

string Airplane::getInfo() {
    string str;
    str = "\nAirplane:\t" + Airplane::callsign + " (" + Airplane::number +  ")\n"
          + "->model:\t" + Airplane::model +"\n"
          + "->type:\t" + Airplane::type + "\n"
          + "->engine:\t" + Airplane::engine + "\n"
          + "->size:\t" + Airplane::size + "\n";

    return str;
}

int Airplane::getAttemptGate() const {
    return Airplane::attemptGate;
}
void Airplane::setAttemptGate(int attemptGate) {
    Airplane::attemptGate = attemptGate;
    ENSURE(Airplane::getAttemptGate() == attemptGate, "attempt gate set");
}

bool Airplane::isAlreadyLinedUp() const {
    return Airplane::alreadyLinedUp;
}
void Airplane::setAlreadyLinedUp(bool alreadyLinedUp) {
    Airplane::alreadyLinedUp = alreadyLinedUp;
    ENSURE(Airplane::alreadyLinedUp == alreadyLinedUp, "technicalChecked set");
}

bool Airplane::isPermissionToTakeOff() const {
    return Airplane::permissionToTakeOff;
}
void Airplane::setPermissionToTakeOff(bool permissionToTakeOff) {
    Airplane::permissionToTakeOff = permissionToTakeOff;
    ENSURE(Airplane::permissionToTakeOff == permissionToTakeOff, "technicalChecked set");
}

bool Airplane::isWaitAtRunway() const {
    return Airplane::waitAtRunway;
}
void Airplane::setWaitAtRunway(bool waitAtRunway) {
    Airplane::waitAtRunway = waitAtRunway;
    ENSURE(Airplane::waitAtRunway == waitAtRunway, "technicalChecked set");
}

bool Airplane::isWaitOnRunway() const {
    return Airplane::waitOnRunway;
}
void Airplane::setWaitOnRunway(bool waitOnRunway) {
    Airplane::waitOnRunway = waitOnRunway;
    ENSURE(Airplane::waitOnRunway == waitOnRunway, "technicalChecked set");
}

Airplane::~Airplane() {

}


/// Validation Functions

// Militairy airplanes
bool AirplaneMilitairy::validEngineType(string type) {

    if (AirplaneMilitairy::getSize() == "small"){
        return type == "jet";
    }else{
        if (AirplaneMilitairy::getSize() == "large") {
            return type == "propeller";
        }else{
            return true;

        }
    }

}

bool AirplaneMilitairy::validSize(string size) {

    if (AirplaneMilitairy::getEngine() == "jet"){
        return size == "small";
    }
    else{
        if (AirplaneMilitairy::getEngine() == "propeller") {
            return size == "large";

        }else{
            return size != "medium";

        }
    }

}

bool AirplaneMilitairy::validRunway(Runway *runway) {
    return Airplane::validRunway(runway);
}

AirplaneMilitairy::AirplaneMilitairy() : Airplane("militairy") {
}


// Private airplanes
bool AirplanePrivate::validEngineType(string type) {

    if (AirplanePrivate::getSize() == "medium"){
        return type == "jet";

    }
    else{
        return true;

    }

}

bool AirplanePrivate::validSize(string size) {

    if (AirplanePrivate::getEngine() == "propeller"){
        return size == "small";
    }
    else{
        return size != "large";
    }

}

bool AirplanePrivate::validRunway(Runway *runway) {
    return Airplane::validRunway(runway);
}

AirplanePrivate::AirplanePrivate() : Airplane("private") {
}


// Airline airplanes
bool AirplaneAirline::validEngineType(string type) {

    if (AirplaneAirline::getSize() == "large"){
        return type == "jet";
    }
    else{

        return true;
    }

}

bool AirplaneAirline::validSize(string size) {

    if (AirplaneAirline::getEngine() == "propeller"){
        return size == "medium";
    }
    else{
        return size != "small";
    }

}

bool AirplaneAirline::validRunway(Runway *runway) {
    return Airplane::validRunway(runway);
}

AirplaneAirline::AirplaneAirline() : Airplane("airline") {

}


// Emergency airplanes
bool AirplaneEmergency::validEngineType(string type) {

    return type == "propeller";

}

bool AirplaneEmergency::validSize(string size) {

    return size == "small";

}

bool AirplaneEmergency::validRunway(Runway *runway) {
    return Airplane::validRunway(runway);
}

AirplaneEmergency::AirplaneEmergency() : Airplane("emergency") {

}
