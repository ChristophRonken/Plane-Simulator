//
// Created by oliviervh on 01.03.18.
//

#include "AirplaneClass.h"
#include <string>

string gTime;
int gTimePassed;
int gStartingTime;


Airplane::Airplane() {
    self = this;
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

bool Airplane::getEmergencyInAirport() const {
    return emergencyInAirport;
}
void Airplane::setEmergencyInAirport(bool emergencyInAirport) {
    Airplane::emergencyInAirport = emergencyInAirport;
}

void Airplane::setSquawkCode(string code){

    int index = 0;

    if (code == ""){
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
        if (Value == "Gate" || Value == "Approaching" )
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

bool Airplane::getsimulationFinished(){
    return Airplane::simulationFinished;
}
void Airplane::setsimulationFinished(bool finished){
    Airplane::simulationFinished = finished;
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
    return (isReadyForDeparture() && Airplane::airPort != NULL && Airplane::runway != NULL && Airplane::state == "Waiting for departure");
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
        currentTask = "going to runway";
        readyToTaxiMessage(this, tijd);
        return;
    }

}

void Airplane::taxiToRunway(Runway* runw){
    if (Airplane::getState() == "Waiting for taxi to runway") {
        Airplane::setState("trying to taxi");
    }

    REQUIRE(currentTask == "going to runway", "correct state");
    if (runw == NULL){
        runw = Airplane::attemptRunway;
    }

    REQUIRE(!runw->getHoldingShortOccupied(), "Runway fully occupied.");
    if (gate != -1){
        airPort->setGateOccupied(gate, false);
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
                        Airplane::setState("Waiting for departure");
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
                            Airplane::setState("crossing");
                            setOpperationTime(1);
                            return;
                        }
                        else{
                            Airplane::setState("waiting at taxicrossing");
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
    REQUIRE(currentTask == "going to gate", "correct state");
    REQUIRE(validGate(gate), "valid gate number");

    string tijd = getTime();
    if (runway != NULL){
        taxiRoute = runway->getTaxiRoute();
        runway->setOccupied(false);
        runway->setPermissionToCross(true);
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
                    if (crossed){
                        taxiCrossing = "";
                        taxiPoint = taxiRoute->getTaxiPoints()[i];
                        requestMessageSend = false;
                        messageMessageSend = false;
                        confirmMessageSend = false;
                        setOpperationTime(5);
                        crossed = false;
                        runway->setPermissionToCross(true);
                        return;
                    }
                    else {
                        if (runway->getPermissionToCross()){
                            crossed = true;
                            runway->setPermissionToCross(false);
                            return;
                        }
                        else{
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
        if (state != "Approaching") {
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

        logMessage(
                Airplane::number + " is approaching " + Port->getName() + " at " + intToString(height) + "ft.");
        if (height == 10000) {
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
            if (!requestMessageSend) {
                requestMessageSend = true;
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

            logMessage(Airplane::number + " is landing at Runway" + Runw->getName());
            Airplane::setAirport(Port);
            logMessage("Airplane (" + Airplane::number + ") landed in " + Port->getIata());

            Airplane::setRunway(Runw);
            logMessage("Airplane (" + Airplane::number + ") is now at runway " + Runw->getName() + "\n");

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

    REQUIRE(readyForTakeOff(), "Ready for take off");
    REQUIRE(Airplane::getHeight() == 0, "Plane not on ground");
    if (currentTask == "at holding point") {
        if (!requestMessageSend) {
            holdingShortAtRunway(this, runway, tijd);
            requestMessageSend = true;
            setOpperationTime(1);
            return;
        }

        if (!messageMessageSend) {
            /*
            cout << "isoccupied" << runway->isOccupied() <<endl;
            cout << "wachtop " << runway->getWaitingOnRunway() <<endl;
            cout << "wachtaan " << runway->getHoldingShortOccupied() <<endl;
            cout << "planewachtop " << Airplane::waitonrunway <<endl;
            cout << "planewachtaan " << Airplane::waitatrunway <<endl;
            cout << "loopend" << endl;
             */

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
        opperationTime = 3000;
        height += 500;
    }
    else if (Airplane::getEngine() == "jet"){
        opperationTime = 3000;
        height += 1000;
    }

    ENSURE(runway == NULL && state == "Airborne" && airPort == NULL && height != 0, "Airborne");

    currentTask = "taking-Off";

    Airplane::setsimulationFinished(true);
    return;

}

void Airplane::exitPlane(){
    REQUIRE(currentTask == "exit passengers", "correct state");

    if (passengers <= 0) {

        passengers = 0;

        //logMessage(passengerCapacity + " passengers exited " + callsign);


        Airplane::setState("Waiting for technical check");
        currentTask = "technical check";
        return;
    }else{
        if (size == "small"){
            opperationTime = 1;
        }else{
            if (size == "medium"){
                opperationTime = 2;

            }else{
                opperationTime = 3;

            }
        }

    }
}

void Airplane::enterPlane(){
    REQUIRE(currentTask == "board passengers", "correct state");

    if (passengers >= passengerCapacity) {

        passengers = passengerCapacity;

        //logMessage(passengerCapacity + " passengers exited " + callsign + " at gate "
          //                  + intToString(gate) + " of " + airPort->getName());

        Airplane::setState("Waiting for IFR");
        currentTask = "IFR";
        return;
    }else{
        if (size == "small"){
            opperationTime = 1;
        }else{
            if (size == "medium"){
                opperationTime = 2;

            }else{
                opperationTime = 3;

            }
        }
    }

}

void Airplane::technicalCheck(){
    REQUIRE(currentTask == "technical check", "correct state");

    Airplane::emergencyInAirport = false;

    if (Airplane::getSize() == "small"){
        opperationTime = 1;
    }
    else if (Airplane::getSize() == "medium"){
        opperationTime = 2;
    }
    else if (Airplane::getSize() == "large"){
        opperationTime = 3;
    }
    //logMessage(getNumber() + " has been checked for technical malfunction");
    Airplane::setState("Waiting for refuel");
    Airplane::setOpperationTime(ceil(fuelCapacity / cFuelPerMinute));
    currentTask = "refueling";
    return;
}

void Airplane::refuel() {
    REQUIRE(currentTask == "refueling", "correct state");
    //cout << fuelCapacity << endl;
    //cout << fuel << endl;

    logMessage(getNumber() + " has been refueled");

    if (emergencyInAirport) {
        Airplane::setState("Waiting for taxi to gate");
        currentTask = "taxi to gate";
    } else {
        Airplane::setState("Waiting for board passengers");

        cout << getTimePassed() << ", " << flightPlan->getDeparture() << endl;

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




//simulation

void Airplane::initSimulation(Airport *Port) {
    Airplane::onitsway = false;
    Airplane::waitonrunway = false;
    Airplane::waitatrunway = false;
    for (unsigned int i = 0; i < Port->getRunways().size(); i++) {
        Port->getRunways()[i]->setPermissionToCross(true);
        Port->getRunways()[i]->setonItsWay(false);
        Port->getRunways()[i]->setWaitingOnRunway(false);
        Port->getRunways()[i]->setHoldingShortOccupied(false);
    }
    if (flightPlan != NULL) {
        if (getState() == "Approaching") {
            Airplane::setHeight(10000);
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
    }else if (currentTask == "idle"){
        currentTask = "board passengers";

    }



}

bool Airplane::notFinished(Airport* Port) {
    return !(currentTask == "finished");

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

void Airplane::boardPassengers() {

    if (opperationTime){

        passengers += (passengerCapacity - passengers)/opperationTime;

    }else{
        passengers = passengerCapacity;

    }

}

void Airplane::exitPassengers() {

    if (opperationTime){

        passengers += (passengerCapacity - passengers)/opperationTime;

    }else{
        passengers = 0;

    }
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

const string &Airplane::getCurrentTask() const {
    return currentTask;
}

void Airplane::setCurrentTask(const string &currentTask) {
    Airplane::currentTask = currentTask;
}

void Airplane::continueTask() {

    if (currentTask == "refueling"){
        if (fuel + cFuelPerMinute < fuelCapacity) {
            fuel += cFuelPerMinute;

        }else{
            fuel = fuelCapacity;

        }
        return;
    }

    if (currentTask == "board passengers"){
        if (passengers + (passengerCapacity - passengers)/opperationTime < passengerCapacity) {
            passengers += ceil((passengerCapacity - passengers)/opperationTime);

        }else{
            passengers = passengerCapacity;

        }
        return;

    }

    if (currentTask == "exit passengers"){
        if (passengers - (passengerCapacity - passengers)/opperationTime > 0) {
            passengers -= ceil((passengerCapacity - passengers)/opperationTime);

        }else{
            passengers = 0;

        }
        return;

    }

    if (currentTask == "taking-Off"){
        ascend();

    }


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
        height += cJetDescentionSpeed;


    }else{
        height += cProprellerDescentionSpeed;

    }

    if (height >= 5000){
        currentTask = "finished";

    }

}



