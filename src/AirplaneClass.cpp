//
// Created by oliviervh on 01.03.18.
//

#include "AirplaneClass.h"
#include <string>

string gTime;
int gTimePassed;
int gStartingTime;


Airplane::Airplane() {
    gate = -1;
    runway = NULL;
    passengers = 125;
    passengerCapacity = 125;
    taxiPoint = "";
    taxiCrossing = "";
    flightPlan = new FlightPlan();

}

//getters & setters
const string &Airplane::getNumber() const {
    return number;
}
void Airplane::setNumber(const string &number) {
    Airplane::number = number;

}

const string &Airplane::getCallsign() const {
    return callsign;
}
void Airplane::setCallsign(const string &callsign) {
    Airplane::callsign = callsign;
}

const string &Airplane::getModel() const {
    return model;
}
void Airplane::setModel(const string &model) {
    Airplane::model = model;

}

const string &Airplane::getState() const {
    return state;
}
void Airplane::setState(const string &state) {
    Airplane::state = state;
}

int Airplane::getFuel() const {
    return fuel;
}
void Airplane::setFuel(int fuel) {
    Airplane::fuel = fuel;
}

int Airplane::getHeight() const {
    return height;
}
void Airplane::setHeight(int height) {
    Airplane::height = height;
}

int Airplane::getFuelCapacity() const {
    return fuelCapacity;
}
void Airplane::setFuelCapacity(int fuelCapacity) {
    Airplane::fuelCapacity = fuelCapacity;
}

int Airplane::getPassengers() const {
    return passengers;
}
void Airplane::setPassengers(int passengers) {
    Airplane::passengers = passengers;
}

int Airplane::getPassengerCapacity() const {
    return passengerCapacity;
}
void Airplane::setPassengerCapacity(int passengerCapacity) {
    Airplane::passengerCapacity = passengerCapacity;
}

Airport *Airplane::getAirport() const {
    return airPort;
}
void Airplane::setAirport(Airport *airPort){
    Airplane::airPort = airPort;

}

const string &Airplane::getType() const {
    return type;
}
void Airplane::setType(const string &type) {
    REQUIRE(validPlaneType(type), "Valid type?");
    Airplane::type = type;
}

const string &Airplane::getEngine() const {
    return engine;
}
void Airplane::setEngine(const string &engine) {
    REQUIRE(validEngineType(engine), "valid Engine");
    Airplane::engine = engine;
}

const string &Airplane::getSize() const {
    return size;
}
void Airplane::setSize(const string &size) {
    REQUIRE(validSize(size), "valid size");
    Airplane::size = size;

}

int Airplane::getOpperationTime() const {
    return opperationTime;
}
void Airplane::setOpperationTime(int opperationTime) {
    Airplane::opperationTime = opperationTime;
}

Runway *Airplane::getRunway() const {
    return runway;
}
void Airplane::setRunway(Runway *runway) {

    Airplane::runway = runway;

}

int Airplane::getGate() const {
    return gate;
}
void Airplane::setGate(int gate) {
    Airplane::gate = gate;
}

Airport *Airplane::getAirPort() const {
    return airPort;
}
void Airplane::setAirPort(Airport *airPort) {
    Airplane::airPort = airPort;
}

Runway *Airplane::getAttemptRunway() const {
    return attemptRunway;
}
void Airplane::setAttemptRunway(Runway * attemptRunway) {
    Airplane::attemptRunway = attemptRunway;
}

FlightPlan *Airplane::getFlightPlan() const {
    return flightPlan;
}
void Airplane::setFlightPlan(FlightPlan *flightPlan) {
    Airplane::flightPlan = flightPlan;
}

TaxiRoute *Airplane::getTaxiRoute() const {
    return taxiRoute;
}
void Airplane::setTaxiRoute(TaxiRoute *taxiRoute) {
    Airplane::taxiRoute = taxiRoute;
}

const string &Airplane::getTaxiPoint() const {
    return taxiPoint;
}
void Airplane::setTaxiPoint(const string &taxiPoint) {
    Airplane::taxiPoint = taxiPoint;
}

const string &Airplane::getTaxiCrossing() const {
    return taxiCrossing;
}
void Airplane::setTaxiCrossing(const string &taxiCrossing) {
    Airplane::taxiCrossing = taxiCrossing;
}

bool Airplane::isIFRAuthorized() const {
    return IFRAuthorized;
}
void Airplane::setIFRAuthorized(bool IFRAuthorized) {
    Airplane::IFRAuthorized = IFRAuthorized;
}

bool Airplane::isPushback() const {
    return pushback;
}
void Airplane::setPushback(bool pushback) {
    Airplane::pushback = pushback;
}

bool Airplane::isRequestMessageSend() const {
    return requestMessageSend;
}
void Airplane::setRequestMessageSend(bool requestMessageSend) {
    Airplane::requestMessageSend = requestMessageSend;
}

bool Airplane::isMessageMessageSend() const {
    return messageMessageSend;
}
void Airplane::setMessageMessageSend(bool messageMessageSend) {
    Airplane::messageMessageSend = messageMessageSend;
}

bool Airplane::isConfirmMessageSend() const {
    return confirmMessageSend;
}
void Airplane::setConfirmMessageSend(bool confirmMessageSend) {
    Airplane::confirmMessageSend = confirmMessageSend;
}

bool Airplane::isTaxiRequest() const {
    return taxiRequest;
}
void Airplane::setTaxiRequest(bool taxiRequest) {
    Airplane::taxiRequest = taxiRequest;
}

bool Airplane::isRequest() const {
    return request;
}
void Airplane::setRequest(bool request) {
    Airplane::request = request;
}

bool Airplane::isRequestWait() const {
    return requestWait;
}
void Airplane::setRequestWait(bool requestWait) {
    Airplane::requestWait = requestWait;
}

bool Airplane::isEmergencyInAirport() const {
    return emergencyInAirport;
}
void Airplane::setEmergencyInAirport(bool emergencyInAirport) {
    Airplane::emergencyInAirport = emergencyInAirport;
}

void Airplane::setSquawkCode(string code){

    int index;

    if (code == ""){
        if (type == "private"){
            if (size == "small"){
                index = 0;

            }else{
                index = 1;

            }
        }
        if (type == "airline"){
            if (size == "medium"){
                if (engine == "propeller"){
                    index = 2;

                }else{
                    index = 3;

                }

            }else{
                index = 4;

            }
        }
        if (type == "military"){
            index = 5;

        }
        if (type == "emergency"){
            index = 6;

        }

        if (index == 0) {
            squawkCode == "0001-0777";

        }else{
            squawkCode == intToString(index) + "000-" + intToString(index) + "777";

        }

    }else{
        squawkCode = code;

    }
}
const string &Airplane::getSquawkCode() const {
    return squawkCode;
}

void setTime(string time){
    gTime = time;
};
string getTime(){

    return gTime;

};

void setTimePassed(int time){
    gTimePassed = time;

}
int getTimePassed(){
    return gTimePassed;

}

void setStartingTime(int time){
    gStartingTime = time;

}
int getStartingTime(){
    return gStartingTime;

}

string Airplane::getDestination() {
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
        Airplane::setState(Value);
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
        int i;
        istringstream(Value) >> i;
        Airplane::setPassengers(i);
        Airplane::setPassengerCapacity(i);
        return;
    }

    else if (Type == "height"){
        int i;
        istringstream(Value) >> i;
        Airplane::setHeight(i);
        return;
    }

    else if (Type == "fuel"){
        int i;
        istringstream(Value) >> i;
        Airplane::setFuel(i);
        Airplane::setFuelCapacity(i);
        return;
    }

    else if (Type == "gate"){
        int i;
        istringstream(Value) >> i;
        Airplane::setGate(i);
        return;
    }

    else {
        REQUIRE(false, "Valid Type");
    }

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
                    if (runway->getLength() >= 3000 && runway->getType() == "asphalt"){
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
            if (Runw->getLength() >= 3000 && Runw->getType() == "asphalt" && !Runw->isOccupied()){
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
        vector<int> t = airPort->getFreeGates();
        if (t.size() == 0){
            return false;
        }
        return true;

    }

    if (!(gate >= 0 && gate < airPort->getGates())){
        return false;
    }
    if (airPort->getGateOccupied(gate)){
        return false;
    }

    return true;

}

bool Airplane::validRunway(Runway* Runw){
    if (Runw == NULL){
        vector<int> runw = airPort->getFreeRunways();
        for (int i = 0; (unsigned)i<runw.size(); i++){
            Runway *runway = airPort->getRunways()[i];
            if (getSize() == "small"){
                if (getEngine() == "propeller"){
                    if (runway->getLength() >= 500){
                        return true;
                    }
                    continue;
                }
                else if (getEngine() == "jet"){
                    if (runway->getLength() >= 1000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (getSize() == "medium"){
                if (getEngine() == "propeller"){
                    if (runway->getLength() >= 1000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (getEngine() == "jet"){
                    if (runway->getLength() >= 2000 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
            }
            else if (getSize() == "large"){
                if (getEngine() == "propeller"){
                    if (runway->getLength() >= 1500 && runway->getType() == "asphalt"){
                        return true;
                    }
                    continue;
                }
                else if (getEngine() == "jet"){
                    if (runway->getLength() >= 3000 && runway->getType() == "asphalt"){
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
            if (Runw->getLength() >= 500){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine() == "jet"){
            if (Runw->getLength() >= 1000 && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (getSize() == "medium"){
        if (getEngine() == "propeller"){
            if (Runw->getLength() >= 1000 && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine() == "jet"){
            if (Runw->getLength() >= 2000 && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (getSize() == "large"){
        if (getEngine() == "propeller"){
            if (Runw->getLength() >= 1500 && Runw->getType() == "asphalt"){
                return true;
            }
            else{
                return false;
            }
        }
        else if (getEngine() == "jet"){
            if (Runw->getLength() >= 3000 && Runw->getType() == "asphalt"){
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

    return (airPort != NULL);

}

bool Airplane::atGate() {

    return state == "Standing at gate" && gate >= 0;


}

bool Airplane::readyForTakeOff() {
    return (isReadyForDeparture() && Airplane::airPort != NULL && Airplane::runway != NULL && Airplane::state == "At runway");
}

bool Airplane::permissionToDescend(int height, Airport* Port, Runway* Runway){
    if (height == 10000){
        if (Port->getWait5000() == NULL){
            Port->setWait5000(this);
            return true;
        }
        else{
            return false;
        }
    }
    else if (height == 5000){
        if (Port->getWait3000() == NULL){
            Port->setWait5000(NULL);
            Port->setWait3000(this);
            return true;
        }
        else{
            return false;
        }
    }
    else if (height == 3000){
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



// functies

void Airplane::toGate(int gate) {

    REQUIRE(Airplane::validGate(gate), "valid gate index");
    REQUIRE(Airplane::atAirport(), "At airport");

    if (gate == -1){
        vector<int> t = Airplane::getAirport()->getFreeGates();

        gate = t[0];

    }

    if (Airplane::getGate() != -1){  // if the plane was at another gate...
        Airplane::getAirport()->setGateOccupied(Airplane::getGate(), false);

    }

    if (runway != NULL) {   // if the plane was at a runway...
        runway->setOccupied(false);
        runway = NULL;
    }

    // Set new gate
    Airplane::setGate(gate);
    Airplane::getAirport()->setGateOccupied(Airplane::getGate(), true);

    state = "Standing at gate";

}

void Airplane::pushBack(Runway* Runw) {
    REQUIRE(currentTask == "IFR" || currentTask == "pushback" || currentTask == "request taxi", "correct state");

    string tijd = getTime();

    if (currentTask == "IFR") {
        REQUIRE(atAirport(), "At airport");
        REQUIRE(validRunway(Runw), "Valid runway");

        if (!requestMessageSend) {

            if (Runw == NULL) {
                vector<int> runw = airPort->getFreeRunways();
                for (int i = 0; (unsigned) i < runw.size(); i++) {
                    if (validRunway(airPort->getRunways()[i])) {
                        attemptRunway = airPort->getRunways()[i];
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
            Airplane::setState("Waiting for pushback");
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
                opperationTime = 1;
            }
            else if (Airplane::getSize() == "medium"){
                opperationTime = 2;
            }
            else if (Airplane::getSize() == "large"){
                opperationTime = 3;
            }
            Airplane::setState("Waiting for taxirequest");
            currentTask = "request taxi";
            return;
        }
    }

    else if(currentTask == "request taxi") {
        Airplane::setState("Waiting for taxi to runway");
        currentTask = "taxi to runway";
        readyToTaxiMessage(this, tijd);
        return;
    }

}

void Airplane::taxiToRunway(Runway* runw){
    REQUIRE(currentTask == "going to runway", "correct state");
    if (runw == NULL){
        runw = Airplane::attemptRunway;
    }
    REQUIRE(!runw->getWachtaanRunway(), "Runway fully occupied.");
    if (gate != -1){
        airPort->setGateOccupied(gate, false);
        gate = -1;
    }
    string tijd = getTime();
    taxiRoute = runw->getTaxiRoute();
    if (taxiPoint == "" && taxiCrossing == ""){
        taxiPoint = taxiRoute->getTaxiPoints()[0];
        return;
    }
    if (taxiPoint != ""){
        for (unsigned int i=0; i < taxiRoute->getTaxiPoints().size(); i++){
            if (taxiPoint == taxiRoute->getTaxiPoints()[i]){
                if (i == taxiRoute->getTaxiPoints().size()-1){
                    if (!messageMessageSend){
                        toRunwayMessage(this, runw, taxiPoint, tijd);
                        messageMessageSend = true;
                        return;
                    }
                    else if (!confirmMessageSend){
                        toRunwayConfirmation(this, runw, taxiPoint, tijd);
                        confirmMessageSend = true;
                        return;
                    }
                    else{
                        messageMessageSend = false;
                        confirmMessageSend = false;
                        runway = runw;
                        opperationTime = 1;
                        Airplane::setState("Waiting for departure");
                        currentTask == "at holding point";
                        return;
                    }
                }
                else if (!messageMessageSend) {
                    toHoldingPointMessage(this, taxiRoute->getTaxiCrossings()[i], taxiPoint, tijd);
                    messageMessageSend = true;
                    return;
                }
                else  if (!confirmMessageSend) {
                    toHoldingPointConfirmation(this, taxiRoute->getTaxiCrossings()[i], taxiPoint, tijd);
                    confirmMessageSend = true;
                    return;
                }
                else{
                    taxiPoint = "";
                    taxiCrossing = taxiRoute->getTaxiCrossings()[i];
                    messageMessageSend = false;
                    confirmMessageSend = false;
                    opperationTime = 5;
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
                    taxiCrossing = "";
                    taxiPoint = taxiRoute->getTaxiPoints()[i+1];
                    requestMessageSend = false;
                    messageMessageSend = false;
                    confirmMessageSend = false;
                    return;
                }
            }

        }
    }
}

void Airplane::taxiToGate(int gate){
    REQUIRE(currentTask == "going to gate", "correct state");
    REQUIRE(validGate(gate), "valid gate number");

    string tijd = getTime();
    if (runway != NULL){
        taxiRoute = runway->getTaxiRoute();
        runway->setOccupied(false);
        runway = NULL;
    }

    if (taxiPoint == "" && taxiCrossing == ""){
        taxiPoint = taxiRoute->getTaxiPoints()[taxiRoute->getTaxiPoints().size()-1];
        return;
    }
    if (taxiPoint != ""){
        for (unsigned int i=0; i < taxiRoute->getTaxiPoints().size(); i++){
            if (taxiPoint == taxiRoute->getTaxiPoints()[i]){
                if (i == 0){
                    if (!messageMessageSend){
                        toGateMessage(this, gate, taxiPoint, tijd);
                        messageMessageSend = true;
                        return;
                    }
                    else if (!confirmMessageSend){
                        toGateConfirmation(this, gate, taxiPoint, tijd);
                        confirmMessageSend = true;
                        return;
                    }
                    else{
                        messageMessageSend = false;
                        confirmMessageSend = false;
                        setGate(gate);
                        airPort->setGateOccupied(gate, true);
                        opperationTime = 1;
                        Airplane::setState("Waiting for exit passengers");
                        currentTask == "exit passengers";
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
                    taxiCrossing = taxiRoute->getTaxiCrossings()[i-1];
                    messageMessageSend = false;
                    confirmMessageSend = false;
                    opperationTime = 5;
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
                    taxiCrossing = "";
                    taxiPoint = taxiRoute->getTaxiPoints()[i];
                    requestMessageSend = false;
                    messageMessageSend = false;
                    confirmMessageSend = false;
                    return;
                }
            }

        }
    }
}

void Airplane::emergencyLanding(Airport* Port){
    REQUIRE(currentTask == "emergency crash" || currentTask == "emergency landing" || currentTask == "crash", "correct state");

    string tijd = getTime();
    if(currentTask != "emergency crash" || currentTask != "emergency landing") {
        if (Airplane::getState() != "Crashing") {
            REQUIRE(Airplane::getFuel() == 0, "Plane is out of fuel");
            REQUIRE(Airplane::getState() == "Airborne", "Plane is out of fuel");
        }

        Airplane::setState("Crashing");

        if (!requestMessageSend) {
            if (height >= 3000) {
                EmergencyAbove3000ftRequest(this, Port, tijd);
                emergencyInAirport = true;
                requestMessageSend = true;
                if (Airplane::getEngine() == "jet") {
                    Airplane::setHeight(Airplane::getHeight()-1000);
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::setHeight(Airplane::getHeight()-500);
                }
                opperationTime = 1;
                return;
            } else {
                EmergencyBelow3000ftRequest(this, Port, tijd);
                emergencyInAirport = false;
                requestMessageSend = true;
                if (Airplane::getEngine() == "jet") {
                    Airplane::setHeight(Airplane::getHeight()-1000);
                } else if (Airplane::getEngine() == "propeller") {
                    Airplane::setHeight(Airplane::getHeight()-500);
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
                    opperationTime = Airplane::getHeight() / 1000;
                } else if (Airplane::getEngine() == "propeller") {
                    opperationTime = Airplane::getHeight() / 500;
                }
                Airplane::setHeight(0);
                return;
            } else {
                EmergencyBelow3000ftMessage(this, tijd);
                currentTask = "emergency crash";
                if (Airplane::getEngine() == "jet") {

                    opperationTime = Airplane::getHeight() / 1000;
                } else if (Airplane::getEngine() == "propeller") {
                    opperationTime = Airplane::getHeight() / 500;
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
            Airplane::setState("Waiting for exit passengers");
        }
        else{
            Airplane::setState("Waiting for exit passengers");
        }
        requestMessageSend = false;
        currentTask = "exit passengers";
        return;
    }
}

void Airplane::land(Airport *Port, Runway* Runw) {
    REQUIRE(currentTask == "try to land" || currentTask == "landing" || currentTask == "descending to 5000ft."  || currentTask == "descending to 3000ft." || currentTask == "descending to 0ft.", "correct task");

    string tijd = getTime();
    if (currentTask == "try to land") {
        if (state != "Approaching") {
            REQUIRE(state == "Airborne", "Plane is not airborne");
            REQUIRE(validLandingSpot(Port, Runw), "Valid landing spot");

            Airplane::setState("Approaching");

            if (Runw == NULL) {
                inputMessage("Preparing airplane (" + Airplane::number + ") for landing in " + Port->getName());

                vector<Runway *> runw = Port->getRunways();

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

        notificationMessage(
                Airplane::number + " is approaching " + Port->getName() + " at " + intToString(height) + "ft.");
        if (height == 10000) {
            if (!request) {
                request = true;
                if (permissionToDescend(height, Port, Runw)) {
                    descendTo5000ftMessage(this, tijd);
                    requestWait = false;
                    opperationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    requestWait = true;
                    opperationTime = 1;
                    return;
                }
            } else {
                request = false;
                if (requestWait) {
                    waitBeforeDescendConfirmation(this, tijd);
                    requestWait = false;
                    opperationTime = 1;
                    return;
                } else {
                    descendTo5000ftConfirmation(this, tijd);
                    currentTask = "descending to 5000ft.";
                    Airplane::setHeight(5000);
                    if (Airplane::getEngine() == "jet") {
                        opperationTime = 6;
                    } else if (Airplane::getEngine() == "propeller") {
                        opperationTime = 11;
                    }
                    return;
                }
            }
        }
        if (height == 5000) {
            if (!request) {
                request = true;
                if (permissionToDescend(height, Port, Runw)) {
                    descendTo3000ftMessage(this, tijd);
                    requestWait = false;
                    opperationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    requestWait = true;
                    opperationTime = 1;
                    return;
                }
            } else {
                request = false;
                if (requestWait) {
                    waitBeforeDescendConfirmation(this, tijd);
                    actionMessage(Airplane::number + " is waiting at a height of " + intToString(height));
                    requestWait = false;
                    opperationTime = 1;
                    return;
                } else {
                    descendTo3000ftConfirmation(this, tijd);
                    currentTask = "descending to 3000ft.";
                    Airplane::setHeight(3000);
                    if (Airplane::getEngine() == "jet") {
                        opperationTime = 3;
                    } else if (Airplane::getEngine() == "propeller") {
                        opperationTime = 5;
                    }
                    return;
                }
            }
        }
        if (height == 3000) {
            if (!request) {
                request = true;
                if (permissionToDescend(height, Port, Runw)) {
                    finalApproachMessage(this, Runw, tijd);
                    Runw->setOccupied(true);
                    requestWait = false;
                    opperationTime = 1;
                    return;
                } else {
                    waitBeforeDescendMessage(this, tijd);
                    requestWait = true;
                    opperationTime = 1;
                    return;
                }
            } else {
                request = false;
                if (requestWait) {
                    waitBeforeDescendConfirmation(this, tijd);
                    actionMessage(Airplane::number + " is waiting at a height of " + intToString(height));
                    requestWait = false;
                    opperationTime = 1;
                    return;
                } else {
                    finalApproachConfirmation(this, Runw, tijd);
                    Airplane::setState("on final approach");
                    currentTask = "descending to 0ft.";
                    Airplane::setHeight(0);
                    if (Airplane::getEngine() == "jet") {
                        opperationTime = 4;
                    } else if (Airplane::getEngine() == "propeller") {
                        opperationTime = 7;
                    }
                    return;
                }
            }
        } else {
            currentTask = "landing";
            opperationTime = 2;

            actionMessage(Airplane::number + " is landing at Runway" + Runw->getName());
            Airplane::setAirport(Port);
            notificationMessage("Airplane (" + Airplane::number + ") landed in " + Port->getIata());

            Airplane::setRunway(Runw);
            notificationMessage("Airplane (" + Airplane::number + ") is now at runway " + Runw->getName() + "\n");

            Airplane::setState("At runway");


            ENSURE(Runw == Airplane::getRunway(), "Landed");
        }
    }
    else {
            afterLandingMessage(this, Port, Runw, tijd);
            currentTask = "taxi to gate";
            opperationTime = 1;
            return;

    }

}

void Airplane::takeOff() {
    REQUIRE(currentTask == "taking off" || currentTask == "at holding point", "correct state");
    string tijd = getTime();

    cout << "request: " << Airplane::requestMessageSend << endl;
    cout << "message: " << Airplane::messageMessageSend << endl;
    cout << "confirm: " << Airplane::confirmMessageSend << endl;

    REQUIRE(readyForTakeOff(), "Ready for take off");
    REQUIRE(Airplane::getHeight() == 0, "Plane not on ground");
    if (currentTask == "at holding point") {
        if (!requestMessageSend) {
            holdingShortAtRunway(this, runway, tijd);
            requestMessageSend = true;
            return;
        }

        if (!messageMessageSend) {

            if (!runway->isOccupied() && !runway->getWachtopRunway() && !runway->getWachtaanRunway() && !runway->getCrossing()) {
                clearedForTakeOffMessage(this, runway, tijd);
                permissiontotakeoff = true;
                messageMessageSend = true;
                runway->setWachtopRunway(true);
                runway->setOccupied(true);
                runway->setPermissionToCross(false);
                return;
            } else if (!runway->isOccupied() && !runway->getWachtopRunway() && runway->getWachtaanRunway() && !runway->getCrossing() && Airplane::waitatrunway) {
                clearedForTakeOffMessage(this, runway, tijd);
                permissiontotakeoff = true;
                messageMessageSend = true;
                runway->setWachtopRunway(true);
                runway->setOccupied(true);
                runway->setPermissionToCross(false);
                return;
            } else if (!runway->isOccupied() && !runway->getWachtopRunway() && !runway->getWachtaanRunway() && runway->getCrossing()) {
                lineUpRunwayMessage(this, runway, tijd);
                messageMessageSend = true;
                waitonrunway = true;
                runway->setWachtopRunway(true);
                runway->setOccupied(true);
                return;
            } else if (!runway->isOccupied() && !runway->getWachtopRunway() && runway->getWachtaanRunway() && runway->getCrossing() && Airplane::waitatrunway) {
                lineUpRunwayMessage(this, runway, tijd);
                messageMessageSend = true;
                waitonrunway = true;
                Airplane::waitatrunway = false;
                runway->setWachtaanRunway(false);
                runway->setWachtopRunway(true);
                runway->setOccupied(true);
                return;
            } else if (!runway->getWachtaanRunway()) {
                waitAtRunwayMessage(this, tijd);
                messageMessageSend = true;
                waitatrunway = true;
                runway->setWachtaanRunway(true);
                return;
            }
            cout << "isoccupied" << runway->isOccupied() <<endl;
            cout << "wachtop " << runway->getWachtopRunway() <<endl;
            cout << "wachtaan " << runway->getWachtaanRunway() <<endl;
            cout << "planewachtop " << Airplane::waitonrunway <<endl;
            cout << "planewachtaan " << Airplane::waitatrunway <<endl;
            cout << "loopend" << endl;
        }
        else {
            if (permissiontotakeoff) {
                clearedForTakeOffConfirmation(this, runway, tijd);
                permissiontotakeoff = false;
                currentTask == "taking off";
                requestMessageSend = false;
                messageMessageSend = false;
                if(!alreadylinedup){
                    opperationTime = 2;
                }
                alreadylinedup = false;
                return;
            }
            if (waitonrunway) {
                lineUpRunwayConfirmation(this, runway, tijd);
                alreadylinedup = true;
                waitonrunway = false;
                requestMessageSend = false;
                messageMessageSend = false;
                Airplane::waitonrunway = true;
                return;
            }
            if (waitatrunway) {
                waitAtRunwayConfirmation(this, tijd);
                waitatrunway = false;
                requestMessageSend = false;
                messageMessageSend = false;
                Airplane::waitatrunway = true;
                return;
            }
        }
    }

    inputMessage("Sending airplane " + Airplane::getNumber() + " for departure");

    notificationMessage("Airplane (" + Airplane::getNumber() + ") is taking off at " + Airplane::getAirport()->getName());

    while (height < 5000) {

        actionMessage("Airplane (" + Airplane::getNumber() + ") ascended to " + intToString(height) + "ft");
        height += 1000;

    }

    notificationMessage("Airplane (" + Airplane::getNumber() + ") has left " + Airplane::getAirport()->getName() + "\n");
    runway->setOccupied(false);
    runway->setWachtopRunway(false);
    Airplane::waitonrunway = false;

    Airplane::setAirport(NULL);
    Airplane::setRunway(NULL);
    Airplane::setState("Airborne");

    if (Airplane::getEngine() == "propeller"){
        opperationTime = 3;
    }
    else if (Airplane::getEngine() == "jet"){
        opperationTime = 2;
    }

    ENSURE(runway == NULL && state == "Airborne" && airPort == NULL && height >= 5000, "Airborne");

    cout << "takeoff started" << endl;

    cout << "finished" << endl;

    currentTask = "flying";

}

void Airplane::exitPlane(){
    REQUIRE(currentTask == "exit passengers", "correct state");

    opperationTime = ceil(Airplane::getPassengers()/2);
    passengers = 0;

    if (emergencyInAirport) {
        notificationMessage(passengerCapacity + " passengers exited " + callsign + " from the emergency exit");
    }
    else{
        notificationMessage(passengerCapacity + " passengers exited " + callsign);
    }

    Airplane::setState("Waiting for technical check");
    currentTask = "technical check";
    return;
}

void Airplane::enterPlane(){
    REQUIRE(currentTask == "board passengers", "correct state");

    opperationTime = ceil(Airplane::getPassengers()/2);
    passengers = passengerCapacity;

    notificationMessage(passengerCapacity + " passengers exited " + callsign + " at gate "
                        + intToString(gate) + " of " + airPort->getName());

    Airplane::setState("Waiting for IFR");
    currentTask = "IFR";
    return;
}

void Airplane::technicalCheck(){
    REQUIRE(currentTask == "technical check", "correct state");

    if (Airplane::getSize() == "small"){
        opperationTime = 1;
    }
    else if (Airplane::getSize() == "medium"){
        opperationTime = 2;
    }
    else if (Airplane::getSize() == "large"){
        opperationTime = 3;
    }
    notificationMessage(getNumber() + " has been checked for technical malfunction");
    Airplane::setState("Waiting for refuel");
    currentTask = "refueling";
    return;
}

void Airplane::refuel() {
    REQUIRE(currentTask == "refueling", "correct state");

    opperationTime = ceil(fuelCapacity / 10000);
    notificationMessage(getNumber() + " has been refueled");

    if (emergencyInAirport) {
        Airplane::setState("Waiting for taxi to gate");
        currentTask = "taxi to gate";
    } else {
        Airplane::setState("Waiting for board passengers");
        currentTask = "board passengers";
    }


    return;
}




//simulation
void Airplane::finishtask(Airport* Port) {
    // Finilise the current task
    // set Airport after landing
    // ...

}

void Airplane::nextTask(Airport* Port) {

    if (currentTask == "flying"){
        if (currentTask != "idle" && currentTask != "IFR"){
            afterLanding();

        }else{
            if (currentTask != "IFR"){
                prepareForDeparture();

            }else{
                if(currentTask == ""){


                }

            }
        }
    }

}

void Airplane::initSimulation(Airport *Port) {
    if (getState() == "Approaching"){
        if (flightPlan != NULL){
            opperationTime = flightPlan->getArrival();

        }

    }

    if (getState() == "Gate"){
        if (flightPlan != NULL) {
            opperationTime = flightPlan->getDeparture();
        }

        setAirport(Port);
        setGate(Port->getFreeGates()[0]);
        Port->setGateOccupied(0, true);
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
        taxiToGate(0);
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
    }



}

bool Airplane::notFinished(Airport* Port) {
    return false;
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



