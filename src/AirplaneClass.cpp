//
// Created by oliviervh on 01.03.18.
//

#include "AirplaneClass.h"
#include <string>
#include <cstdlib>

string gTime;
int gTimePassed;
int gStartingTime;


Airplane::Airplane() {
    Airplane::self = this;
    Airplane::number = "";
    Airplane::callsign = "";
    Airplane::model = "";
    Airplane::state = "";
    Airplane::type = "";
    Airplane::engine = "";
    Airplane::size = "";
    Airplane::squawkCode = "";
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
    Airplane::currentTask = "";
    Airplane::flightPlan = NULL;
    Airplane::taxiRoute = NULL;
    Airplane::taxiPoint = "";
    Airplane::taxiCrossing = "";
    Airplane::technicalChecked = false;
    Airplane::ifrAuthorized = false;
    Airplane::pushback = false;
    Airplane::requestMessageSend = false;
    Airplane::messageMessageSend = false;
    Airplane::confirmMessageSend = false;
    Airplane::taxiRequest = false;
    Airplane::emergencyInAirport = false;
    Airplane::crossed = false;
    Airplane::alreadyLinedUp = false;
    Airplane::permissionToTakeOff = false;
    Airplane::waitAtRunway = false;
    Airplane::waitOnRunway = false;
    Airplane::onItsWay = false;
    Airplane::simulationFinished = false;

}

//getters & setters

bool Airplane::getTechnicalChecked() const{
    return Airplane::technicalChecked;
}
void Airplane::setTechnicalChecked(bool boolean) {
    Airplane::technicalChecked = boolean;
    ENSURE(Airplane::technicalChecked == boolean, "technicalChecked set");

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

const string &Airplane::getState() const {
    return Airplane::state;
}
void Airplane::setState(const string &state) {
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
void Airplane::setType(const string &type) {
    REQUIRE(Airplane::validPlaneType(type), "Valid type?");
    Airplane::type = type;
    ENSURE( Airplane::type == type, "type set");
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
    if (gate != -1){
        REQUIRE(Airplane::atAirport(), "at Airport");
    }
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

bool Airplane::isIFRAuthorized() const {
    return Airplane::ifrAuthorized;
}
void Airplane::setIFRAuthorized(bool ifrAuthorized) {
    Airplane::ifrAuthorized = ifrAuthorized;
    ENSURE(Airplane::ifrAuthorized == ifrAuthorized , "IFR authorized set");
}

bool Airplane::isPushback() const {
    return Airplane::pushback;
}
void Airplane::setPushback(bool pushback) {
    Airplane::pushback = pushback;
    ENSURE(Airplane::pushback == pushback , "pushback set");
}

bool Airplane::isRequestMessageSend() const {
    return Airplane::requestMessageSend;
}
void Airplane::setRequestMessageSend(bool requestMessageSend) {
    Airplane::requestMessageSend = requestMessageSend;
    ENSURE(Airplane::requestMessageSend == requestMessageSend , "request message send set");
}

bool Airplane::isMessageMessageSend() const {
    return Airplane::messageMessageSend;
}
void Airplane::setMessageMessageSend(bool messageMessageSend) {
    Airplane::messageMessageSend = messageMessageSend;
    ENSURE(Airplane::messageMessageSend == messageMessageSend , "message send set");
}

bool Airplane::isConfirmMessageSend() const {
    return confirmMessageSend;
}
void Airplane::setConfirmMessageSend(bool confirmMessageSend) {
    Airplane::confirmMessageSend = confirmMessageSend;
    ENSURE(Airplane::confirmMessageSend == confirmMessageSend , "confirm message send set");
}

bool Airplane::isTaxiRequest() const {
    return Airplane::taxiRequest;
}
void Airplane::setTaxiRequest(bool taxiRequest) {
    Airplane::taxiRequest = taxiRequest;
    ENSURE(Airplane::taxiRequest == taxiRequest , "taxi request set");
}

bool Airplane::getEmergencyInAirport() const {
    return Airplane::emergencyInAirport;
}
void Airplane::setEmergencyInAirport(bool emergencyInAirport) {
    Airplane::emergencyInAirport = emergencyInAirport;
    ENSURE(Airplane::emergencyInAirport == emergencyInAirport, "emergency in airport set");
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
            int randNumb = rand() % 776 + 1;
            Airplane::squawkCode = intToString(randNumb);

        }else{
            int randNumb = rand() % 777;
            int code = 1000*index + randNumb;
            Airplane::squawkCode = intToString(code);

        }

    }else{
        Airplane::squawkCode = intToString(code);

    }

    ENSURE(!Airplane::getSquawkCode().empty() , "squawkCode set");
}
const string &Airplane::getSquawkCode() const {
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

void Airplane::setVar(const string &type, const string &value) {

    if (type == "number"){
        Airplane::setNumber(value);
        return ;
    }

    else if (type == "model"){
        Airplane::setModel(value);
        return;
    }

    else if (type == "callsign"){
        Airplane::setCallsign(value);
        return;
    }

    else if (type == "status"){
        if (value == "Gate" || value == "Approaching" ) {
            Airplane::setState(value);
        }
        return;
    }

    else if (type == "type"){
        if (Airplane::validPlaneType(value)){
            Airplane::setType(value);
        }
        return;
    }

    else if (type == "engine"){
        if (Airplane::validEngineType(value)) {
            Airplane::setEngine(value);
            return;
        }
    }

    else if (type == "size"){
        if (Airplane::validSize(value)) {
            Airplane::setSize(value);
            return;
        }
    }

    else if (type == "passengers"){
        if (isNumber(value)) {
            int i;
            istringstream(value) >> i;
            Airplane::setPassengers(i);
            Airplane::setPassengerCapacity(i);
        }
        return;
    }

    else if (type == "height"){
        if (isNumber(value)) {
            int i;
            istringstream(value) >> i;
            Airplane::setHeight(i);
        }
        return;
    }

    else if (type == "fuel"){
        if (isNumber(value)) {
            int i;
            istringstream(value) >> i;
            Airplane::setFuel(i);
            Airplane::setFuelCapacity(i);
        }
        return;
    }

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

    if (runway == NULL){
        vector<int> runway = airport->getFreeRunways();
        for (int i = 0; (unsigned)i<runway.size(); i++){
            Runway *runway = airport->getRunways()[i];
            if (Airplane::size == "small"){
                if (Airplane::engine == "propeller"){
                    if (runway->getLength() >= 500){
                        return true;
                    }
                    continue;
                }
                else if (Airplane::engine == "jet"){
                    if (runway->getLength() >= 1000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (Airplane::size == "medium"){
                if (getEngine()== "propeller"){
                    if (runway->getLength() >= 1000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (Airplane::engine == "jet"){
                    if (runway->getLength() >= 2000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (Airplane::size  == "large"){
                if (Airplane::engine == "propeller"){
                    if (runway->getLength() >= 1500 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (Airplane::engine == "jet"){
                    if (runway->getLength() >= kHeightLevelC && runway->getType() == "asphalt"){
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
            if (runway->getLength() >= 500 && !runway->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
        else if (Airplane::engine == "jet"){
            if (runway->getLength() >= 1000 && runway->getType() == "asphalt" && !runway->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (Airplane::size == "medium"){
        if (Airplane::engine == "propeller"){
            if (runway->getLength() >= 1000 && runway->getType() == "asphalt" && !runway->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
        else if (Airplane::engine == "jet"){
            if (runway->getLength() >= 2000 && runway->getType() == "asphalt" && !runway->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (Airplane::size  == "large"){
        if (Airplane::engine == "propeller"){
            if (runway->getLength() >= 1500 && runway->getType() == "asphalt" && !runway->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
        else if (Airplane::engine == "jet"){
            if (runway->getLength() >= kHeightLevelC && runway->getType() == "asphalt" && !runway->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
    }
    return false;
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
        vector<int> runway = Airplane::airport->getFreeRunways();
        for (int i = 0; (unsigned)i<runway.size(); i++){
            Runway *runway = Airplane::airport->getRunways()[i];
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
                    if (runway->getLength() >= kHeightLevelC && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
        }
        return false;
    }
    else if (!runway->isOccupied()) {
        if (Airplane::size == "small") {
            if (Airplane::engine == "propeller") {
                if (runway->getLength() >= kRunwayLengthA) {
                    return true;
                } else {
                    return false;
                }
            } else if (Airplane::engine == "jet") {
                if (runway->getLength() >= kRunwayLengthB && runway->getType() == "asphalt") {
                    return true;
                } else {
                    return false;
                }
            }
        } else if (Airplane::size == "medium") {
            if (Airplane::engine == "propeller") {
                if (runway->getLength() >= kRunwayLengthB && runway->getType() == "asphalt") {
                    return true;
                } else {
                    return false;
                }
            } else if (Airplane::engine == "jet") {
                if (runway->getLength() >= kRunwayLengthD && runway->getType() == "asphalt") {
                    return true;
                } else {
                    return false;
                }
            }
        } else if (Airplane::size == "large") {
            if (Airplane::engine == "propeller") {
                if (runway->getLength() >= kRunwayLengthC && runway->getType() == "asphalt") {
                    return true;
                } else {
                    return false;
                }
            } else if (Airplane::engine == "jet") {
                if (runway->getLength() >= kRunwayLengthB && runway->getType() == "asphalt") {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

bool Airplane::validPlaneType(const string &type) {

    if (type != "private" && type != "airline" && type != "military" && type != "emergency"){
        return false;
    }

    else if (Airplane::size == "small"){

        if (type == "airline"){
            return false;

        }

        if (Airplane::engine == "propeller"){
            if (type == "military"){
                return false;

            }
        }

        if (Airplane::engine == "jet"){
            if (type == "emergency"){
                return false;

            }
        }
    }

    else if (Airplane::size == "medium"){
        if (type == "military" || type == "emergency"){
            return false;

        }

        if (Airplane::engine == "propeller"){
            if (type == "private"){
                return false;

            }
        }
    }

    else if (Airplane::size == "large") {
        if (type == "emergency" || type == "private"){
            return false;

        }

        if (Airplane::engine == "jet"){
            if (type == "military"){
                return false;

            }
        }

        if (Airplane::engine == "propeller" ){
            if (type == "airline"){
                return false;

            }
        }
    }


    return true;

}

bool Airplane::validEngineType(const string &engine) {

    if (engine != "propeller" && engine != "jet"){
        return false;
    }

    else if (Airplane::type != "private" && Airplane::type != "airline" && Airplane::type != "military" && Airplane::type != "emergency"){
        return true;
    }

    else if (Airplane::size != "small" && Airplane::size != "medium" && Airplane::size != "large"){
        if (Airplane::type == "private"){
            return true;
        }
        else if (Airplane::type == "airline"){
            return true;

        }
        else if (Airplane::type == "military"){
            return true;
        }
        else{
            return engine == "propeller";
        }
    }

    else {
        if (Airplane::type == "private"){
            if (Airplane::size == "small"){
                return true;
            }
            else if (Airplane::size == "medium"){
                return engine == "jet";
            }
            else{
                return false;
            }
        }
        else if (Airplane::type == "airline"){
            if (Airplane::size == "small"){
                return false;
            }
            else if (Airplane::size == "medium"){
                return true;
            }
            else{
                return engine == "jet";
            }
        }
        else if (Airplane::type == "military"){
            if (Airplane::size == "small"){
                return engine == "jet";
            }
            else if (Airplane::size == "medium"){
                return false;
            }
            else{
                return engine == "propeller";
            }
        }
        else{
            if (Airplane::size == "small"){
                return engine == "propeller";
            }
            else if (Airplane::size == "medium"){
                return false;
            }
            else{
                return false;
            }
        }
    }
}

bool Airplane::validSize(const string &size) {
    if (size != "small" && size != "medium" && size != "large") {
        return false;
    }

    else if (Airplane::type != "private" && Airplane::type != "airline" && Airplane::type != "military" && Airplane::type != "emergency"){
        return true;
    }

    else if (Airplane::engine != "propeller" && Airplane::engine != "jet"){
        if (Airplane::type == "private"){
            if (size == "large"){
                return false;
            }
            else{
                return true;
            }
        }
        else if (Airplane::type == "airline"){
            if (size == "small"){
                return false;
            }
            else{
                return true;
            }
        }
        else if (Airplane::type == "military"){
            if (size == "medium"){
                return false;
            }
            else{
                return true;
            }
        }
        else{
            return size == "small";
        }
    }

    else {
        if (Airplane::type == "private"){
            if (Airplane::engine == "jet"){
                return size != "large";
            }
            else{
                return size == "small";
            }
        }
        else if (Airplane::type == "airline"){
            if (Airplane::engine == "jet"){
                return size != "small";
            }
            else{
                return size == "medium";
            }
        }
        else if (Airplane::type == "military"){
            if (Airplane::engine == "jet"){
                return size == "small";
            }
            else{
                return size == "large";
            }
        }
        else {
            if (Airplane::engine == "jet"){
                return false;
            }
            else{
                return size == "small";
            }
        }
    }
}

bool Airplane::atAirport() {

    return (Airplane::airport != NULL);

}

bool Airplane::atGate() {

    return Airplane::gate >= 0;

}

bool Airplane::readyForTakeOff() {
    return (Airplane::isReadyForDeparture() && Airplane::airport != NULL && Airplane::runway != NULL && Airplane::state == "Waiting for departure");
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
            airport->setWait3000(NULL);
            return true;
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

    if (Airplane::size.empty() || Airplane::fuel == 0 || Airplane::type.empty() || Airplane::model.empty() || Airplane::number.empty()
        || Airplane::callsign.empty() || Airplane::state.empty() || Airplane::engine.empty()){

        return false;
    }

    return (validSize(Airplane::size) && validEngineType(Airplane::engine) && validPlaneType(Airplane::type) && Airplane::properlyInitialised());

}


// functies
void Airplane::pushBack(Runway* runway) {
    REQUIRE(Airplane::getCurrentTask() == "IFR" || Airplane::getCurrentTask() == "pushback"
            || Airplane::getCurrentTask() == "request taxi", "correct state");
    REQUIRE(Airplane::atAirport(), "At airport");
    REQUIRE(Airplane::validRunway(runway), "Valid runway");

    Airplane::setState("pushback");
    string tijd = getTime();

    if (Airplane::currentTask == "IFR") {

        if (!Airplane::requestMessageSend) {

            if (runway == NULL) {
                vector<int> runway = Airplane::airport->getFreeRunways();
                for (int i = 0; (unsigned) i < runway.size(); i++) {
                    if (validRunway(Airplane::airport->getRunways()[i])) {
                        Airplane::attemptRunway = Airplane::airport->getRunways()[i];
                        break;
                    }
                }
            }
            IFRRequest(this, tijd);
            Airplane::requestMessageSend = true;
            return;
        }
        if (Airplane::requestMessageSend && runway == NULL) {
            runway = Airplane::attemptRunway;
        }
        if (!Airplane::messageMessageSend) {
            IFRMessage(this, tijd);
            Airplane::messageMessageSend = true;
            return;
        }
        if (!confirmMessageSend) {
            IFRConfirmation(this, tijd);
            Airplane::requestMessageSend = false;
            Airplane::messageMessageSend = false;
            Airplane::currentTask = "pushback";
            return;
        }
    }
    else if (Airplane::currentTask == "pushback") {

        if (!Airplane::requestMessageSend) {
            pushbackRequest(this, tijd);
            Airplane::requestMessageSend = true;
            return;
        }

        if (!Airplane::messageMessageSend) {
            pushbackMessage(this, tijd);
            Airplane::messageMessageSend = true;
            return;
        }

        if (!Airplane::confirmMessageSend) {
            pushbackConfirmation(this, tijd);
            Airplane::requestMessageSend = false;
            Airplane::messageMessageSend = false;
            Airplane::pushback = true;
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
        Airplane::currentTask = "going to runway";
        readyToTaxiMessage(this, tijd);
        return;
    }

}

void Airplane::taxiToRunway(Runway* runway){

    REQUIRE(Airplane::getCurrentTask() == "going to runway", "correct state");
    REQUIRE(Airplane::getRunway() != NULL || Airplane::getAttemptRunway() != NULL, "destination runway was set");
    if (runway == NULL){
        runway = Airplane::attemptRunway;
    }

    if (Airplane::gate != -1){
        Airplane::airport->setGateOccupied(Airplane::gate, false);
        Airplane::gate = -1;
    }

    //REQUIRE((!Airplane::onItsWay && !runw->getOnItsWay()) || (Airplane::onItsWay && runw->getOnItsWay()), "no plane on its way");

    Airplane::onItsWay = true;
    runway->setOnItsWay(true);

    const string &tijd = getTime();
    Airplane::taxiRoute = runway->getTaxiRoute();

    if (Airplane::taxiPoint.empty() && Airplane::taxiCrossing.empty()){
        Airplane::taxiPoint = Airplane::taxiRoute->getTaxiPoints()[0];
        Airplane::setState("at taxipoint");
        Airplane::operationTime = 1;
        return;
    }

    if (Airplane::taxiPoint != ""){
        for (unsigned int i=0; i < Airplane::taxiRoute->getTaxiPoints().size(); i++){
            if (Airplane::taxiPoint == Airplane::taxiRoute->getTaxiPoints()[i]){
                if (i == Airplane::taxiRoute->getTaxiPoints().size()-1){
                    if (!Airplane::messageMessageSend){
                        toRunwayMessage(this, runway, taxiPoint, tijd);
                        Airplane::messageMessageSend = true;
                        Airplane::operationTime = 1;
                        return;
                    }
                    else if (!Airplane::confirmMessageSend){
                        toRunwayConfirmation(this, runway, Airplane::taxiPoint, tijd);
                        Airplane::confirmMessageSend = true;
                        setOperationTime(1);
                        return;
                    }
                    else{
                        Airplane::messageMessageSend = false;
                        Airplane::confirmMessageSend = false;
                        Airplane::runway = runway;
                        Airplane::setState("at holding point");

                        Airplane::currentTask = "at holding point";
                        Airplane::onItsWay = false;
                        runway->setOnItsWay(false);
                        Airplane::operationTime = 1;

                        runway->setHoldingShortOccupied(true);
                        return;
                    }
                }
                else if (!Airplane::messageMessageSend) {
                    toHoldingPointMessage(this, taxiRoute->getTaxiCrossings()[i], taxiPoint, tijd);
                    Airplane::messageMessageSend = true;
                    Airplane::operationTime = 1;
                    return;
                }
                else  if (!Airplane::confirmMessageSend) {
                    toHoldingPointConfirmation(this, taxiRoute->getTaxiCrossings()[i], taxiPoint, tijd);
                    Airplane::confirmMessageSend = true;
                    Airplane::operationTime = 1;
                    return;
                }
                else{
                    Airplane::taxiPoint = "";
                    Airplane::taxiCrossing = Airplane::taxiRoute->getTaxiCrossings()[i];
                    Airplane::setState("at taxicrossing");
                    Airplane::messageMessageSend = false;
                    Airplane::confirmMessageSend = false;
                    Airplane::operationTime = 5;
                    return;
                }
            }
        }
    }
    else if (Airplane::taxiCrossing != ""){
        for (unsigned int i=0; i < Airplane::taxiRoute->getTaxiCrossings().size(); i++){
            if (Airplane::taxiCrossing == Airplane::taxiRoute->getTaxiCrossings()[i]){
                if (!Airplane::requestMessageSend) {
                    clearedToCrossRequest(this, taxiRoute->getTaxiCrossings()[i], tijd);
                    Airplane::requestMessageSend = true;
                    Airplane::operationTime = 1;
                    return;
                }
                else  if (!Airplane::messageMessageSend) {

                    if (!Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->getPermissionToCross()){
                        Airplane::operationTime = 1;
                        Airplane::requestMessageSend = false;
                        return;
                    }
                    else {
                        clearedToCrossMessage(this, Airplane::taxiRoute->getTaxiCrossings()[i], tijd);
                        Airplane::messageMessageSend = true;
                        setOperationTime(1);
                        return;
                    }
                }
                else  if (!Airplane::confirmMessageSend) {
                    clearedToCrossConfirmation(Airplane::taxiRoute->getTaxiCrossings()[i], tijd);
                    Airplane::confirmMessageSend = true;
                    Airplane::operationTime = 1;
                    return;
                }
                else{
                    if (Airplane::crossed){
                        Airplane::taxiCrossing = "";
                        Airplane::setTaxiPoint(taxiRoute->getTaxiPoints()[i+1]);
                        Airplane::requestMessageSend = false;
                        Airplane::messageMessageSend = false;
                        Airplane::confirmMessageSend = false;
                        Airplane::crossed = false;
                        runway->setPermissionToCross(true);
                        Airplane::setState("at taxipoint");
                        Airplane::setOperationTime(5);
                        return;
                    }
                    else {
                        if (runway->getPermissionToCross()){
                            Airplane::crossed = true;
                            runway->setPermissionToCross(false);
                            Airplane::setState("crossing taxicrossing");
                            Airplane::setOperationTime(1);
                            return;
                        }
                        else{
                            Airplane::setState("at taxicrossing");
                            Airplane::setOperationTime(1);
                            return;
                        }
                    }
                }
            }
        }
    }
}

void Airplane::taxiToGate(int gate){

    REQUIRE(Airplane::currentTask == "going to gate", "correct task");
    REQUIRE(Airplane::validGate(gate), "valid gate number");
    if(!Airplane::onItsWay) {

        if (gate == -1) {
            Airplane::attemptGate = Airplane::airport->getFreeGates()[0];
        }
        else{
            Airplane::attemptGate = gate;
        }

        Airplane::airport->setGateOccupied(Airplane::attemptGate, true);
        Airplane::onItsWay = true;
    }
    const string &tijd = getTime();
    if (Airplane::runway != NULL){
        Airplane::taxiRoute = Airplane::runway->getTaxiRoute();
        Airplane::runway->setOccupied(false);
        Airplane::runway->setPermissionToCross(true);
        Airplane::runway = NULL;
    }

    if (Airplane::taxiPoint == "" && Airplane::taxiCrossing == ""){
        Airplane::setState("at taxipoint");
        Airplane::taxiPoint = Airplane::taxiRoute->getTaxiPoints()[Airplane::taxiRoute->getTaxiPoints().size()-1];
        return;
    }
    if (!Airplane::taxiPoint.empty()){
        for (unsigned int i=0; i < Airplane::taxiRoute->getTaxiPoints().size(); i++){
            if (Airplane::taxiPoint == Airplane::taxiRoute->getTaxiPoints()[i]){
                if (i == 0){
                    if (!Airplane::messageMessageSend){
                        toGateMessage(this, Airplane::attemptGate, Airplane::taxiPoint, tijd);
                        Airplane::messageMessageSend = true;
                        return;
                    }
                    else if (!Airplane::confirmMessageSend){
                        toGateConfirmation(this, Airplane::attemptGate, Airplane::taxiPoint, tijd);
                        Airplane::confirmMessageSend = true;
                        return;
                    }
                    else{
                        Airplane::messageMessageSend = false;
                        Airplane::confirmMessageSend = false;
                        //setGate(attemptGate);
                        Airplane::operationTime = 1;
                        Airplane::onItsWay = false;
                        Airplane::currentTask = "exit passengers";
                        Airplane::setState("exit passengers");
                        Airplane::setGate(attemptGate);
                        return;
                    }
                }

                else if (!Airplane::messageMessageSend) {
                    toHoldingPointMessage(this, Airplane::taxiRoute->getTaxiCrossings()[i-1], Airplane::taxiPoint, tijd);
                    Airplane::messageMessageSend = true;
                    return;
                }
                else  if (!Airplane::confirmMessageSend) {
                    toHoldingPointConfirmation(this, Airplane::taxiRoute->getTaxiCrossings()[i-1], Airplane::taxiPoint, tijd);
                    Airplane::confirmMessageSend = true;
                    return;
                }
                else{
                    Airplane::taxiPoint = "";
                    Airplane::setState("at taxicrossing");
                    Airplane::taxiCrossing = taxiRoute->getTaxiCrossings()[i-1];
                    Airplane::messageMessageSend = false;
                    Airplane::confirmMessageSend = false;
                    Airplane::setOperationTime(5);
                    return;
                }
            }
        }
    }
    else if (!Airplane::taxiCrossing.empty()){
        for (unsigned int i=0; i < Airplane::taxiRoute->getTaxiCrossings().size(); i++){
            if (Airplane::taxiCrossing == Airplane::taxiRoute->getTaxiCrossings()[i]){
                if (!Airplane::requestMessageSend) {
                    clearedToCrossRequest(this, Airplane::taxiRoute->getTaxiCrossings()[i], tijd);
                    Airplane::requestMessageSend = true;
                    return;
                }
                else  if (!Airplane::messageMessageSend) {
                    if (!Airplane::getAirport()->getRunway(Airplane::taxiCrossing)->getPermissionToCross()){
                        return;
                    }
                    else {
                        clearedToCrossMessage(this, Airplane::taxiRoute->getTaxiCrossings()[i], tijd);
                        Airplane::messageMessageSend = true;
                        return;
                    }
                }
                else  if (!Airplane::confirmMessageSend) {
                    clearedToCrossConfirmation(Airplane::taxiRoute->getTaxiCrossings()[i], tijd);
                    Airplane::confirmMessageSend = true;
                    return;
                }
                else{
                    if (Airplane::crossed){
                        Airplane::taxiCrossing = "";
                        Airplane::taxiPoint = Airplane::taxiRoute->getTaxiPoints()[i+1];
                        Airplane::requestMessageSend = false;
                        Airplane::messageMessageSend = false;
                        Airplane::confirmMessageSend = false;
                        Airplane::crossed = false;
                        Airplane::runway->setPermissionToCross(true);
                        Airplane::setState("at taxipoint");
                        Airplane::setOperationTime(5);
                        return;
                    }
                    else {
                        if (Airplane::runway->getPermissionToCross()){
                            Airplane::crossed = true;
                            Airplane::runway->setPermissionToCross(false);
                            Airplane::setState("crossing taxicrossing");
                            Airplane::setOperationTime(1);
                            return;
                        }
                        else{
                            Airplane::setState("at taxicrossing");
                            Airplane::setOperationTime(1);
                            return;
                        }
                    }
                }
            }

        }
    }
}

void Airplane::emergencyLanding(Airport* airport){

    REQUIRE(Airplane::currentTask == "emergency crash" || Airplane::currentTask == "emergency landing" || Airplane::currentTask == "crash", "correct state");
    REQUIRE(!(Airplane::currentTask != "emergency crash" || Airplane::currentTask != "emergency landing") ||
            (Airplane::getState() == "Airborne" && (Airplane::currentTask != "emergency crash" ||
                    Airplane::currentTask != "emergency landing")), "Plane is out of fuel");


    const string &tijd = getTime();
    if(Airplane::currentTask != "emergency crash" || currentTask != "emergency landing") {

        if (!Airplane::requestMessageSend) {
            if (Airplane::height >= Airplane::kHeightLevelC) {
                EmergencyAbove3000ftRequest(this, airport, tijd);
                Airplane::emergencyInAirport = true;
                Airplane::requestMessageSend = true;
                if (Airplane::getEngine() == "jet") {
                    Airplane::setHeight(Airplane::getHeight()-Airplane::kJetDescentionSpeed);
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::setHeight(Airplane::getHeight()-Airplane::kProprellerDescentionSpeed);
                }
                Airplane::operationTime = 1;
                return;
            } else {
                EmergencyBelow3000ftRequest(this, airport, tijd);
                Airplane::emergencyInAirport = false;
                Airplane::requestMessageSend = true;
                if (Airplane::getEngine() == "jet") {
                    Airplane::setHeight(Airplane::getHeight()-Airplane::kJetDescentionSpeed);
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::setHeight(Airplane::getHeight()-Airplane::kProprellerDescentionSpeed);
                }
                Airplane::operationTime = 1;
                return;
            }
        } else {
            Airplane::requestMessageSend = false;
            if (Airplane::emergencyInAirport) {
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
                return;
            } else {
                EmergencyBelow3000ftMessage(this, tijd);
                Airplane::currentTask = "emergency crash";
                if (Airplane::getEngine() == "jet") {

                    Airplane::operationTime = Airplane::getHeight() / Airplane::kJetDescentionSpeed;
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::operationTime = Airplane::getHeight() / Airplane::kProprellerDescentionSpeed;
                }
                if (Airplane::getHeight() == 0){
                    Airplane::operationTime += 1;
                }
                Airplane::setHeight(0);
                return;
            }
        }
    }
    else{
        if (Airplane::emergencyInAirport){
            Airplane::runway->setPermissionToCross(true);
            Airplane::setState("emergency exit");
            Airplane::requestMessageSend = false;
            Airplane::currentTask = "exit passengers";
            return;
        }
        else{
            Airplane::setState("Finished");
            Airplane::requestMessageSend = false;
            Airplane::currentTask = "Finished";
            return;
        }

    }
}

void Airplane::land(Airport *airport, Runway* runway) {
    REQUIRE(Airplane::currentTask == "try to land" || Airplane::currentTask == "landing" || Airplane::currentTask == "descending to 5000ft."  || Airplane::currentTask == "descending to 3000ft." || Airplane::currentTask == "descending to 0ft.", "correct task");

    const string &tijd = getTime();
    if (Airplane::currentTask != "landing") {
        if (Airplane::state != "Approaching" && Airplane::state != "on final approach") {
            REQUIRE(Airplane::state == "Airborne", "Plane is not airborne");
            REQUIRE(validLandingSpot(airport, runway), "Valid landing spot");

            Airplane::setState("Approaching");

            if (runway == NULL) {
                logMessage("Preparing airplane (" + Airplane::number + ") for landing in " + airport->getName());

                vector<Runway*> runways = airport->getRunways();

                for (unsigned int i = 0; i < runways.size(); i++) {
                    if (!runways[i]->isOccupied()) {
                        Airplane::runway = runways[i];
                        Airplane::attemptRunway = runways[i];
                        break;

                    }
                }
            }

            initialCommunicationMessage(this, airport, tijd);
            Airplane::operationTime = 1;
            return;
        } else if (runway == NULL) {
            runway = attemptRunway;

        }

        logMessage(Airplane::number + " is approaching " + airport->getName() + " at " + intToString(height) + "ft.");
        if (Airplane::height == Airplane::kHeightLevelA) {
            if (!Airplane::requestMessageSend) {
                Airplane::requestMessageSend = true;

                if (permissionToDescend(Airplane::height, airport, runway)) {

                    descendTo5000ftMessage(this, tijd);
                    Airplane::confirmMessageSend = false;
                    Airplane::operationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    Airplane::confirmMessageSend = true;
                    Airplane::operationTime = 1;
                    return;
                }
            } else {

                Airplane::requestMessageSend = false;
                if (Airplane::confirmMessageSend) {
                    waitBeforeDescendConfirmation(this, tijd);
                    Airplane::confirmMessageSend = false;
                    Airplane::operationTime = 1;
                    return;

                } else {
                    descendTo5000ftConfirmation(this, tijd);
                    Airplane::currentTask = "descending to 5000ft.";
                    airport->setWait5000(this);

                    if (Airplane::getEngine() == "jet") {
                        Airplane::operationTime = (Airplane::kHeightLevelA - Airplane::kHeightLevelB)/Airplane::kJetDescentionSpeed +1;

                    } else if (Airplane::getEngine() == "propeller") {
                        Airplane::operationTime = (Airplane::kHeightLevelA - Airplane::kHeightLevelB)/Airplane::kProprellerDescentionSpeed +1;

                    }
                    return;
                }
            }
        }

        if (Airplane::height == Airplane::kHeightLevelB) {Airplane::operationTime = 6;
            if (!Airplane::requestMessageSend) {
                Airplane::requestMessageSend = true;
                if (permissionToDescend(Airplane::height, airport, runway)) {
                    descendTo3000ftMessage(this, tijd);
                    Airplane::confirmMessageSend = false;
                    Airplane::operationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    Airplane::confirmMessageSend = true;
                    Airplane::operationTime = 1;
                    return;
                }
            } else {
                Airplane::requestMessageSend = false;
                if (Airplane::confirmMessageSend) {
                    waitBeforeDescendConfirmation(this, tijd);
                    logMessage(Airplane::number + " is waiting at a height of " + intToString(height));
                    Airplane::confirmMessageSend = false;
                    Airplane::operationTime = 1;
                    return;
                } else {
                    descendTo3000ftConfirmation(this, tijd);
                    Airplane::currentTask = "descending to 3000ft.";

                    if (Airplane::getEngine() == "jet") {
                        Airplane::operationTime = (Airplane::kHeightLevelB - Airplane::kHeightLevelC)/Airplane::kProprellerDescentionSpeed -1;
                    } else if (Airplane::getEngine() == "propeller") {
                        Airplane::operationTime = (Airplane::kHeightLevelB - Airplane::kHeightLevelC)/Airplane::kProprellerDescentionSpeed -1;
                    }
                    return;
                }
            }
        }

        if (Airplane::height == Airplane::kHeightLevelC) {
            if (!Airplane::requestMessageSend) {
                Airplane::requestMessageSend = true;

                if (runway == NULL) {
                    logMessage("Preparing airplane (" + Airplane::number + ") for landing in " + airport->getName());

                    vector<Runway*> runways = airport->getRunways();

                    for (unsigned int i = 0; i < runways.size(); i++) {
                        if (!runways[i]->isOccupied()) {
                            runway = runways[i];
                            Airplane::attemptRunway = runways[i];
                            break;

                        }
                    }
                }

                if (permissionToDescend(Airplane::height, airport, runway)) {
                    finalApproachMessage(this, runway, tijd);
                    runway->setOccupied(true);
                    runway->setPermissionToCross(false);
                    Airplane::confirmMessageSend = false;
                    Airplane::operationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    Airplane::confirmMessageSend = true;
                    Airplane::operationTime = 1;
                    return;
                }
            } else {
                Airplane::requestMessageSend = false;
                if (Airplane::confirmMessageSend) {
                    waitBeforeDescendConfirmation(this, tijd);
                    logMessage(Airplane::number + " is waiting at a height of " + intToString(Airplane::height));
                    Airplane::confirmMessageSend = false;
                    Airplane::operationTime = 1;
                    return;
                } else {
                    finalApproachConfirmation(this, runway, tijd);
                    Airplane::setState("on final approach");
                    Airplane::currentTask = "descending to 0ft.";

                    if (Airplane::getEngine() == "jet") {
                        Airplane::operationTime = Airplane::kHeightLevelC/Airplane::kJetDescentionSpeed;
                    } else if (Airplane::getEngine() == "propeller") {
                        Airplane::operationTime = Airplane::kHeightLevelC/Airplane::kProprellerDescentionSpeed;
                    }
                    return;
                }
            }
        } else {
            Airplane::currentTask = "landing";
            Airplane::operationTime = 2;

            logMessage(Airplane::number + " is landing at Runway" + runway->getName());
            Airplane::setAirport(airport);
            logMessage("Airplane (" + Airplane::number + ") landed in " + airport->getIata());

            Airplane::setRunway(runway);
            logMessage("Airplane (" + Airplane::number + ") is now at runway " + runway->getName() + "\n");

            Airplane::setState("At runway");
            Airplane::height -= Airplane::kJetDescentionSpeed;


            ENSURE(Airplane::runway == runway, "Landed");
        }
    }
    else {
        afterLandingMessage(this, Airplane::airport, Airplane::runway, tijd);
        Airplane::currentTask = "going to gate";
        Airplane::operationTime = 1;
        return;

    }

}

void Airplane::takeOff() {
    REQUIRE(Airplane::currentTask == "taking off" || Airplane::currentTask == "at holding point", "correct state");
    const string &tijd = getTime();

    REQUIRE(Airplane::getHeight() == 0, "Plane not on ground");
    if (Airplane::currentTask == "at holding point") {
        if (!Airplane::requestMessageSend) {
            holdingShortAtRunway(this, Airplane::runway, tijd);
            Airplane::requestMessageSend = true;
            Airplane::setOperationTime(1);
            return;
        }

        if (!Airplane::messageMessageSend) {
            if (!Airplane::runway->isOccupied() && !Airplane::runway->getWaitingOnRunway() && !Airplane::runway->getHoldingShortOccupied() && !Airplane::runway->getCrossing()) {
                clearedForTakeOffMessage(this, Airplane::runway, tijd);
                Airplane::permissionToTakeOff = true;
                Airplane::messageMessageSend = true;
                Airplane::runway->setWaitingOnRunway(true);
                Airplane::runway->setOccupied(true);
                Airplane::runway->setPermissionToCross(false);
                setOperationTime(1);
                return;
            } else if (!Airplane::runway->isOccupied() && !Airplane::runway->getWaitingOnRunway() && Airplane::runway->getHoldingShortOccupied() && !Airplane::runway->getCrossing() && Airplane::waitAtRunway) {
                clearedForTakeOffMessage(this, Airplane::runway, tijd);
                Airplane::permissionToTakeOff = true;
                Airplane::messageMessageSend = true;
                Airplane::runway->setWaitingOnRunway(true);
                Airplane::runway->setOccupied(true);
                Airplane::runway->setPermissionToCross(false);
                setOperationTime(1);
                return;
            } else if (!Airplane::runway->isOccupied() && !Airplane::runway->getWaitingOnRunway() && !Airplane::runway->getHoldingShortOccupied() && Airplane::runway->getCrossing()) {
                lineUpRunwayMessage(this, Airplane::runway, tijd);
                Airplane::messageMessageSend = true;
                Airplane::waitOnRunway = true;
                Airplane::runway->setWaitingOnRunway(true);
                Airplane::runway->setOccupied(true);
                setOperationTime(1);
                return;
            } else if (!Airplane::runway->isOccupied() && !Airplane::runway->getWaitingOnRunway() && Airplane::runway->getHoldingShortOccupied() && Airplane::runway->getCrossing() && Airplane::waitAtRunway) {
                lineUpRunwayMessage(this, Airplane::runway, tijd);
                Airplane::messageMessageSend = true;
                Airplane::waitOnRunway = true;
                Airplane::waitAtRunway = false;
                Airplane::runway->setWaitingOnRunway(true);
                Airplane::runway->setOccupied(true);
                Airplane::setOperationTime(1);
                return;
            } else if (!Airplane::runway->getHoldingShortOccupied() || (Airplane::runway->getHoldingShortOccupied() && Airplane::waitAtRunway)) {
                waitAtRunwayMessage(this, tijd);
                Airplane::messageMessageSend = true;
                Airplane::waitAtRunway = true;
                Airplane::runway->setHoldingShortOccupied(true);
                Airplane::setOperationTime(1);
                return;
            }
        }
        else {
            if (Airplane::permissionToTakeOff) {
                clearedForTakeOffConfirmation(this, Airplane::runway, tijd);
                Airplane::permissionToTakeOff = false;
                Airplane::setState("At runway");
                Airplane::currentTask == "taking off";
                Airplane::requestMessageSend = false;
                Airplane::messageMessageSend = false;
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
                Airplane::requestMessageSend = false;
                Airplane::messageMessageSend = false;
                Airplane::waitOnRunway = true;
                Airplane::setState("lined up");
                Airplane::setOperationTime(1);
                Airplane::runway->setHoldingShortOccupied(false);
                return;
            }
            if (Airplane::waitAtRunway) {
                waitAtRunwayConfirmation(this, tijd);
                Airplane::requestMessageSend = false;
                Airplane::messageMessageSend = false;
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

    Airplane::setAirport(NULL);
    Airplane::setRunway(NULL);
    Airplane::setState("Airborne");

    if (Airplane::getEngine() == "propeller"){
        Airplane::operationTime = Airplane::kHeightLevelC;
        Airplane::height += Airplane::kProprellerAscentionSpeed;
    }
    else if (Airplane::getEngine() == "jet"){
        Airplane::operationTime = Airplane::kHeightLevelC;
        Airplane::height += Airplane::kJetAscentionSpeed;
    }

    ENSURE(Airplane::runway == NULL && Airplane::state == "Airborne" && Airplane::airport == NULL && Airplane::height != 0, "Airborne");

    Airplane::currentTask = "taking-Off";

    Airplane::setSimulationFinished(true);
    return;

}

void Airplane::exitPlane(){
    REQUIRE(Airplane::getCurrentTask() == "exit passengers" && Airplane::atGate(), "correct state");
    Airplane::setTaxiPoint("");
    Airplane::setTaxiCrossing("");
    if (Airplane::passengers <= 0) {

        Airplane::passengers = 0;

        logMessage(intToString(Airplane::passengerCapacity) + " passengers exited " + Airplane::callsign + " at gate "
                   + intToString(Airplane::gate) + " of " + Airplane::airport->getName());

        if(Airplane::getEmergencyInAirport()){
            Airplane::setState("emergency check");
        }
        else{
            Airplane::setState("technical check");

        }
        Airplane::currentTask = "technical check";
        return;
    }else{
        if (Airplane::size == "small"){
            Airplane::operationTime = kSmall*Airplane::kBoardingExitingTime;
            Airplane::passengers -= Airplane::passengerCapacity/(kSmall*Airplane::kBoardingExitingTime);
        }else{
            if (size == "medium"){
                Airplane::operationTime = kMedium*Airplane::kBoardingExitingTime;
                Airplane::passengers -= Airplane::passengerCapacity/(kMedium*Airplane::kBoardingExitingTime);
            }else{
                Airplane::operationTime = kLarge*Airplane::kBoardingExitingTime;
                Airplane::passengers -= Airplane::passengerCapacity/(kLarge*Airplane::kBoardingExitingTime);

            }
        }
    }
}

void Airplane::enterPlane(){
    REQUIRE(Airplane::getCurrentTask() == "board passengers" && Airplane::atGate(), "correct state");

    if (Airplane::passengers >= Airplane::passengerCapacity) {

        Airplane::passengers = Airplane::passengerCapacity;

        logMessage(intToString(Airplane::passengerCapacity) + " passengers entered " + Airplane::callsign + " at gate "
                            + intToString(Airplane::gate) + " of " + Airplane::airport->getName());

        Airplane::setState("pushback");
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
    REQUIRE(Airplane::getCurrentTask() == "technical check" && Airplane::atGate(), "correct state");

    Airplane::emergencyInAirport = false;
    if (!Airplane::technicalChecked && Airplane::size != "small"){
        if (Airplane::getSize() == "medium") {
            Airplane::operationTime = kMedium-1;
        } else if (Airplane::getSize() == "large") {
            Airplane::operationTime = kLarge-1;
        }
        Airplane::technicalChecked = true;
        return;
    }

    logMessage(getNumber() + " has been checked for technical malfunction");
    if (emergencyInAirport){
        Airplane::setState("emergency refuel");
    }
    else {
        if (Airplane::fuel == Airplane::fuelCapacity){
            Airplane::currentTask = "board passengers";
            Airplane::setState("board passengers");
        }else{
            Airplane::setState("refuel");
            Airplane::setOperationTime(ceil((Airplane::fuelCapacity - Airplane::fuel)/ Airplane::kFuelPerMinute));
            Airplane::currentTask = "refueling";
        }
    }

    return;
}

void Airplane::refuel() {
    REQUIRE(Airplane::getCurrentTask() == "refueling" && atGate(), "correct state");

    logMessage(getNumber() + " has been refueled");

    if (Airplane::emergencyInAirport) {
        Airplane::currentTask = "taxi to gate";

    } else {
        Airplane::setState("board passengers");

        // << getTimePassed() << ", " << flightPlan->getDeparture() << endl;
        if (getTimePassed() > Airplane::flightPlan->getDeparture()) { ;
            Airplane::currentTask = "board passengers";

        }else{
            Airplane::currentTask = "idle";
            Airplane::operationTime = Airplane::flightPlan->getDeparture() - getTimePassed();
        }

    }

    Airplane::setFuel(Airplane::getFuelCapacity());

    return;

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

    }else{
        Airplane::height += Airplane::kProprellerAscentionSpeed;

    }

    if (Airplane::height >= Airplane::kHeightLevelB){
        Airplane::currentTask = "finished";

    }

    logMessage(Airplane::number + " is leaving " + airport->getName() + " at " + intToString(Airplane::height) + "ft.");

}


//simulation
void Airplane::initSimulation(Airport *airport) {
    Airplane::setSimulationFinished(false);
    Airplane::onItsWay = false;
    Airplane::waitOnRunway = false;
    Airplane::waitAtRunway = false;
    Airplane::requestMessageSend = false;
    Airplane::messageMessageSend = false;
    Airplane::confirmMessageSend = false;
    Airplane::technicalChecked = false;
    Airplane::emergencyInAirport = false;
    Airplane::alreadyLinedUp = false;
    Airplane::ifrAuthorized = false;
    Airplane::pushback = false;

    Airplane::setSquawkCode();

    for (unsigned int i = 0; i < airport->getRunways().size(); i++) {
        airport->getRunways()[i]->setPermissionToCross(true);
        airport->getRunways()[i]->setOnItsWay(false);
        airport->getRunways()[i]->setWaitingOnRunway(false);
        airport->getRunways()[i]->setHoldingShortOccupied(false);
    }
    if (Airplane::flightPlan != NULL) {
        if (Airplane::getState() == "Approaching") {
            Airplane::setHeight(Airplane::kHeightLevelA);
            Airplane::operationTime = Airplane::flightPlan->getArrival();
            Airplane::currentTask = "try to land";


        }

        if (Airplane::getState() == "Gate") {

            Airplane::setHeight(0);
            Airplane::setFuel(0);
            Airplane::setPassengers(0);

            Airplane::operationTime = Airplane::flightPlan->getDeparture();
            Airplane::currentTask = "technical check";

            Airplane::setAirport(airport);
            Airplane::setGate(airport->getFreeGates()[0]);
            airport->setGateOccupied(0, true);

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

bool Airplane::notFinished(Airport* airport) {
    return !(Airplane::currentTask == "finished");

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


    if (Airplane::currentTask == "taking-Off"){
        Airplane::ascend(airport);

    }

    if (Airplane::currentTask == "descending to 5000ft." || Airplane::currentTask == "descending to 3000ft." || Airplane::currentTask == "descending to 0ft."){
        Airplane::descend(airport);

    }



}


//Output
void Airplane::printInfo() {
    cout << Airplane::getInfo() << endl;

}

string Airplane::getInfo() {
    string str;
    str = "\nAirplane:\t" + Airplane::callsign + " (" + Airplane::number +  ")\n"
          + "->model:\t" + Airplane::model +"\n"
          + "->type:\t" + Airplane::type + "\n"
          + "->engine:\t" + Airplane::engine + "\n"
          + "->size:\t" + Airplane::size + "\n";

    return str;
}

int Airplane::getAttemptgate() const {
    return Airplane::attemptGate;
}

void Airplane::setAttemptgate(int attemptGate) {
    Airplane::attemptGate = attemptGate;
    ENSURE(Airplane::getAttemptgate() == attemptGate, "attempt gate set");
}

bool Airplane::isOnItsWay() const {
    return onItsWay;
}

void Airplane::setOnItsWay(bool onItsWay) {
    Airplane::onItsWay = onItsWay;
    ENSURE(Airplane::isOnItsWay() == onItsWay, "onItsWay set");
}










