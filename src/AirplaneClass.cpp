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
    self = this;
    gate = -1;
    runway = NULL;
    taxiPoint = "";
    taxiCrossing = "";
    flightPlan = NULL;
    attemptRunway = NULL;

}

//getters & setters
const string &Airplane::getNumber() const {
    return number;
}
void Airplane::setNumber(const string &number) {
    Airplane::number = number;
    ENSURE(Airplane::getNumber() == number, "number set");

}

const string &Airplane::getCallsign() const {
    return callsign;
}
void Airplane::setCallsign(const string &callsign) {
    Airplane::callsign = callsign;
    ENSURE(Airplane::getCallsign() == callsign, "callsign set");
}

const string &Airplane::getModel() const {
    return model;
}
void Airplane::setModel(const string &model) {
    Airplane::model = model;
    ENSURE(Airplane::getModel() == model, "model set");
}

const string &Airplane::getState() const {
    return state;
}
void Airplane::setState(const string &state) {
    Airplane::state = state;
    ENSURE(Airplane::getState() == state, "state set");
}

int Airplane::getFuel() const {
    return fuel;
}
void Airplane::setFuel(int fuel) {
    Airplane::fuel = fuel;
    ENSURE(Airplane::getFuel() == fuel, "fuel set");
}

int Airplane::getHeight() const {
    return height;
}
void Airplane::setHeight(int height) {
    Airplane::height = height;
    ENSURE(Airplane::getHeight() == height, "height set");
}

int Airplane::getFuelCapacity() const {
    return fuelCapacity;
}
void Airplane::setFuelCapacity(int fuelCapacity) {
    Airplane::fuelCapacity = fuelCapacity;
    ENSURE(Airplane::getFuelCapacity() == fuelCapacity, "fuel capacity set");
}

int Airplane::getPassengers() const {
    return passengers;
}
void Airplane::setPassengers(int passengers) {
    Airplane::passengers = passengers;
    ENSURE(Airplane::getPassengers() == passengers, "passengers set");
}

int Airplane::getPassengerCapacity() const {
    return passengerCapacity;
}
void Airplane::setPassengerCapacity(int passengerCapacity) {
    Airplane::passengerCapacity = passengerCapacity;
    ENSURE(Airplane::getPassengerCapacity() == passengerCapacity, "passenger capacity set");
}

Airport *Airplane::getAirport() const {
    return airport;
}
void Airplane::setAirport(Airport *airport){
    Airplane::airport = airport;
    ENSURE(Airplane::getAirport() == airport, "airport set");

}

const string &Airplane::getType() const {
    return type;
}
void Airplane::setType(const string &type) {
    REQUIRE(validPlaneType(type), "Valid type?");
    Airplane::type = type;
    ENSURE(!validPlaneType(type) || (validPlaneType(type) && Airplane::getType() == type), "type set");
}

const string &Airplane::getEngine() const {
    return engine;
}
void Airplane::setEngine(const string &engine) {
    REQUIRE(validEngineType(engine), "valid Engine");
    Airplane::engine = engine;
    ENSURE(!validEngineType(engine) || (validEngineType(engine) && Airplane::getEngine() == engine), "engine set");

}

const string &Airplane::getSize() const {
    return size;
}
void Airplane::setSize(const string &size) {
    REQUIRE(validSize(size), "valid size");
    Airplane::size = size;
    ENSURE(!validSize(size) || (validSize(size) && Airplane::getSize() == size), "size set");
}

int Airplane::getOpperationTime() const {
    return opperationTime;
}
void Airplane::setOpperationTime(int opperationTime) {
    Airplane::opperationTime = opperationTime;
    ENSURE(Airplane::getOpperationTime() == opperationTime, "opperation time set");
}

Runway *Airplane::getRunway() const {
    return runway;
}
void Airplane::setRunway(Runway *runway) {
    Airplane::runway = runway;
    ENSURE(Airplane::getRunway() == runway, "runway set");

}

int Airplane::getGate() const {
    return gate;
}
void Airplane::setGate(int gate) {
    REQUIRE(validGate(gate), "validGate");
    Airplane::gate = gate;
    ENSURE(Airplane::getGate() == gate, "gate set");
}

Runway *Airplane::getAttemptRunway() const {
    return attemptRunway;
}
void Airplane::setAttemptRunway(Runway * attemptRunway) {
    Airplane::attemptRunway = attemptRunway;
    ENSURE(Airplane::getAttemptRunway() == attemptRunway, "attempt runway set");
}

FlightPlan *Airplane::getFlightPlan() const {
    return flightPlan;
}
void Airplane::setFlightPlan(FlightPlan *flightPlan) {
    Airplane::flightPlan = flightPlan;
    ENSURE(Airplane::getFlightPlan() == flightPlan , "flight plan set");
}

TaxiRoute *Airplane::getTaxiRoute() const {
    return taxiRoute;
}
void Airplane::setTaxiRoute(TaxiRoute *taxiRoute) {
    Airplane::taxiRoute = taxiRoute;
    ENSURE(Airplane::getTaxiRoute() == taxiRoute, "taxiroute set");
}

const string &Airplane::getTaxiPoint() const {
    return taxiPoint;
}
void Airplane::setTaxiPoint(const string &taxiPoint) {
    Airplane::taxiPoint = taxiPoint;
    ENSURE(Airplane::getTaxiPoint() == taxiPoint, "taxi point set");
}

const string &Airplane::getTaxiCrossing() const {
    return taxiCrossing;
}
void Airplane::setTaxiCrossing(const string &taxiCrossing) {
    Airplane::taxiCrossing = taxiCrossing;
    ENSURE(Airplane::getTaxiCrossing() == taxiCrossing, "taxi crossing set");
}

bool Airplane::isIFRAuthorized() const {
    return IFRAuthorized;
}
void Airplane::setIFRAuthorized(bool IFRAuthorized) {
    Airplane::IFRAuthorized = IFRAuthorized;
    ENSURE(Airplane::isIFRAuthorized() == IFRAuthorized , "IFR authorized set");
}

bool Airplane::isPushback() const {
    return pushback;
}
void Airplane::setPushback(bool pushback) {
    Airplane::pushback = pushback;
    ENSURE(Airplane::isPushback() == pushback , "pushback set");
}

bool Airplane::isRequestMessageSend() const {
    return requestMessageSend;
}
void Airplane::setRequestMessageSend(bool requestMessageSend) {
    Airplane::requestMessageSend = requestMessageSend;
    ENSURE(Airplane::isRequestMessageSend() == requestMessageSend , "request message send set");
}

bool Airplane::isMessageMessageSend() const {
    return messageMessageSend;
}
void Airplane::setMessageMessageSend(bool messageMessageSend) {
    Airplane::messageMessageSend = messageMessageSend;
    ENSURE(Airplane::isMessageMessageSend() == messageMessageSend , "message send set");
}

bool Airplane::isConfirmMessageSend() const {
    return confirmMessageSend;
}
void Airplane::setConfirmMessageSend(bool confirmMessageSend) {
    Airplane::confirmMessageSend = confirmMessageSend;
    ENSURE(Airplane::isConfirmMessageSend() == confirmMessageSend , "confirm message send set");
}

bool Airplane::isTaxiRequest() const {
    return taxiRequest;
}
void Airplane::setTaxiRequest(bool taxiRequest) {
    Airplane::taxiRequest = taxiRequest;
    ENSURE(Airplane::isTaxiRequest() == taxiRequest , "taxi request set");
}

bool Airplane::getEmergencyInAirport() const {
    return emergencyInAirport;
}
void Airplane::setEmergencyInAirport(bool emergencyInAirport) {
    Airplane::emergencyInAirport = emergencyInAirport;
    ENSURE(Airplane::getEmergencyInAirport() == emergencyInAirport, "emergency in airport set");
}

void Airplane::setSquawkCode(int code){

    int index = 0;

    if (code == 0){
        if (type == "private"){
            if (size == "small"){
                index = PrivateSmallSquawk;

            }else{
                index = PrivateMediumSquawk;

            }
        }
        if (type == "airline"){
            if (size == "medium"){
                if (engine == "propeller"){
                    index = AirlineMediumPropellerSquawk;

                }else{
                    index = AirlineMediumJetSquawk;

                }

            }else{
                index = AirlineLargeSquawk;

            }
        }
        if (type == "military"){
            index = MilitarySquawk;

        }
        if (type == "emergency"){
            index = EmegencySquawk;

        }

        if (index == PrivateSmallSquawk) {
            int randNumb = rand() % 776 + 1;
            squawkCode == intToString(randNumb);

        }else{
            int randNumb = rand() % 777;
            int code = 1000*index + randNumb;
            squawkCode == intToString(code);

        }

    }else{
        squawkCode = intToString(code);

    }

    ENSURE(Airplane::getSquawkCode().empty() , "squawkCode set");

}
const string &Airplane::getSquawkCode() const {
    return squawkCode;
}

void setTime(string time){
    gTime = time;
    ENSURE(getTime() == time , "gTime set");
};
string getTime(){

    return gTime;

};

void setTimePassed(int time){
    gTimePassed = time;
    ENSURE(getTimePassed() == time, "passed time set");

}
int getTimePassed(){
    return gTimePassed;

}

void setStartingTime(int time){
    gStartingTime = time;
    ENSURE(getStartingTime() == time , "starting time set");

}
int getStartingTime(){
    return gStartingTime;

}

string Airplane::getDestination() {
    REQUIRE(getFlightPlan() != NULL, "has a flightPlan");
    return flightPlan->getDestination();
}

void Airplane::setVar(string Type, string Value) {

    if (Type == "number"){
        Airplane::setNumber(Value);
        return ;
    }

    else if (Type == "model"){
        Airplane::setModel(Value);
        return ;
    }

    else if (Type == "callsign"){
        Airplane::setCallsign(Value);
        return;
    }

    else if (Type == "status"){
        if (Value == "Gate" || Value == "Approaching" ) {
            Airplane::setState(Value);
        }
        return;
    }

    else if (Type == "type"){
        if (validPlaneType(Value)){
            Airplane::setType(Value);
        }
        return;
    }

    else if (Type == "engine"){
        if (validEngineType(Value)) {
            Airplane::setEngine(Value);
            return;
        }
    }

    else if (Type == "size"){
        if (validSize(Value)) {
            Airplane::setSize(Value);
            return;
        }
    }

    else if (Type == "passengers"){
        if (isNumber(Value)) {
            int i;
            istringstream(Value) >> i;
            Airplane::setPassengers(i);
            Airplane::setPassengerCapacity(i);
        }
        return;
    }

    else if (Type == "height"){
        if (isNumber(Value)) {
            int i;
            istringstream(Value) >> i;
            Airplane::setHeight(i);
        }
        return;
    }

    else if (Type == "fuel"){
        if (isNumber(Value)) {
            int i;
            istringstream(Value) >> i;
            Airplane::setFuel(i);
            Airplane::setFuelCapacity(i);
        }
        return;
    }

}

bool Airplane::getsimulationFinished(){
    return Airplane::simulationFinished;
}
void Airplane::setsimulationFinished(bool finished){
    Airplane::simulationFinished = finished;
    ENSURE(Airplane::getsimulationFinished() == finished , "simulation finished set");
}

const string &Airplane::getCurrentTask() const {
    return currentTask;
}
void Airplane::setCurrentTask(const string &currentTask) {
    Airplane::currentTask = currentTask;
    ENSURE(Airplane::getCurrentTask() == currentTask , "currentTask set");
}


//checks
bool Airplane::validLandingSpot(Airport *Port, Runway *Runw) {

    if (Port == NULL){
        return false;

    }

    if (Runw == NULL){
        vector<int> runw = Port->getFreeRunways();
        for (int i = 0; (unsigned)i<runw.size(); i++){
            Runway *runway = Port->getRunways()[i];
            if (getSize() == "small"){
                if (getEngine()== "propeller"){
                    if (runway->getLength() >= 500){
                        return true;
                    }
                    continue;
                }
                else if (getEngine()== "jet"){
                    if (runway->getLength() >= 1000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (getSize() == "medium"){
                if (getEngine()== "propeller"){
                    if (runway->getLength() >= 1000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (getEngine()== "jet"){
                    if (runway->getLength() >= 2000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (getSize() == "large"){
                if (getEngine()== "propeller"){
                    if (runway->getLength() >= 1500 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (getEngine()== "jet"){
                    if (runway->getLength() >= cHeightLevelC && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
        }
        return false;
    }
    else if (getSize() == "small"){
        if (getEngine()== "propeller"){
            if (Runw->getLength() >= 500 && !Runw->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine()== "jet"){
            if (Runw->getLength() >= 1000 && Runw->getType() == "asphalt" && !Runw->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (getSize() == "medium"){
        if (getEngine() == "propeller"){
            if (Runw->getLength() >= 1000 && Runw->getType() == "asphalt" && !Runw->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine() == "jet"){
            if (Runw->getLength() >= 2000 && Runw->getType() == "asphalt" && !Runw->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (getSize() == "large"){
        if (getEngine() == "propeller"){
            if (Runw->getLength() >= 1500 && Runw->getType() == "asphalt" && !Runw->isOccupied()){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine() == "jet"){
            if (Runw->getLength() >= cHeightLevelC && Runw->getType() == "asphalt" && !Runw->isOccupied()){
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
        vector<int> t = airport->getFreeGates();
        return t.size() != 0;

    }

    if (!(gate >= 0 && gate < airport->getGates())){
        return false;
    }
    return !airport->getGateOccupied(gate);

}

bool Airplane::validRunway(Runway* Runw){

    if (Runw == NULL){
        vector<int> runw = airport->getFreeRunways();
        for (int i = 0; (unsigned)i<runw.size(); i++){
            Runway *runway = airport->getRunways()[i];
            if (getSize() == "small"){
                if (getEngine() == "propeller"){
                    if (runway->getLength() >= cRunwayLengthA){
                        return true;
                    }
                    continue;
                }
                else if (getEngine() == "jet"){
                    if (runway->getLength() >= cRunwayLengthB && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (getSize() == "medium"){
                if (getEngine() == "propeller"){
                    if (runway->getLength() >= cRunwayLengthB && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (getEngine() == "jet"){
                    if (runway->getLength() >= cRunwayLengthD && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (getSize() == "large"){
                if (getEngine() == "propeller"){
                    if (runway->getLength() >= cRunwayLengthC && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (getEngine() == "jet"){
                    if (runway->getLength() >= cHeightLevelC && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
        }
        return false;
    }
    else if (getSize() == "small"){
        if (getEngine() == "propeller"){
            if (Runw->getLength() >= cRunwayLengthA){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine() == "jet"){
            if (Runw->getLength() >= cRunwayLengthB && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (getSize() == "medium"){
        if (getEngine() == "propeller"){
            if (Runw->getLength() >= cRunwayLengthB && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine() == "jet"){
            if (Runw->getLength() >= cRunwayLengthD && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (getSize() == "large"){
        if (getEngine() == "propeller"){
            if (Runw->getLength() >= cRunwayLengthC && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine() == "jet"){
            if (Runw->getLength() >= cRunwayLengthB && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
    }
    return false;
}

bool Airplane::validPlaneType(string type) {

    if (type != "private" && type != "airline" && type != "military" && type != "emergency"){
        return false;

    }

    if (size == "small"){

        if (type == "airline"){
            return false;

        }

        if (engine == "propeller"){
            if (type == "military"){
                return false;

            }
        }

        if (engine == "jet"){
            if (type == "emergency"){
                return false;

            }
        }
    }

    if (size == "medium"){
        if (type == "military" || type == "emergency"){
            return false;

        }

        if (engine == "propeller"){
            if (type == "private"){
                return false;

            }
        }
    }

    if (size == "large") {
        if (type == "emergency" || type == "private"){
            return false;

        }

        if (engine == "jet"){
            if (type == "military"){
                return false;

            }
        }

        if (engine == "propeller" ){
            if (type == "airline"){
                return false;

            }
        }
    }

    return true;
}

bool Airplane::validEngineType(string engine) {

    if (engine != "propeller" && engine != "jet"){
        return false;
    }

    if (type == "private"){

        if (size == "medium"){
            if (engine == "propeller"){
                return false;

            }
        }

        return true;
    }

    if (type == "airline"){

        if (size == "large"){
            if (engine == "propeller"){
                return false;

            }
        }

        return true;

    }

    if (type == "military"){
        if (size == "small"){
            return (engine == "jet");
        }

        if (size == "large") {
            return (engine == "propeller");
        }
    }

    if (type == "emergency"){
        return (engine == "propeller");

    }

    return true;

}

bool Airplane::validSize(string size) {

    if (type == "private"){
        if (size == "large"){
            return false;

        }

        if (engine == "propeller"){
            if (size == "medium"){
                return false;

            }
        }
    }

    if (type == "airline"){
        if (size == "small"){
            return false;

        }

        if (engine == "propeller"){
            if (size == "large"){
                return false;

            }
        }
    }

    if (type == "military"){
        if (size == "medium"){
            return false;

        }

        if (engine == "jet"){
            if (size == "large"){
                return false;

            }
        }

        if (engine == "propeller"){
            if (size == "small"){
                return false;

            }
        }
    }

    if (type == "emergency"){
        if (size == "large" || size == "medium"){
            return false;

        }
    }

    return true;

}

bool Airplane::atAirport() {

    return (airport != NULL);

}

bool Airplane::atGate() {

    return state == "Standing at gate" && gate >= 0;


}

bool Airplane::readyForTakeOff() {
    return (isReadyForDeparture() && Airplane::airport != NULL && Airplane::runway != NULL && Airplane::state == "Waiting for departure");
}

bool Airplane::permissionToDescend(int height, Airport* Port, Runway* Runway){
    if (height == cHeightLevelA){
        if (Port->getWait5000() == NULL){
            Port->setWait5000(this);
            return true;
        }
        else{
            return false;
        }
    }
    else if (height == cHeightLevelB){
        if (Port->getWait3000() == NULL){
            Port->setWait5000(NULL);
            Port->setWait3000(this);
            return true;
        }
        else{
            return false;
        }
    }
    else if (height == cHeightLevelC){
        if (Runway->isOccupied()){
            return false;
        }
        else{
            Port->setWait3000(NULL);
            return true;
        }
    }
    else {
        return true;
    }
}

bool Airplane::isReadyForDeparture() const {

    if (passengers == passengerCapacity){
        if (fuel == fuelCapacity){
            return true;
        }
    }
    return false;

}

bool Airplane::propperlyInitialised() {
    return (self == this);
}

bool Airplane::isValid() {

    if (size.empty() || fuel == 0 || type.empty() || model.empty() || number.empty()
        || callsign.empty() || state.empty() || engine.empty()){

        return false;
    }

    return (validSize(size) && validEngineType(engine) && validPlaneType(type) && propperlyInitialised());

}


// functies

void Airplane::pushBack(Runway* Runw) {
    REQUIRE(currentTask == "IFR" || currentTask == "pushback" || currentTask == "request taxi", "correct state");

    Airplane::setState("pushback");
    string tijd = getTime();

    if (currentTask == "IFR") {
        REQUIRE(atAirport(), "At airport");
        REQUIRE(validRunway(Runw), "Valid runway");

        if (!requestMessageSend) {

            if (Runw == NULL) {
                vector<int> runw = airport->getFreeRunways();
                for (int i = 0; (unsigned) i < runw.size(); i++) {
                    if (validRunway(airport->getRunways()[i])) {
                        attemptRunway = airport->getRunways()[i];
                        break;
                    }
                }
            }
            IFRRequest(this, tijd);
            requestMessageSend = true;
            return;
        }
        if (requestMessageSend && Runw == NULL) {
            Runw = attemptRunway;
        }
        if (!messageMessageSend) {
            IFRMessage(this, tijd);
            messageMessageSend = true;
            return;
        }
        if (!confirmMessageSend) {
            IFRConfirmation(this, tijd);
            requestMessageSend = false;
            messageMessageSend = false;
            currentTask = "pushback";
            return;
        }
    }
    else if (currentTask == "pushback") {

        if (!requestMessageSend) {
            pushbackRequest(this, tijd);
            requestMessageSend = true;
            return;
        }

        if (!messageMessageSend) {
            pushbackMessage(this, tijd);
            messageMessageSend = true;
            return;
        }

        if (!confirmMessageSend) {
            pushbackConfirmation(this, tijd);
            requestMessageSend = false;
            messageMessageSend = false;
            pushback = true;
            if (Airplane::getSize() == "small"){
                opperationTime = cSmall;
            }
            else if (Airplane::getSize() == "medium"){
                opperationTime = cMedium;
            }
            else if (Airplane::getSize() == "large"){
                opperationTime = cLarge;
            }
            currentTask = "request taxi";
            return;
        }
    }

    else if(currentTask == "request taxi") {
        currentTask = "going to runway";
        readyToTaxiMessage(this, tijd);
        return;
    }

}

void Airplane::taxiToRunway(Runway* runw){


    REQUIRE(currentTask == "going to runway", "correct state");
    if (runw == NULL){
        runw = Airplane::attemptRunway;
    }

    REQUIRE(!runw->getHoldingShortOccupied(), "Runway fully occupied.");
    if (gate != -1){
        airport->setGateOccupied(gate, false);
        gate = -1;
    }

    REQUIRE((!Airplane::onitsway && !runw->getonItsWay()) || (Airplane::onitsway && runw->getonItsWay()), "no plane on its way");

    Airplane::onitsway = true;
    runw->setonItsWay(true);
    string tijd = getTime();
    taxiRoute = runw->getTaxiRoute();

    if (taxiPoint.empty() && taxiCrossing.empty()){
        taxiPoint = taxiRoute->getTaxiPoints()[0];
        Airplane::setState("at taxipoint");
        setOpperationTime(1);
        return;
    }

    if (taxiPoint != ""){
        for (unsigned int i=0; i < taxiRoute->getTaxiPoints().size(); i++){
            if (taxiPoint == taxiRoute->getTaxiPoints()[i]){
                if (i == taxiRoute->getTaxiPoints().size()-1){
                    if (!messageMessageSend){
                        toRunwayMessage(this, runw, taxiPoint, tijd);
                        messageMessageSend = true;
                        setOpperationTime(1);
                        return;
                    }
                    else if (!confirmMessageSend){
                        toRunwayConfirmation(this, runw, taxiPoint, tijd);
                        confirmMessageSend = true;
                        setOpperationTime(1);
                        return;
                    }
                    else{
                        messageMessageSend = false;
                        confirmMessageSend = false;
                        runway = runw;
                        Airplane::setState("at holding point");
                        currentTask = "at holding point";
                        Airplane::onitsway = false;
                        runw->setonItsWay(false);
                        setOpperationTime(1);
                        runway->setHoldingShortOccupied(true);
                        return;
                    }
                }
                else if (!messageMessageSend) {
                    toHoldingPointMessage(this, taxiRoute->getTaxiCrossings()[i], taxiPoint, tijd);
                    messageMessageSend = true;
                    setOpperationTime(1);
                    return;
                }
                else  if (!confirmMessageSend) {
                    toHoldingPointConfirmation(this, taxiRoute->getTaxiCrossings()[i], taxiPoint, tijd);
                    confirmMessageSend = true;
                    setOpperationTime(1);
                    return;
                }
                else{
                    taxiPoint = "";
                    taxiCrossing = taxiRoute->getTaxiCrossings()[i];
                    Airplane::setState("at taxicrossing");
                    messageMessageSend = false;
                    confirmMessageSend = false;
                    setOpperationTime(5);
                    return;
                }
            }
        }
    }
    else if (taxiCrossing != ""){
        for (unsigned int i=0; i < taxiRoute->getTaxiCrossings().size(); i++){
            if (taxiCrossing == taxiRoute->getTaxiCrossings()[i]){
                if (!requestMessageSend) {
                    clearedToCrossRequest(this, taxiRoute->getTaxiCrossings()[i], tijd);
                    requestMessageSend = true;
                    setOpperationTime(1);
                    return;
                }
                else  if (!messageMessageSend) {

                    if (!Airplane::getAirport()->getRunway(taxiCrossing)->getPermissionToCross()){
                        setOpperationTime(1);
                        requestMessageSend = false;
                        return;
                    }
                    else {
                        clearedToCrossMessage(this, taxiRoute->getTaxiCrossings()[i], tijd);
                        messageMessageSend = true;
                        setOpperationTime(1);
                        return;
                    }
                }
                else  if (!confirmMessageSend) {
                    clearedToCrossConfirmation(this, taxiRoute->getTaxiCrossings()[i], tijd);
                    confirmMessageSend = true;
                    setOpperationTime(1);
                    return;
                }
                else{
                    if (crossed){
                        taxiCrossing = "";
                        taxiPoint = taxiRoute->getTaxiPoints()[i+1];
                        requestMessageSend = false;
                        messageMessageSend = false;
                        confirmMessageSend = false;
                        crossed = false;
                        runw->setPermissionToCross(true);
                        Airplane::setState("at taxipoint");
                        setOpperationTime(5);
                        return;
                    }
                    else {
                        if (runw->getPermissionToCross()){
                            crossed = true;
                            runw->setPermissionToCross(false);
                            Airplane::setState("crossing taxicrossing");
                            setOpperationTime(1);
                            return;
                        }
                        else{
                            Airplane::setState("at taxicrossing");
                            setOpperationTime(1);
                            return;
                        }
                    }
                }
            }
        }
    }
}

void Airplane::taxiToGate(int gate){
    REQUIRE(currentTask == "going to gate", "correct task");
    REQUIRE(validGate(gate), "valid gate number");
    if(!onitsway) {
        if (gate == -1) {
            attemptgate = airport->getFreeGates()[0];
        }
        else{
            attemptgate = gate;
        }
        airport->setGateOccupied(attemptgate, true);
        Airplane::onitsway = true;
    }
    string tijd = getTime();
    if (runway != NULL){
        taxiRoute = runway->getTaxiRoute();
        runway->setOccupied(false);
        runway->setPermissionToCross(true);
        runway = NULL;
    }

    if (taxiPoint == "" && taxiCrossing == ""){
        Airplane::setState("at taxipoint");
        taxiPoint = taxiRoute->getTaxiPoints()[taxiRoute->getTaxiPoints().size()-1];
        return;
    }
    if (!taxiPoint.empty()){
        for (unsigned int i=0; i < taxiRoute->getTaxiPoints().size(); i++){
            if (taxiPoint == taxiRoute->getTaxiPoints()[i]){
                if (i == 0){
                    if (!messageMessageSend){
                        toGateMessage(this, attemptgate, taxiPoint, tijd);
                        messageMessageSend = true;
                        return;
                    }
                    else if (!confirmMessageSend){
                        toGateConfirmation(this, attemptgate, taxiPoint, tijd);
                        confirmMessageSend = true;
                        return;
                    }
                    else{
                        messageMessageSend = false;
                        confirmMessageSend = false;
                        setGate(attemptgate);
                        opperationTime = 1;
                        Airplane::onitsway = false;
                        currentTask = "exit passengers";
                        Airplane::setState("exit passengers");
                        Airplane::setGate(attemptgate);
                        return;
                    }
                }

                else if (!messageMessageSend) {
                    toHoldingPointMessage(this, taxiRoute->getTaxiCrossings()[i-1], taxiPoint, tijd);
                    messageMessageSend = true;
                    return;
                }
                else  if (!confirmMessageSend) {
                    toHoldingPointConfirmation(this, taxiRoute->getTaxiCrossings()[i-1], taxiPoint, tijd);
                    confirmMessageSend = true;
                    return;
                }
                else{
                    taxiPoint = "";
                    Airplane::setState("at taxicrossing");
                    taxiCrossing = taxiRoute->getTaxiCrossings()[i-1];
                    messageMessageSend = false;
                    confirmMessageSend = false;
                    opperationTime = 5;
                    return;
                }
            }
        }
    }
    else if (!taxiCrossing.empty()){
        for (unsigned int i=0; i < taxiRoute->getTaxiCrossings().size(); i++){
            if (taxiCrossing == taxiRoute->getTaxiCrossings()[i]){
                if (!requestMessageSend) {
                    clearedToCrossRequest(this, taxiRoute->getTaxiCrossings()[i], tijd);
                    requestMessageSend = true;
                    return;
                }
                else  if (!messageMessageSend) {
                    if (!Airplane::getAirport()->getRunway(taxiCrossing)->getPermissionToCross()){
                        return;
                    }
                    else {
                        clearedToCrossMessage(this, taxiRoute->getTaxiCrossings()[i], tijd);
                        messageMessageSend = true;
                        return;
                    }
                }
                else  if (!confirmMessageSend) {
                    clearedToCrossConfirmation(this, taxiRoute->getTaxiCrossings()[i], tijd);
                    confirmMessageSend = true;
                    return;
                }
                else{
                    if (crossed){
                        taxiCrossing = "";
                        taxiPoint = taxiRoute->getTaxiPoints()[i+1];
                        requestMessageSend = false;
                        messageMessageSend = false;
                        confirmMessageSend = false;
                        crossed = false;
                        runway->setPermissionToCross(true);
                        Airplane::setState("at taxipoint");
                        setOpperationTime(5);
                        return;
                    }
                    else {
                        if (runway->getPermissionToCross()){
                            crossed = true;
                            runway->setPermissionToCross(false);
                            Airplane::setState("crossing taxicrossing");
                            setOpperationTime(1);
                            return;
                        }
                        else{
                            Airplane::setState("at taxicrossing");
                            setOpperationTime(1);
                            return;
                        }
                    }
                }
            }

        }
    }
}

void Airplane::emergencyLanding(Airport* Port){

    REQUIRE(currentTask == "emergency crash" || currentTask == "emergency landing" || currentTask == "crash", "correct state");
    REQUIRE(!(currentTask != "emergency crash" || currentTask != "emergency landing") ||
            (Airplane::getState() == "Airborne" && (currentTask != "emergency crash" ||
                    currentTask != "emergency landing")), "Plane is out of fuel");


    string tijd = getTime();
    if(currentTask != "emergency crash" || currentTask != "emergency landing") {

        if (!requestMessageSend) {
            if (height >= cHeightLevelC) {
                EmergencyAbove3000ftRequest(this, Port, tijd);
                emergencyInAirport = true;
                requestMessageSend = true;
                if (Airplane::getEngine() == "jet") {
                    Airplane::setHeight(Airplane::getHeight()-cJetDescentionSpeed);
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::setHeight(Airplane::getHeight()-cProprellerDescentionSpeed);
                }
                opperationTime = 1;
                return;
            } else {
                EmergencyBelow3000ftRequest(this, Port, tijd);
                emergencyInAirport = false;
                requestMessageSend = true;
                if (Airplane::getEngine() == "jet") {
                    Airplane::setHeight(Airplane::getHeight()-cJetDescentionSpeed);
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::setHeight(Airplane::getHeight()-cProprellerDescentionSpeed);
                }
                opperationTime = 1;
                return;
            }
        } else {
            requestMessageSend = false;
            if (emergencyInAirport) {
                EmergencyAbove3000ftMessage(this, runway, tijd);
                runway = Port->getRunways()[Port->getFreeRunways()[0]];
                Port->getRunways()[Port->getFreeRunways()[0]]->setOccupied(true);
                Port->getRunways()[Port->getFreeRunways()[0]]->setPermissionToCross(false);
                currentTask = "emergency landing";
                if (Airplane::getEngine() == "jet") {
                    opperationTime = Airplane::getHeight() / cJetDescentionSpeed;
                } else if (Airplane::getEngine() == "propeller") {
                    opperationTime = Airplane::getHeight() / cProprellerDescentionSpeed;
                }
                Airplane::setHeight(0);
                return;
            } else {
                EmergencyBelow3000ftMessage(this, tijd);
                currentTask = "emergency crash";
                if (Airplane::getEngine() == "jet") {

                    opperationTime = Airplane::getHeight() / cJetDescentionSpeed;
                } else if (Airplane::getEngine() == "propeller") {
                    opperationTime = Airplane::getHeight() / cProprellerDescentionSpeed;
                }
                if (Airplane::getHeight() == 0){
                    opperationTime += 1;
                }
                Airplane::setHeight(0);
                return;
            }
        }
    }
    else{
        if (emergencyInAirport){
            runway->setPermissionToCross(true);
            Airplane::setState("emergency exit");
            requestMessageSend = false;
            currentTask = "exit passengers";
            return;
        }
        else{
            Airplane::setState("Finished");
            requestMessageSend = false;
            currentTask = "Finished";
            return;
        }

    }
}

void Airplane::land(Airport *Port, Runway* Runw) {
    REQUIRE(currentTask == "try to land" || currentTask == "landing" || currentTask == "descending to 5000ft."  || currentTask == "descending to 3000ft." || currentTask == "descending to 0ft.", "correct task");

    string tijd = getTime();
    if (currentTask != "landing") {
        if (state != "Approaching" && state != "on final approach") {
            REQUIRE(state == "Airborne", "Plane is not airborne");
            REQUIRE(validLandingSpot(Port, Runw), "Valid landing spot");

            Airplane::setState("Approaching");

            if (Runw == NULL) {
                logMessage("Preparing airplane (" + Airplane::number + ") for landing in " + Port->getName());

                vector<Runway*> runw = Port->getRunways();

                for (unsigned int i = 0; i < runw.size(); i++) {
                    if (!runw[i]->isOccupied()) {
                        Runw = runw[i];
                        attemptRunway = runw[i];
                        break;

                    }
                }
            }

            initialCommunicationMessage(this, Port, tijd);
            opperationTime = 1;
            return;
        } else if (Runw == NULL) {
            Runw = attemptRunway;

        }

        logMessage(Airplane::number + " is approaching " + Port->getName() + " at " + intToString(height) + "ft.");
        if (height == cHeightLevelA) {
            if (!requestMessageSend) {
                requestMessageSend = true;

                if (permissionToDescend(height, Port, Runw)) {

                    descendTo5000ftMessage(this, tijd);
                    confirmMessageSend = false;
                    opperationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    confirmMessageSend = true;
                    opperationTime = 1;
                    return;
                }
            } else {

                requestMessageSend = false;
                if (confirmMessageSend) {
                    waitBeforeDescendConfirmation(this, tijd);
                    confirmMessageSend = false;
                    opperationTime = 1;
                    return;

                } else {
                    descendTo5000ftConfirmation(this, tijd);
                    currentTask = "descending to 5000ft.";
                    Port->setWait5000(this);

                    if (Airplane::getEngine() == "jet") {
                        opperationTime = (cHeightLevelA - cHeightLevelB)/cJetDescentionSpeed +1;

                    } else if (Airplane::getEngine() == "propeller") {
                        opperationTime = (cHeightLevelA - cHeightLevelB)/cProprellerDescentionSpeed +1;

                    }
                    return;
                }
            }
        }

        if (height == cHeightLevelB) {opperationTime = 6;
            if (!requestMessageSend) {
                requestMessageSend = true;
                if (permissionToDescend(height, Port, Runw)) {
                    descendTo3000ftMessage(this, tijd);
                    confirmMessageSend = false;
                    opperationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    confirmMessageSend = true;
                    opperationTime = 1;
                    return;
                }
            } else {
                requestMessageSend = false;
                if (confirmMessageSend) {
                    waitBeforeDescendConfirmation(this, tijd);
                    logMessage(Airplane::number + " is waiting at a height of " + intToString(height));
                    confirmMessageSend = false;
                    opperationTime = 1;
                    return;
                } else {
                    descendTo3000ftConfirmation(this, tijd);
                    currentTask = "descending to 3000ft.";

                    if (Airplane::getEngine() == "jet") {
                        opperationTime = (cHeightLevelB - cHeightLevelC)/cProprellerDescentionSpeed -1;
                    } else if (Airplane::getEngine() == "propeller") {
                        opperationTime = (cHeightLevelB - cHeightLevelC)/cProprellerDescentionSpeed -1;
                    }
                    return;
                }
            }
        }

        if (height == cHeightLevelC) {
            if (!requestMessageSend) {
                requestMessageSend = true;

                if (Runw == NULL) {
                    logMessage("Preparing airplane (" + Airplane::number + ") for landing in " + Port->getName());

                    vector<Runway*> runw = Port->getRunways();

                    for (unsigned int i = 0; i < runw.size(); i++) {
                        if (!runw[i]->isOccupied()) {
                            Runw = runw[i];
                            attemptRunway = runw[i];
                            break;

                        }
                    }
                }

                if (permissionToDescend(height, Port, Runw)) {
                    finalApproachMessage(this, Runw, tijd);
                    Runw->setOccupied(true);
                    Runw->setPermissionToCross(false);
                    confirmMessageSend = false;
                    opperationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    confirmMessageSend = true;
                    opperationTime = 1;
                    return;
                }
            } else {
                requestMessageSend = false;
                if (confirmMessageSend) {
                    waitBeforeDescendConfirmation(this, tijd);
                    logMessage(Airplane::number + " is waiting at a height of " + intToString(height));
                    confirmMessageSend = false;
                    opperationTime = 1;
                    return;
                } else {
                    finalApproachConfirmation(this, Runw, tijd);
                    Airplane::setState("on final approach");
                    currentTask = "descending to 0ft.";

                    if (Airplane::getEngine() == "jet") {
                        opperationTime = cHeightLevelC/cJetDescentionSpeed;
                    } else if (Airplane::getEngine() == "propeller") {
                        opperationTime = cHeightLevelC/cProprellerDescentionSpeed;
                    }
                    return;
                }
            }
        } else {
            currentTask = "landing";
            opperationTime = 2;

            logMessage(Airplane::number + " is landing at Runway" + Runw->getName());
            Airplane::setAirport(Port);
            logMessage("Airplane (" + Airplane::number + ") landed in " + Port->getIata());

            Airplane::setRunway(Runw);
            logMessage("Airplane (" + Airplane::number + ") is now at runway " + Runw->getName() + "\n");

            Airplane::setState("At runway");
            height -= cJetDescentionSpeed;


            ENSURE(Runw == Airplane::getRunway(), "Landed");
        }
    }
    else {
        afterLandingMessage(this, Port, runway, tijd);
        currentTask = "going to gate";
        opperationTime = 1;
        return;

    }

}

void Airplane::takeOff() {
    REQUIRE(currentTask == "taking off" || currentTask == "at holding point", "correct state");
    string tijd = getTime();

    REQUIRE(Airplane::getHeight() == 0, "Plane not on ground");
    if (currentTask == "at holding point") {
        if (!requestMessageSend) {
            holdingShortAtRunway(this, runway, tijd);
            requestMessageSend = true;
            setOpperationTime(1);
            return;
        }

        if (!messageMessageSend) {
            if (!runway->isOccupied() && !runway->getWaitingOnRunway() && !runway->getHoldingShortOccupied() && !runway->getCrossing()) {
                clearedForTakeOffMessage(this, runway, tijd);
                permissiontotakeoff = true;
                messageMessageSend = true;
                runway->setWaitingOnRunway(true);
                runway->setOccupied(true);
                runway->setPermissionToCross(false);
                setOpperationTime(1);
                return;
            } else if (!runway->isOccupied() && !runway->getWaitingOnRunway() && runway->getHoldingShortOccupied() && !runway->getCrossing() && Airplane::waitatrunway) {
                clearedForTakeOffMessage(this, runway, tijd);
                permissiontotakeoff = true;
                messageMessageSend = true;
                runway->setWaitingOnRunway(true);
                runway->setOccupied(true);
                runway->setPermissionToCross(false);
                setOpperationTime(1);
                return;
            } else if (!runway->isOccupied() && !runway->getWaitingOnRunway() && !runway->getHoldingShortOccupied() && runway->getCrossing()) {
                lineUpRunwayMessage(this, runway, tijd);
                messageMessageSend = true;
                waitonrunway = true;
                runway->setWaitingOnRunway(true);
                runway->setOccupied(true);
                setOpperationTime(1);
                return;
            } else if (!runway->isOccupied() && !runway->getWaitingOnRunway() && runway->getHoldingShortOccupied() && runway->getCrossing() && Airplane::waitatrunway) {
                lineUpRunwayMessage(this, runway, tijd);
                messageMessageSend = true;
                waitonrunway = true;
                Airplane::waitatrunway = false;
                runway->setWaitingOnRunway(true);
                runway->setOccupied(true);
                setOpperationTime(1);
                return;
            } else if (!runway->getHoldingShortOccupied() || (runway->getHoldingShortOccupied() && Airplane::waitatrunway)) {
                waitAtRunwayMessage(this, tijd);
                messageMessageSend = true;
                waitatrunway = true;
                runway->setHoldingShortOccupied(true);
                setOpperationTime(1);
                return;
            }
        }
        else {
            if (permissiontotakeoff) {
                clearedForTakeOffConfirmation(this, runway, tijd);
                permissiontotakeoff = false;
                Airplane::setState("At runway");
                currentTask == "taking off";
                requestMessageSend = false;
                messageMessageSend = false;
                if(!alreadylinedup){
                    setOpperationTime(2);;
                }
                else{
                    setOpperationTime(1);
                }
                alreadylinedup = false;
                runway->setHoldingShortOccupied(false);
                return;
            }
            if (waitonrunway) {
                lineUpRunwayConfirmation(this, runway, tijd);
                alreadylinedup = true;
                requestMessageSend = false;
                messageMessageSend = false;
                Airplane::waitonrunway = true;
                Airplane::setState("lined up");
                setOpperationTime(1);
                runway->setHoldingShortOccupied(false);
                return;
            }
            if (waitatrunway) {
                waitAtRunwayConfirmation(this, tijd);
                requestMessageSend = false;
                messageMessageSend = false;
                Airplane::waitatrunway = true;
                setOpperationTime(1);
                return;
            }
        }
    }

    logMessage("Sending airplane " + Airplane::getNumber() + " for departure");

    logMessage("Airplane (" + Airplane::getNumber() + ") is taking off at " + Airplane::getAirport()->getName());

    runway->setOccupied(false);
    runway->setWaitingOnRunway(false);
    runway->setPermissionToCross(true);
    Airplane::waitonrunway = false;

    Airplane::setAirport(NULL);
    Airplane::setRunway(NULL);
    Airplane::setState("Airborne");

    if (Airplane::getEngine() == "propeller"){
        opperationTime = cHeightLevelC;
        height += cProprellerAscentionSpeed;
    }
    else if (Airplane::getEngine() == "jet"){
        opperationTime = cHeightLevelC;
        height += cJetAscentionSpeed;
    }

    ENSURE(runway == NULL && state == "Airborne" && airport == NULL && height != 0, "Airborne");

    currentTask = "taking-Off";

    Airplane::setsimulationFinished(true);
    return;

}

void Airplane::exitPlane(){
    REQUIRE(Airplane::getCurrentTask() == "exit passengers" && Airplane::atGate(), "correct state");

    if (passengers <= 0) {

        passengers = 0;

        logMessage(intToString(passengerCapacity) + " passengers exited " + callsign + " at gate "
                   + intToString(gate) + " of " + airport->getName());

        if(Airplane::getEmergencyInAirport()){
            Airplane::setState("emergency check");
        }
        else{
            Airplane::setState("technical check");

        }
        currentTask = "technical check";
        return;
    }else{
        if (size == "small"){
            opperationTime = cSmall*cBoardingExitingTime;
            passengers -= passengerCapacity/(cSmall*cBoardingExitingTime);
        }else{
            if (size == "medium"){
                opperationTime = cMedium*cBoardingExitingTime;
                passengers -= passengerCapacity/(cMedium*cBoardingExitingTime);
            }else{
                opperationTime = cLarge*cBoardingExitingTime;
                passengers -= passengerCapacity/(cLarge*cBoardingExitingTime);

            }
        }
    }
}

void Airplane::enterPlane(){
    REQUIRE(Airplane::getCurrentTask() == "board passengers" && Airplane::atGate(), "correct state");

    if (passengers >= passengerCapacity) {

        passengers = passengerCapacity;

        logMessage(intToString(passengerCapacity) + " passengers entered " + callsign + " at gate "
                            + intToString(gate) + " of " + airport->getName());

        Airplane::setState("pushback");
        currentTask = "IFR";
        return;
    }else{
        if (size == "small"){
            opperationTime = cSmall*cBoardingExitingTime;
            passengers += passengerCapacity / (cSmall*cBoardingExitingTime);
        }else{
            if (size == "medium"){
                opperationTime = cMedium*cBoardingExitingTime;
                passengers += passengerCapacity / (cMedium*cBoardingExitingTime);

            }else{
                opperationTime = cLarge*cBoardingExitingTime;
                passengers += passengerCapacity / (cLarge*cBoardingExitingTime);

            }
        }
    }
}

void Airplane::technicalCheck(){
    REQUIRE(Airplane::getCurrentTask() == "technical check" && Airplane::atGate(), "correct state");

    Airplane::emergencyInAirport = false;
    if (!technicalChecked && size != "small"){
        if (Airplane::getSize() == "medium") {
            opperationTime = cMedium-1;
        } else if (Airplane::getSize() == "large") {
            opperationTime = cLarge-1;
        }
        technicalChecked = true;
        return;
    }

    logMessage(getNumber() + " has been checked for technical malfunction");
    if (emergencyInAirport){
        Airplane::setState("emergency refuel");
    }
    else {
        if (fuel == fuelCapacity){
            currentTask = "board passengers";
            Airplane::setState("board passengers");
        }else{
            Airplane::setState("refuel");
            Airplane::setOpperationTime(ceil((fuelCapacity - fuel)/ cFuelPerMinute));
            currentTask = "refueling";
        }
    }

    return;
}

void Airplane::refuel() {
    REQUIRE(Airplane::getCurrentTask() == "refueling" && atGate(), "correct state");

    logMessage(getNumber() + " has been refueled");

    if (emergencyInAirport) {
        currentTask = "taxi to gate";

    } else {
        Airplane::setState("board passengers");

        // << getTimePassed() << ", " << flightPlan->getDeparture() << endl;
        if (getTimePassed() > flightPlan->getDeparture()) { ;
            currentTask = "board passengers";

        }else{
            currentTask = "idle";
            opperationTime = flightPlan->getDeparture() - getTimePassed();
        }

    }

    Airplane::setFuel(Airplane::getFuelCapacity());

    return;

}

void Airplane::descend() {

    if (engine == "jet"){
        height -= cJetDescentionSpeed;


    }else{
        height -= cProprellerDescentionSpeed;

    }

}

void Airplane::ascend() {
    if (engine == "jet"){
        height += cJetAscentionSpeed;

    }else{
        height += cProprellerAscentionSpeed;

    }

    if (height >= cHeightLevelB){
        currentTask = "finished";

    }

}

//simulation

void Airplane::initSimulation(Airport *Port) {
    Airplane::setsimulationFinished(false);
    Airplane::onitsway = false;
    Airplane::waitonrunway = false;
    Airplane::waitatrunway = false;
    Airplane::requestMessageSend = false;
    Airplane::messageMessageSend = false;
    Airplane::confirmMessageSend = false;
    Airplane::technicalChecked = false;

    for (unsigned int i = 0; i < Port->getRunways().size(); i++) {
        Port->getRunways()[i]->setPermissionToCross(true);
        Port->getRunways()[i]->setonItsWay(false);
        Port->getRunways()[i]->setWaitingOnRunway(false);
        Port->getRunways()[i]->setHoldingShortOccupied(false);
    }
    if (flightPlan != NULL) {
        if (getState() == "Approaching") {
            Airplane::setHeight(cHeightLevelA);
            opperationTime = flightPlan->getArrival();
            currentTask = "try to land";


        }

        if (getState() == "Gate") {

            Airplane::setHeight(0);
            Airplane::setFuel(0);
            Airplane::setPassengers(0);

            opperationTime = flightPlan->getDeparture();
            currentTask = "technical check";

            setAirport(Port);
            setGate(Port->getFreeGates()[0]);
            Port->setGateOccupied(0, true);

        }
    }else{
        currentTask = "finished";

    }

}

void Airplane::execTask(Airport* Port) {
    opperationTime -= 1;

    if (currentTask == "try to land" || currentTask == "descending to 5000ft." || currentTask == "descending to 3000ft." || currentTask == "descending to 0ft." || currentTask == "landing"){
        land(Port);
    } else if (currentTask == "emergency crash" || currentTask == "emergency landing" || currentTask == "crash"){
        emergencyLanding(Port);
    } else if(currentTask == "IFR" || currentTask == "pushback" || currentTask == "request taxi"){
        pushBack();
    } else if(currentTask == "going to runway"){
        taxiToRunway();
    } else if(currentTask == "going to gate"){
        taxiToGate();
    } else if(currentTask == "taking off" || currentTask == "at holding point"){
        takeOff();
    } else if(currentTask == "exit passengers"){
        exitPlane();
    } else if(currentTask == "board passengers"){
        enterPlane();
    } else if(currentTask == "technical check"){
        technicalCheck();
    } else if(currentTask == "refueling"){
        refuel();
    }else if (currentTask == "idle"){
        currentTask = "board passengers";

    }



}

bool Airplane::notFinished(Airport* Port) {
    return !(currentTask == "finished");

}

void Airplane::continueTask() {

    if (currentTask == "refueling"){
        if (fuel + cFuelPerMinute < fuelCapacity) {
            fuel += cFuelPerMinute;

        }else{
            fuel = fuelCapacity;
            opperationTime = 1;

        }
        return;
    }

    if (currentTask == "board passengers"){
        if (size == "small") {
            if (passengers + passengerCapacity / (cSmall*cBoardingExitingTime) <= passengerCapacity) {
                passengers += passengerCapacity / (cSmall*cBoardingExitingTime);
                return;
            }


        }else if (size == "medium"){
            if (passengers + passengerCapacity / (cMedium*cBoardingExitingTime) <= passengerCapacity) {
                passengers += passengerCapacity / (cMedium*cBoardingExitingTime);
                return;
            }


        }else if (size == "large"){
            if (passengers + passengerCapacity/(cLarge*cBoardingExitingTime) <= passengerCapacity) {
                passengers += passengerCapacity / (cLarge*cBoardingExitingTime);
                return;
            }

        }
        passengers = passengerCapacity;
        opperationTime = 1;
    }

    if (currentTask == "exit passengers"){
        if (size == "small") {
            if (passengers - passengerCapacity / (cSmall*cBoardingExitingTime) >= 0) {
                passengers -= passengerCapacity / (cSmall*cBoardingExitingTime);
                return;
            }


        }else if (size == "medium"){
            if (passengers - passengerCapacity / (cMedium*cBoardingExitingTime) >= 0) {
                passengers -= passengerCapacity / (cMedium*cBoardingExitingTime);
                return;
            }


        }else if (size == "large"){
            if (passengers - passengerCapacity/(cLarge*cBoardingExitingTime) >= 0) {
                passengers -= passengerCapacity / (cLarge*cBoardingExitingTime);
                return;
            }

        }
        passengers = 0;
        opperationTime = 1;

    }

    if (currentTask == "taking-Off"){
        Airplane::ascend();

    }

    if (currentTask == "descending to 5000ft." || currentTask == "descending to 3000ft." || currentTask == "descending to 0ft."){
        Airplane::descend();

    }



}

//Output

void Airplane::printInfo() {
    cout << Airplane::getInfo() << endl;

}

string Airplane::getInfo() {
    string str;
    str = "\nAirplane:\t" + callsign + " (" + number +  ")\n"
          + "->model:\t" + model +"\n"
          + "->type:\t" + type + "\n"
          + "->engine:\t" + engine + "\n"
          + "->size:\t" + size + "\n";

    return str;
}










