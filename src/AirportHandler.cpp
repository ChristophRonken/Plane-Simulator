//
// Created by oliviervh on 01.03.18.
//

#include "AirportHandler.h"
#include "AirplaneClass.h"
#include <algorithm>
#include <vector>




AirportHandler::AirportHandler() {}

AirportHandler::~AirportHandler() {

    for (unsigned int i = 0; i < Airplanes.size(); i++){
        delete Airplanes[i];

    }

    for (unsigned int i = 0; i < Airports.size(); i++) {
        delete Airports[i];

    }
}


//getters & setters
const vector<Airport *> &AirportHandler::getAirports() const {
    return Airports;
}
void AirportHandler::setAirports(const vector<Airport *> &Airports) {

    REQUIRE(validAirports(Airports), "Valid airports");

    AirportHandler::Airports = Airports;
    ENSURE(Airports == AirportHandler::getAirports(), "Set Airports");

}

const vector<Airplane *> &AirportHandler::getAirplanes() const {
    return Airplanes;
}
void AirportHandler::setAirplanes(const vector<Airplane *> &Airplanes) {

    REQUIRE(validAirplanes(Airplanes), "Valid airplanes");

    AirportHandler::Airplanes = Airplanes;

    ENSURE(AirportHandler::getAirplanes() == Airplanes, "Airplanes set");

}

Airport *AirportHandler::getAirport(string iata) {
    for (unsigned int i = 0; i < Airports.size(); i++){
        if (Airports[i]->getIata() == iata){
            return Airports[i];
        }
    }
    return NULL;
}


//add remove
void AirportHandler::addAirplane(Airplane *Plane) {

    REQUIRE(validAirplane(Plane), "Valid airplane");

    Airplanes.push_back(Plane);
    ENSURE(AirportHandler::airplaneExists(Plane->getNumber()), "Plane added");

}
void AirportHandler::removeAirplane(string number){

    REQUIRE(AirportHandler::airplaneExists(number), "Airplane exists");

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        if (Airplanes[i]->getNumber() == number) {
            Airplanes[i]->setAirport(NULL);
            delete Airplanes[i];
            Airplanes[i] = Airplanes[Airplanes.size()-1];
            Airplanes.resize(Airplanes.size()-1);

            //succesMessage("Airplane Deleted (" + callsign + ")" );
            return;
        }
    }

    ENSURE(!AirportHandler::airplaneExists(number), "Airplane doesn't exist");


}

void AirportHandler::addAirport(Airport *Port) {

    REQUIRE(validAirport(Port), "Valid airport");

    Airports.push_back(Port);
    ENSURE(AirportHandler::airportExists(Port->getIata()), "Airport added");

}
void AirportHandler::removeAirport(string iata){

    REQUIRE(airportExists(iata), "Airport exists");

    for (unsigned int i = 0; i < Airports.size(); i++) {
        if (Airports[i]->getIata() == iata) {

            const vector<Runway *> Runways;
            Airports[i]->setRunways(Runways);

            const vector<bool> occup;
            Airports[i]->setGatesOccupied(occup);

            delete Airports[i];
            Airports[i] = Airports[Airports.size()-1];
            Airports.resize(Airports.size()-1);

            return;

        }
    }

    ENSURE(!AirportHandler::airportExists(iata), "Airport added");

}

SuccessEnum AirportHandler::addXmlData(string fileName) {

    string errorFile = fileName.substr(0, fileName.size() - 4) + "Error.txt";

    ofstream errStream(errorFile.c_str());
    SuccessEnum endResult = Success;

    // Open XML
    const char *cstr = fileName.c_str();
    TiXmlDocument doc(cstr);
    doc.LoadFile();

    if(!doc.LoadFile()) {
        errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << endl;
        return ImportAborted;
    };


    TiXmlElement* root = doc.FirstChildElement();

    // If Xml isn't empty
    if (root != NULL){
        if (root->ValueTStr() != "AirportInfo"){
            errStream << "XML PARTIAL IMPORT: Expected <AirportInfo> ... </AirportInfo> and got <"
                      << root->Value() <<  "> ... </" << root->Value() << ">." << endl;
            endResult = PartialImport;

        }else {

            // Airports
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                if (elemName == "AIRPORT") {
                    Airport *Port = new Airport();
                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {
                        string AttName = elemAtt->Value();
                        string AttValue = elemAtt->GetText();

                        Port->setVar(AttName, string(AttValue));
                    }

                    //Port->isValid();

                    Airports.push_back(Port);

                    continue;
                }
            }
            // Runways
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

                string elemName = elem->Value();
                if (elemName == "RUNWAY") {
                    Runway *Runw = new Runway();

                    // Loop over Variables
                    //attributes
                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {

                        string AttName = elemAtt->Value();
                        if (AttName != "airport" && AttName != "TAXIROUTE") {
                            string AttValue = elemAtt->GetText();
                            Runw->setVar(AttName, string(AttValue));
                        } else {
                            continue;
                        }
                    }

                    //airport
                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {
                        string AttName = elemAtt->Value();
                        if (AttName == "airport") {
                            string AttValue = elemAtt->GetText();
                            for (unsigned int i = 0; i < Airports.size(); i++) {
                                if (Airports[i]->getIata() == AttValue) {
                                    Airports[i]->addRunway(Runw);
                                    break;
                                }

                            }

                            if (Runw->getAirport() == NULL) {
                                errStream << "XML PARTIAL IMPORT: Invalid value for attribute airport at Runway.\n" ;
                                endResult = PartialImport;
                                delete Runw;

                            }
                        }
                    }

                    //taxipoint
                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {
                        string AttName = elemAtt->Value();
                        if (AttName == "TAXIROUTE") {
                            TaxiRoute *Taxi = new TaxiRoute();

                            for (TiXmlElement *SubelemAtt = elemAtt->FirstChildElement();
                                 SubelemAtt != NULL; SubelemAtt = SubelemAtt->NextSiblingElement()) {

                                string SubAttName = SubelemAtt->Value();
                                string SubAttValue = SubelemAtt->GetText();

                                if (SubAttName == "taxipoint") {
                                    Taxi->addTaxiPoint(SubAttValue);
                                } else if (SubAttName == "crossing") {
                                    for (int i = 0; i < (signed) Runw->getAirport()->getRunways().size(); i++) {
                                        if (Runw->getAirport()->getRunways()[i]->getName() == SubAttValue) {
                                            Taxi->addCrossing(SubAttValue);
                                            break;
                                        } else if (i == (signed) Runw->getAirport()->getRunways().size() - 1) {
                                            errStream << "XML PARTIAL IMPORT: failed to create taxipoint.\n";
                                            endResult =  PartialImport;

                                        }
                                    }
                                } else {
                                    errStream << "XML PARTIAL IMPORT: failed to create taxiRoute.\n";
                                    endResult =  PartialImport;

                                }
                            }

                            Runw->setTaxiRoute(Taxi);
                            continue;
                        }
                    }

                    if (!Runw->isValid()) {
                        errStream << "XML PARTIAL IMPORT: failed to create runway.\n";
                        endResult = PartialImport;
                        Runw->getAirport()->removeRunway(Runw->getName());

                    }

                    continue;
                }
            }
            // Airplanes
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();

                if (elemName == "AIRPLANE") {
                    Airplane *Plane = new Airplane();

                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {
                        string AttName = elemAtt->Value();


                        if (AttName == "FLIGHTPLAN") {
                            FlightPlan *Flight = new FlightPlan();
                            for (TiXmlElement *SubelemAtt = elemAtt->FirstChildElement();
                                 SubelemAtt != NULL; SubelemAtt = SubelemAtt->NextSiblingElement()) {
                                string SubAttName = SubelemAtt->Value();
                                string SubAttValue = SubelemAtt->GetText();

                                if (SubAttName == "destination") {
                                    Flight->setDestination(SubAttValue);
                                } else if (SubAttName == "departure") {
                                    int i;
                                    istringstream(SubAttValue) >> i;
                                    Flight->setDeparture(i);
                                } else if (SubAttName == "arrival") {
                                    int i;
                                    istringstream(SubAttValue) >> i;
                                    Flight->setArrival(i);
                                } else if (SubAttName == "interval") {
                                    int i;
                                    istringstream(SubAttValue) >> i;
                                    Flight->setInterval(i);
                                } else {
                                    errStream << "XML PARTIAL IMPORT: invalid value type at flightplan\n";
                                    endResult = PartialImport;

                                }
                            }

                            if (!Flight->isValid()){
                                errStream << "XML PARTIAL IMPORT: invalid value of the flightplan\n";
                                endResult = PartialImport;
                                delete Flight;
                                Flight = NULL;

                            }

                            Plane->setFlightPlan(Flight);
                            continue;

                        }

                        string AttValue = elemAtt->GetText();
                        Plane->setVar(AttName, string(AttValue));

                    }

                    if (Plane->isValid()) {
                        Plane->setSquawkCode();
                        if (validAirplane(Plane)) {
                            Airplanes.push_back(Plane);

                        } else {
                            errStream << "XML PARTIAL IMPORT: double defined Airplane\n";
                            endResult = PartialImport;
                            delete Plane;
                        }
                    }else{
                        errStream << "XML PARTIAL IMPORT: invalid or non defined Airplane values\n";
                        endResult = PartialImport;
                        delete Plane;
                    }

                    continue;
                }
            }
        }
    }

    return endResult;

}


string AirportHandler::timeToString(double passedTimeUnits){

    passedTimeUnits += simulationStartTime*60;

    double hour = int(floor(passedTimeUnits/60))%24;
    double minutes = int(passedTimeUnits)%60;

    stringstream ss;

    if (minutes < 10){
        ss << hour << ":0" << minutes;

    }else{
        if (minutes == 0){
            ss << hour << ":" << "00";

        }else{
            ss << hour << ":" << minutes;

        }
    }

    return ss.str();

}

//checks
bool AirportHandler::validFileName(string name) {
    const char *cstr = name.c_str();
    TiXmlDocument doc(cstr);

    return doc.LoadFile();

}
bool AirportHandler::validAirplanes(vector<Airplane *> Planes) {

    vector<string> names;
    for (unsigned int i = 0; i< Planes.size(); i++){
        string name = Planes[i]->getNumber();
        if (!(find(names.begin(), names.end(), name) == names.end() && name != "")){
            return false;
        }
        names.push_back(name);
    }

    return true;
}
bool AirportHandler::validAirports(vector<Airport *> Ports) {

    vector<string> names;
    for (unsigned int i = 0; i< Ports.size(); i++){
        string name = Ports[i]->getCallsign();
        if (!(find(names.begin(), names.end(), name) == names.end() && name != "")){
            return false;
        }
        names.push_back(name);
    }

    return true;

}
bool AirportHandler::validAirplane(Airplane *Plane) {

    if (Plane->getNumber() == ""){
        return false;

    }

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        if (Airplanes[i]->getNumber() == Plane->getNumber()){
            return false;
        }
    }

    return true;

}
bool AirportHandler::validAirport(Airport* Port) {

    if (Port->getIata() == ""){
        return false;

    }
    for (unsigned int i = 0; i < Airports.size(); i++) {
        if (Airports[i]->getIata() == Port->getIata()){
            return false;

        }
    }

    return true;
}
bool AirportHandler::airportEmpty(Airport *Port) {

    if (Port->getFreeRunways().size() == Port->getRunways().size()){
        if (Port->getFreeGates().size() == unsigned (Port->getGates())){
            for (unsigned int i = 0; i < Airplanes.size(); i++){
                if (Airplanes[i]->notFinished(Port)) {
                    return false;

                }
            }

            return true;

        }
    }


    return false;

}
bool AirportHandler::airplaneExists(string number) {

    for (unsigned int i = 0; i< Airplanes.size(); i++){
        if (Airplanes[i]->getNumber() == number){
            return true;
        }
    }
    return false;

}
bool AirportHandler::airportExists(string iata) {
    for (unsigned int i = 0; i< Airports.size(); i++){
        if (Airports[i]->getIata() == iata){
            return true;
        }
    }
    return false;
}


//simulation
void AirportHandler::runSimulation(string iata) {
    REQUIRE(!AirportHandler::getAirports().empty(), "an airport to run a simulation on exists");

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        Airplanes[i]->initSimulation(Airports[0]);

    }

    setStartingTime(simulationStartTime);
    double nowtime = time(NULL);
    double startTime = nowtime;

    Airport* Port = getAirport(iata);

    while (!airportEmpty(Airports[0])) {

        double later = time(NULL);
        double deltaTime = difftime(later, nowtime);

        if (deltaTime >= TimeUnit){

            nowtime += TimeUnit ;

            double passedTimeUnits = (nowtime - startTime)/TimeUnit;

            setTime(timeToString(passedTimeUnits));
            setTimePassed(passedTimeUnits);

            for (unsigned int i = 0; i < Airplanes.size(); i++) {
                Airplane *Plane = Airplanes[i];

                if (Plane->notFinished(Port)) {
                    if (Plane->getOpperationTime() > 0) {
                        Plane->continueTask();

                    } else {
                        Plane->execTask(Port);

                    }
                    cout << "Tijd: " << getTime() << endl;
                    cout << Plane->getCurrentTask() << endl;
                    cout << Plane->getState() << endl;
                    cout << Plane->getGate();
                    cout << endl;
                    Plane->setOpperationTime(Plane->getOpperationTime() - 1);

                }
            }
            GraphicalAirport3D(iata);
        }
    }


    closeCommunicationLogFile();
    closeLogFile();

}


//output
void AirportHandler::printInfo() {

    for (unsigned int i = 0; i < Airports.size() ; i++) {
        Airports[i]->printInfo();

    }

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        Airplanes[i]->printInfo();

    }

}
string AirportHandler::getInfo() {

    string s;

    for (unsigned int i = 0; i< Airports.size(); i++ ){
        s+= Airports[i]->getInfo();

    }

    for (unsigned int i = 0; i< Airplanes.size(); i++ ){
        s+= Airplanes[i]->getInfo();

    }

    return s;

}
void AirportHandler::fileOutput(string fileName) {

    string str = AirportHandler::getInfo();

    fstream file;
    file.open(fileName.c_str(), fstream::out);
    file << str;
    file.close();

}

void AirportHandler::GraphicalAirport2D(string & AirportIata) {

    REQUIRE(airportExists(AirportIata), "Airport exists");

    string document = AirportIata;
    document += ".txt";
    const char * documentname = document.c_str();

    string s;

    Airport* airport = AirportHandler::getAirport(AirportIata);
    const vector<Runway *> runways = airport->getRunways();

    for (unsigned int i = 0; i< runways.size(); i++ ){
        s += runways[i]->getName();
        s += " | ";
        if (!runways[i]->isOccupied()){
            s += "==========\n";
        }
        else {
            s += "====V=====\n";
        }
        if (runways[i]->getTaxiRoute() != NULL){
            s += runways[i]->getTaxiRoute()->getTaxiPoints()[runways[i]->getTaxiRoute()->getTaxiPoints().size()-1];
            s += " | \n";
        }
    }

    s += "Gates [";
    for (int i = 0; i< airport->getGates(); i++ ){
        if (airport->getGateOccupied(i)){
            s += "V";
        }
        else {
            s += " ";
        }
    }
    s += "]\n";

    fstream file;
    file.open(documentname, fstream::out);
    file << s;
    file.close();

}

void AirportHandler::GraphicalAirport3D(string & AirportIata) {

    REQUIRE(airportExists(AirportIata), "Airport exists");

    string document = "3Doutput" + getTime() + ".ini";
    const char * documentname = document.c_str();

    Airport* airport = AirportHandler::getAirport(AirportIata);
    const vector<Runway *> runways = airport->getRunways();

    // makes vector with all airplanes in the simulation
    vector<Airplane*> unfinishedAirplanes;
    for (unsigned int i=0; i<getAirplanes().size(); i++){
        if (!getAirplanes()[i]->getsimulationFinished()){
            unfinishedAirplanes.push_back(getAirplanes()[i]);
        }
    }

    TaxiRoute* longesttaxi = NULL;
    for (unsigned int i=0; i<airport->getRunways().size(); i++){
        if (longesttaxi == NULL){
            longesttaxi = airport->getRunways()[i]->getTaxiRoute();
        }
        else if (airport->getRunways()[i]->getTaxiRoute()->getTaxiPoints().size() > longesttaxi->getTaxiPoints().size()){
            longesttaxi = airport->getRunways()[i]->getTaxiRoute();
        }
    }


    int aantalfiguren = airport->getRunways().size() + airport->getGates() + unfinishedAirplanes.size() + longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size();
    string s;

    s += "[General]\n";
    s += "size = 1000\n";
    s += "backgroundcolor = (0, 0, 0)\n";
    s += "type = ZBufferedWireframe\n";
    s += "eye = (50, -100, 100)\n";
    s += "nrFigures = " + intToString(aantalfiguren) + "\n";
    s += "\n";

    // draws gates
    for (int i=0; i<airport->getGates(); i++){
        s += "[Figure" + intToString(i) + "]\n";
        s += "type = \"Cube\"\n";
        s += "scale = 3\n";
        s += "rotateX = 0\n";
        s += "rotateY = 0\n";
        s += "rotateZ = 0\n";
        s += "center = (" + intToString(i*6) +", 0, 0)\n";
        if (airport->getGateOccupied(i)){
            s += "color = (1, 0, 0)\n";
        }
        else{
            s += "color = (0, 1, 0)\n";
        }
        s += "\n";
    }

    // draws runways
    for (unsigned int i=0; i<airport->getRunways().size(); i++){
        s += "[Figure" + intToString(i+airport->getGates()) + "]\n";
        s += "type = \"Cylinder\"\n";
        s += "height = 0.2\n";
        s += "n = 2\n";
        s += "scale = 20\n";
        s += "rotateX = 90\n";
        s += "rotateY = 0\n";
        s += "rotateZ = 0\n";
        s += "center = ("+ intToString((airport->getGates()-1)*6 /2) + ", " + intToString(20*(i+1)) + ", 0)\n";
        if (airport->getRunways()[i]->isOccupied()){
            s += "color = (1, 0, 0)\n";
        }
        else{
            s += "color = (0, 1, 0)\n";
        }
        s += "\n";
    }

    // draws all taxipoints
    for (unsigned int i=0; i<longesttaxi->getTaxiPoints().size(); i++){
        s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()) + "]\n";
        s += "type = \"Cylinder\"\n";
        s += "height = 1\n";
        s += "n = 2\n";
        s += "scale = 3\n";
        s += "rotateX = 90\n";
        s += "rotateY = 0\n";
        s += "rotateZ = 0\n";
        s += "center = ("+ intToString((airport->getGates()-1)*6 /2 + 15) + ", " + intToString(20*(i+1)-5) + ", 0)\n";
        if (airport->getRunways()[i]->getHoldingShortOccupied()){
            s += "color = (1, 0, 0)\n";
        }
        else{
            s += "color = (0, 1, 0)\n";
        }
        s += "\n";
    }

    // draws all taxicrossings
    for (unsigned int i=0; i<longesttaxi->getTaxiCrossings().size(); i++){
        s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates() + longesttaxi->getTaxiPoints().size()) + "]\n";
        s += "type = \"Cylinder\"\n";
        s += "height = 1\n";
        s += "n = 2\n";
        s += "scale = 2\n";
        s += "rotateX = 90\n";
        s += "rotateY = 0\n";
        s += "rotateZ = 90\n";
        s += "center = ("+ intToString((airport->getGates()-1)*6 /2) + ", " + intToString(20*(i+1)-2) + ", 0)\n";
        if (!airport->getRunways()[i]->getPermissionToCross()){
            s += "color = (1, 0, 0)\n";
        }
        else{
            s += "color = (0, 1, 0)\n";
        }
        s += "\n";
    }


    // draws all airplanes
    for (unsigned int i=0; i<unfinishedAirplanes.size(); i++){
        string task = unfinishedAirplanes[i]->getCurrentTask();
        Airplane* plane = unfinishedAirplanes[i];
        string state = plane->getState();

        if (state == "Approaching"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (0, 0, " + intToString(ceil(plane->getHeight()/200)) + ")\n";
            s += "color = (1, 1, 0)\n";
            s += "\n";
        }
        else if (state == "on final approach") {
            s += "[Figure" + intToString(
                    i + airport->getRunways().size() + airport->getGates() + longesttaxi->getTaxiPoints().size() +
                    longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2 + 15) + ", " +
                         intToString(20 * (plane->getAttemptRunway()->getTaxiRoute()->getTaxiPoints().size() -1 + 1)) + intToString(ceil(plane->getHeight()/200)) + ")\n";
            s += "color = (1, 1, 1)\n";
        }
        else if (state == "emergency refuel"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            for (unsigned int j=0; j<airport->getRunways().size(); j++){
                if (plane->getRunway() == airport->getRunways()[j]){
                    s += "center = ("+ intToString((airport->getGates()-1)*6 /2  - 10) + ", " + intToString(20*(j+1)) + ", 0)\n";
                }
            }
            s += "color = (1, 0.5, 1)\n";
            s += "\n";
        }
        else if (state == "refuel"){
            s += "[Figure" + intToString(
                    i + airport->getRunways().size() + airport->getGates() + longesttaxi->getTaxiPoints().size() +
                    longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate() * 6) + ", 0, 0)\n";
            s += "color = (1, 0.5, 1)\n";
            s += "\n";
        }
        else if (state == "emergency exit"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            for (unsigned int j=0; j<airport->getRunways().size(); j++){
                if (unfinishedAirplanes[i]->getRunway() == airport->getRunways()[j]){
                    s += "center = ("+ intToString((airport->getGates()-1)*6 /2  - 10) + ", " + intToString(20*(j+1)) + ", 0)\n";
                }
            }
            s += "color = (1, 1, 0)\n";
            s += "\n";
        }
        else if (state == "exit passengers"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate()*6) +", 0, 0)\n";
            s += "color = (1, 1, 0)\n";
            s += "\n";
        }
        else if (state == "emergency check"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            for (unsigned int j=0; j<airport->getRunways().size(); j++){
                if (unfinishedAirplanes[i]->getRunway() == airport->getRunways()[j]){
                    s += "center = ("+ intToString((airport->getGates()-1)*6 /2  - 10) + ", " + intToString(20*(j+1)) + ", 0)\n";
                }
            }
            s += "color = (1, 0, 1)\n";
            s += "\n";
        }
        else if (state == "technical check"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate()*6) +", 0, 0)\n";
            s += "color = (1, 0, 1)\n";
            s += "\n";
        }
        else if (state == "emergency crash" || state == "emergency landing" || state == "crash"){
            if (unfinishedAirplanes[i]->getEmergencyInAirport()){
            } else{
                return;
            }
        }
        else if (state == "at holding point"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2 + 15) + ", " +
                 intToString(20 * (plane->getRunway()->getTaxiRoute()->getTaxiPoints().size() -1 + 1) - 5) + ", 0)\n";
            s += "color = (1, 1, 1)\n";
            s += "\n";
        }
        else if (state == "at taxipoint"){
            for (unsigned int j = 0; j < longesttaxi->getTaxiPoints().size(); j++) {
                if (plane->getTaxiPoint() == longesttaxi->getTaxiPoints()[j]) {
                    s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
                    s += "type = \"Sphere\"\n";
                    s += "n = 2\n";
                    s += "scale = 2\n";
                    s += "rotateX = 0\n";
                    s += "rotateY = 0\n";
                    s += "rotateZ = 0\n";
                    s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2 + 15) + ", " +
                         intToString(20 * (j + 1) - 5) + ", 0)\n";
                    s += "color = (1, 1, 1)\n";
                    s += "\n";
                }
            }
        }
        else if (state == "at taxicrossing" && plane->getCurrentTask() == "going to gate"){
            for (unsigned int j = 0; j < longesttaxi->getTaxiCrossings().size(); j++) {
                if (plane->getTaxiCrossing() == longesttaxi->getTaxiCrossings()[j]) {
                    s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
                    s += "type = \"Sphere\"\n";
                    s += "n = 2\n";
                    s += "scale = 2\n";
                    s += "rotateX = 0\n";
                    s += "rotateY = 0\n";
                    s += "rotateZ = 0\n";
                    s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2) + ", " +
                         intToString(20 * (j + 1) + 5) + ", 0)\n";
                    s += "color = (1, 1, 1)\n";
                    s += "\n";
                }
            }
        }
        else if (state == "at taxicrossing" && plane->getCurrentTask() == "going to runway"){
            for (unsigned int j = 0; j < longesttaxi->getTaxiCrossings().size(); j++) {
                if (plane->getTaxiCrossing() == longesttaxi->getTaxiCrossings()[j]) {
                    s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
                    s += "type = \"Sphere\"\n";
                    s += "n = 2\n";
                    s += "scale = 2\n";
                    s += "rotateX = 0\n";
                    s += "rotateY = 0\n";
                    s += "rotateZ = 0\n";
                    s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2) + ", " +
                         intToString(20 * (j + 1) - 5) + ", 0)\n";
                    s += "color = (1, 1, 1)\n";
                    s += "\n";
                }
            }
        }
        else if (state == "crossing taxicrossing"){
            for (unsigned int j = 0; j < longesttaxi->getTaxiCrossings().size(); j++) {
                if (unfinishedAirplanes[i]->getTaxiCrossing() == longesttaxi->getTaxiCrossings()[j]) {
                    s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
                    s += "type = \"Sphere\"\n";
                    s += "n = 2\n";
                    s += "scale = 2\n";
                    s += "rotateX = 0\n";
                    s += "rotateY = 0\n";
                    s += "rotateZ = 0\n";
                    s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2) + ", " +
                         intToString(20 * (j + 1)) + ", 0)\n";
                    s += "color = (1, 1, 1)\n";
                    s += "\n";
                }
            }
        }
        else if (state == "board passengers"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate()*6) +", 0, 0)\n";
            s += "color = (1, 1, 0.5)\n";
            s += "\n";
        }
        else if (state == "pushback"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate()*6) +", 0, 0)\n";
            s += "color = (0.75, 0.25, 0)\n";
            s += "\n";
        }
        else if (state == "lined up"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            for (unsigned int j=0; j<airport->getRunways().size(); j++){
                if (plane->getRunway() == airport->getRunways()[j]){
                    s += "center = ("+ intToString((airport->getGates()-1)*6 /2  + 15) + ", " + intToString(20*(j+1)) + ", 0)\n";
                }
            }
            s += "color = (0, 1, 1)\n";
            s += "\n";
        }
        else if (state == "ascending"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            for (unsigned int j=0; j<airport->getRunways().size(); j++){
                if (plane->getRunway() == airport->getRunways()[j]){
                    s += "center = ("+ intToString((airport->getGates()-1)*6 /2  - 10) + ", " + intToString(20*(j+1)) + intToString(ceil(plane->getHeight()/200)) + ")\n";
                }
            }
            s += "color = (1, 1, 1)\n";
            s += "\n";
        }
        else if (state == "At runway"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2 + 15) + ", " +
                 intToString(20 * (plane->getRunway()->getTaxiRoute()->getTaxiPoints().size())) + ", 0)\n";
            s += "color = (1, 1, 1)\n";
            s += "\n";
        }
        else {
            cout << "WRONG STATE"<< endl;
        }
    }





    fstream file;
    file.open(documentname, fstream::out);
    file << s;
    file.close();

}

bool AirportHandler::propperlyInitialised() {
    return (this == self);
}


