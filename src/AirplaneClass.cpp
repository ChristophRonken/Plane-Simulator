//
// Created by oliviervh on 01.03.18.
//

#include "AirplaneClass.h"
#include <string>

string gTime;

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

bool Airplane::getReadyForDeparture() const {
    return ReadyForDeparture;
}
void Airplane::setReadyForDeparture(bool ReadyForDeparture) {
    Airplane::ReadyForDeparture = ReadyForDeparture;
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
    Airplane::engine = engine;
}

const string &Airplane::getSize() const {
    return size;
}
void Airplane::setSize(const string &size) {
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
        Airplane::setType(Value);
        return;
    }

    else if (Type == "engine"){
        Airplane::setEngine(Value);
        return;
    }

    else if (Type == "size"){
        Airplane::setSize(Value);
        return;
    }

    else if (Type == "passengers"){
        int i;
        istringstream(Value) >> i;
        Airplane::setPassengers(i);
        return;
    }

    else if (Type == "passengerCap"){
        int i;
        istringstream(Value) >> i;
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
        return;
    }

    else if (Type == "fuelCap"){
        int i;
        istringstream(Value) >> i;
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
        gate = t[0];
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

    if (type == "private" || type == "airline" || type == "military" || "emergency"){
        return true;

    }

    return false;
}
bool Airplane::atAirport() {

    return (airPort != NULL);

}
bool Airplane::atGate() {

    return state == "Standing at gate" && gate >= 0;


}
bool Airplane::readyForTakeOff() {
    return (getReadyForDeparture() && airPort != NULL && Airplane::runway != NULL && Airplane::state == "At runway");
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


// functies
void Airplane::prepareForDeparture() {
    REQUIRE(atGate(), "Standing at gate");

    inputMessage("Preparing airplane (" + getNumber() + ") for departure.");


    notificationMessage(intToString(passengers) + " exited airplane " + getNumber() + " at gate " + intToString(gate) + " of " + airPort->getName() );
    notificationMessage(getNumber() + " has been checked for technical malfunction");
    notificationMessage(getNumber() + " has been refueled");
    notificationMessage(intToString(passengers) + " boarded airplane " + getNumber() + " at gate " + intToString(gate) + " of " + airPort->getName() + "\n" );

    setReadyForDeparture(true);

}

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
}

void Airplane::toRunway(Runway *runway ) {
    string tijd = getTime();
    if (!IFRAuthorized && !requestMessageSend) {
        REQUIRE(atAirport(), "At airport");
        REQUIRE(validRunway(runway), "Valid runway");

        if (runway == NULL) {
            vector<int> runw = airPort->getFreeRunways();
            for (int i = 0; (unsigned) i < runw.size(); i++) {
                Runway *runwaycpy = airPort->getRunways()[i];
                if (validRunway(runwaycpy)) {
                    runway = runwaycpy;
                    attemptRunway = runway;
                    break;
                }
            }
        }
        attemptRunway = runway;
        IFRRequest(this, tijd);
        requestMessageSend = true;
        return;
    }
    else if (runway == NULL){
        runway = attemptRunway;
    }
    if (!IFRAuthorized && !messageMessageSend){
        IFRMessage(this, tijd);
        messageMessageSend = true;
        return;
    }
    if (!IFRAuthorized && !confirmMessageSend){
        IFRConfirmation(this, tijd);
        requestMessageSend = false;
        messageMessageSend = false;
        IFRAuthorized = true;
        return;
    }
    if (!pushback && !requestMessageSend){
        pushbackRequest(this, tijd);
        requestMessageSend = true;
        return;
    }
    if (!pushback && !messageMessageSend){
        pushbackMessage(this, tijd);
        messageMessageSend = true;
        return;
    }
    if (!pushback && !confirmMessageSend){
        pushbackConfirmation(this, tijd);
        requestMessageSend = false;
        messageMessageSend = false;
        pushback = true;
        return;
    }
    if(!taxiRequest) {
        readyToTaxiMessage(this, tijd);
        taxiRequest = true;
        return;
    }
}

void Airplane::taxiToRunway(Runway* Runway){
    if (gate != -1){
        airPort->setGateOccupied(gate, false);
        gate = -1;
    }
    string tijd = getTime();
    if (Runway == NULL){
        Runway = Airplane::attemptRunway;
    }

    taxiRoute = Runway->getTaxiRoute();
    if (taxiPoint == "" && taxiCrossing == ""){
        taxiPoint = taxiRoute->getTaxiPoints()[0];
        return;
    }
    if (taxiPoint != ""){
        for (unsigned int i=0; i < taxiRoute->getTaxiPoints().size(); i++){
            if (taxiPoint == taxiRoute->getTaxiPoints()[i]){
                if (i == taxiRoute->getTaxiPoints().size()-1){
                    if (!messageMessageSend){
                        toRunwayMessage(this, Runway, taxiPoint, tijd);
                        messageMessageSend = true;
                        return;
                    }
                    else if (!confirmMessageSend){
                        toRunwayConfirmation(this, Runway, taxiPoint, tijd);
                        confirmMessageSend = true;
                        return;
                    }
                    else{
                        messageMessageSend = false;
                        confirmMessageSend = false;
                        runway = Runway;
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
                    clearedToCrossMessage(this, taxiRoute->getTaxiCrossings()[i], tijd);
                    messageMessageSend = true;
                    return;
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
                    clearedToCrossMessage(this, taxiRoute->getTaxiCrossings()[i], tijd);
                    messageMessageSend = true;
                    return;
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

void Airplane::descend(){
    int height = Airplane::getHeight();
    REQUIRE(height > 0, "Plane is not in the air.");
    if (Airplane::getEngine()== "jet"){
        Airplane::setHeight(height-1000);
    }
    else if (Airplane::getEngine()== "propeller"){
        Airplane::setHeight(height-500);
    }
}

void Airplane::emergencyLanding(Airport* Port){
    string tijd = getTime();
    if (height == 0){
        return;
    }
    if (!requestMessageSend){
        if (height >= 3000){
            EmergencyAbove3000ftRequest(this, Port, tijd);
            emergencyInAirport = true;
            requestMessageSend = true;
            descend();
            return;
        }
        else{
            EmergencyBelow3000ftRequest(this, Port, tijd);
            emergencyInAirport = false;
            requestMessageSend = true;
            descend();
            if (height == 0){
                requestMessageSend = false;
            }
            return;
        }
    }
    else if (!messageMessageSend){
        if (emergencyInAirport){
            EmergencyAbove3000ftMessage(this, runway, tijd);
            runway = Port->getRunways()[Port->getFreeRunways()[0]];
            Port->setGateOccupied(Port->getFreeRunways()[0], true);
            descend();
            messageMessageSend = true;
            return;
        } else{
            EmergencyBelow3000ftMessage(this, tijd);
            messageMessageSend = true;
            descend();
            if (height == 0){
                messageMessageSend = false;
            }
            return;
        }
    }
    else{
        if (height != 0) {
            descend();
            if (height == 0) {
                requestMessageSend = false;
            }
        }
    }
}

void Airplane::land(Airport *Port, Runway* Runw) {
    string tijd = getTime();
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
        return;
    }
    else if (Runw == NULL){
        Runw = attemptRunway;
    }

    notificationMessage(
            Airplane::number + " is approaching " + Port->getName() + " at " + intToString(height) + "ft.");
    if (height == 10000){
        if (!request) {
            request = true;
            if (permissionToDescend(height, Port, Runw)){
                descendTo5000ftMessage(this, tijd);
                requestWait = false;
                return;
            }
            else {
                waitBeforeDescendMessage(this, tijd);
                requestWait = true;
                return;
            }
        }
        else {
            request = false;
            if (requestWait){
                waitBeforeDescendConfirmation(this, tijd);
                return;
            }
            else{
                descendTo5000ftConfirmation(this, tijd);
                descend();
                return;
            }
        }
    }
    if (height == 5000){
        if (!request) {
            request = true;
            if (permissionToDescend(height, Port, Runw)){
                descendTo3000ftMessage(this, tijd);
                requestWait = false;
                return;
            }
            else {
                waitBeforeDescendMessage(this, tijd);
                requestWait = true;
                return;
            }
        }
        else {
            request = false;
            if (requestWait){
                waitBeforeDescendConfirmation(this, tijd);
                actionMessage(Airplane::number + " is waiting at a height of " + intToString(height));
                return;
            }
            else{
                descendTo3000ftConfirmation(this, tijd);
                descend();
                return;
            }
        }
    }
    if (height == 3000){
        if (!request) {
            request = true;
            if (permissionToDescend(height, Port, Runw)){
                finalApproachMessage(this, Runw, tijd);
                Runw->setOccupied(true);
                requestWait = false;
                return;
            }
            else {
                waitBeforeDescendMessage(this, tijd);
                requestWait = true;
                return;
            }
        }
        else {
            request = false;
            if (requestWait){
                waitBeforeDescendConfirmation(this, tijd);
                actionMessage(Airplane::number + " is waiting at a height of " + intToString(height));
                return;
            }
            else{
                finalApproachConfirmation(this, Runw, tijd);
                descend();
                return;
            }
        }
    }
    else if (height != 0){
        descend();
        actionMessage(Airplane::number + " descended to a height of " + intToString(height));
        return;
    }
    else{
        actionMessage(Airplane::number + " is landing at Runway" + Runw->getName());
        Airplane::setAirport(Port);
        notificationMessage("Airplane (" + Airplane::number + ") landed in " + Port->getIata());

        Airplane::setRunway(Runw);
        notificationMessage("Airplane (" + Airplane::number + ") is now at runway " + Runw->getName() + "\n");

        Airplane::setState("At runway");

        ENSURE(Runw == Airplane::getRunway(), "Landed" );

        afterLandingMessage(this, Port, Runw, tijd);
        return;
    }
}

void Airplane::takeOff() {
    string tijd = getTime();

    REQUIRE(readyForTakeOff(), "Ready for take off");

    if (!requestMessageSend){
        holdingShortAtRunway(this, runway, tijd);
        requestMessageSend = true;
        return;
    }

    if (!messageMessageSend){
        if (!runway->isOccupied() && !runway->getWachtopRunway() && !runway->getWachtaanRunway()){
            clearedForTakeOffMessage(this, runway, tijd);
            permissiontotakeoff = true;
            messageMessageSend = true;
            runway->setOccupied(true);
            return;
        }
        else if (!runway->getWachtopRunway() && !runway->getWachtaanRunway()){
            lineUpRunwayMessage(this, runway, tijd);
            messageMessageSend = true;
            waitonrunway = true;
            runway->setWachtopRunway(true);
            return;
        }
        else if (!runway->getWachtaanRunway()){
            waitAtRunwayMessage(this, tijd);
            messageMessageSend = true;
            waitatrunway = true;
            runway->setWachtaanRunway(true);
            return;
        }
    }
    if (!confirmMessageSend){
        if (permissiontotakeoff){
            clearedForTakeOffConfirmation(this, runway, tijd);
            confirmMessageSend = true;
            return;
        }
        if (waitonrunway){
            lineUpRunwayConfirmation(this, runway, tijd);
            confirmMessageSend = true;
            waitonrunway = false;
            return;
        }
        if (waitatrunway){
            waitAtRunwayConfirmation(this, tijd);
            confirmMessageSend = true;
            waitatrunway = false;
            return;
        }
    }

    inputMessage("Sending airplane " + Airplane::getNumber() + " for departure");

    notificationMessage("Airplane (" + Airplane::getNumber() + ") is taking off at " + Airplane::getAirport()->getName());

    while (height < 5000) {

        actionMessage("Airplane (" + Airplane::getNumber() + ") ascended to " + intToString(height) + "ft");
        height += 1000;

    }

    notificationMessage("Airplane (" + Airplane::getNumber() + ") has left " + Airplane::getAirport()->getName() + "\n");

    Airplane::setAirport(NULL);
    Airplane::setRunway(NULL);

    Airplane::setState("Airborne");

    ENSURE(runway == NULL && state == "Airborne" && airPort == NULL && height >= 5000, "Airborne");

}


//simulation
void Airplane::finishtask(Airport* Port) {
    // Finilise the current task
    // set Airport after landing
    // ...

}
void Airplane::nextTask(Airport* Port) {
    // Initialize the next task
    // opperation time
    // control tower message
    //...

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

    if (getState() == "Approaching"){


    }else{
        if (getState() == "Gate"){


        }//...
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