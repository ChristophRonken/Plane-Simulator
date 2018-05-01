//
// Created by oliviervh on 01.03.18.
//

#include "AirportHandler.h"
#include "AirplaneClass.h"
#include <algorithm>
#include <vector>




AirportHandler::AirportHandler() {}

AirportHandler::~AirportHandler() {

    for (unsigned int i = 0; i < airplanes.size(); i++){
        delete airplanes[i];

    }

    for (unsigned int i = 0; i < airports.size(); i++) {
        delete airports[i];

    }
}


//getters & setters
const vector<Airport *> &AirportHandler::getAirports() const {
    return airports;
}
void AirportHandler::setAirports(const vector<Airport *> &airports) {

    REQUIRE(validAirports(airports), "Valid airports");

    AirportHandler::airports = airports;
    ENSURE(airports == AirportHandler::getAirports(), "Set airports");

}

const vector<Airplane *> &AirportHandler::getAirplanes() const {
    return airplanes;
}
void AirportHandler::setAirplanes(const vector<Airplane *> &airplanes) {

    REQUIRE(validAirplanes(airplanes), "Valid airplanes");

    AirportHandler::airplanes = airplanes;

    ENSURE(AirportHandler::getAirplanes() == airplanes, "airplanes set");

}

Airport *AirportHandler::getAirport(const string &iata) {
    for (unsigned int i = 0; i < airports.size(); i++){
        if (airports[i]->getIata() == iata){
            return airports[i];
        }
    }
    return NULL;
}


//add remove
void AirportHandler::addAirplane(Airplane *airplane) {

    REQUIRE(validAirplane(airplane), "Valid airplane");

    airplanes.push_back(airplane);
    ENSURE(AirportHandler::airplaneExists(airplane->getNumber()), "Plane added");

}

void AirportHandler::removeAirplane(const string &number){

    REQUIRE(AirportHandler::airplaneExists(number), "Airplane exists");

    for (unsigned int i = 0; i < airplanes.size(); i++) {
        if (airplanes[i]->getNumber() == number) {
            airplanes[i]->setAirport(NULL);
            delete airplanes[i];
            airplanes[i] = airplanes[airplanes.size()-1];
            airplanes.resize(airplanes.size()-1);

            //succesMessage("Airplane Deleted (" + callsign + ")" );
            return;
        }
    }

    ENSURE(!AirportHandler::airplaneExists(number), "Airplane doesn't exist");


}

void AirportHandler::addAirport(Airport *airport) {

    REQUIRE(validAirport(airport), "Valid airport");

    airports.push_back(airport);
    ENSURE(AirportHandler::airportExists(airport->getIata()), "Airport added");

}

void AirportHandler::removeAirport(const string &iata){

    REQUIRE(airportExists(iata), "Airport exists");

    for (unsigned int i = 0; i < airports.size(); i++) {
        if (airports[i]->getIata() == iata) {

            const vector<Runway *> Runways;
            airports[i]->setRunways(Runways);

            const vector<bool> occup;
            airports[i]->setGatesOccupied(occup);

            delete airports[i];
            airports[i] = airports[airports.size()-1];
            airports.resize(airports.size()-1);

            return;

        }
    }

    ENSURE(!AirportHandler::airportExists(iata), "Airport added");

}

SuccessEnum AirportHandler::addXmlData(const string &fileName) {

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

            // airports
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

                    airports.push_back(Port);

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
                            for (unsigned int i = 0; i < airports.size(); i++) {
                                if (airports[i]->getIata() == AttValue) {
                                    airports[i]->addRunway(Runw);
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
            // airplanes
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
                            airplanes.push_back(Plane);

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

    passedTimeUnits += gSimulationStartTime*60;

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
bool AirportHandler::validFileName(const string &name) {
    const char *cstr = name.c_str();
    TiXmlDocument doc(cstr);

    return doc.LoadFile();

}
bool AirportHandler::validAirplanes(vector<Airplane *> airplanes) {

    vector<string> names;
    for (unsigned int i = 0; i< airplanes.size(); i++){
        string name = airplanes[i]->getCallsign();
        if (!(find(names.begin(), names.end(), name) == names.end() && name != "")){
            return false;
        }
        names.push_back(name);
    }

    return true;
}
bool AirportHandler::validAirports(vector<Airport *> airports) {

    vector<string> names;
    for (unsigned int i = 0; i< airports.size(); i++){
        string name = airports[i]->getCallsign();
        if (!(find(names.begin(), names.end(), name) == names.end() && name != "")){
            return false;
        }
        names.push_back(name);
    }

    return true;

}
bool AirportHandler::validAirplane(Airplane *airplane) {

    if (airplane->getNumber() == ""){
        return false;

    }

    for (unsigned int i = 0; i < airplanes.size(); i++) {
        if (airplanes[i]->getNumber() == airplane->getNumber()){
            return false;
        }
    }

    return true;

}
bool AirportHandler::validAirport(Airport* airport) {

    if (airport->getIata() == ""){
        return false;

    }
    for (unsigned int i = 0; i < airports.size(); i++) {
        if (airports[i]->getIata() == airport->getIata()){
            return false;

        }
    }

    return true;
}
bool AirportHandler::airportEmpty(Airport *airport) {

    if (airport->getFreeRunways().size() == airport->getRunways().size()){
        if (airport->getFreeGates().size() == unsigned (airport->getGates())){
            for (unsigned int i = 0; i < airplanes.size(); i++){
                if (airplanes[i]->notFinished(airport)) {
                    return false;

                }
            }

            return true;

        }
    }


    return false;

}
bool AirportHandler::airplaneExists(const string &number) {

    for (unsigned int i = 0; i< airplanes.size(); i++){
        if (airplanes[i]->getNumber() == number){
            return true;
        }
    }
    return false;

}
bool AirportHandler::airportExists(const string &iata) {
    for (unsigned int i = 0; i< airports.size(); i++){
        if (airports[i]->getIata() == iata){
            return true;
        }
    }
    return false;
}


//simulation
void AirportHandler::runSimulation(const string &iata) {
    REQUIRE(!AirportHandler::getAirports().empty(), "an airport to run a simulation on exists");

    for (unsigned int i = 0; i < airplanes.size(); i++) {
        airplanes[i]->initSimulation(airports[0]);

    }

    setStartingTime(gSimulationStartTime);

    double nowtime = time(NULL);
    double startTime = nowtime;

    Airport* Port = getAirport(iata);

    while (!airportEmpty(airports[0])) {

        double later = time(NULL);
        double deltaTime = difftime(later, nowtime);

        if (deltaTime >= gTimeUnit){

            nowtime += gTimeUnit ;

            double passedTimeUnits = (nowtime - startTime)/gTimeUnit;

            setTime(timeToString(passedTimeUnits));
            setTimePassed(passedTimeUnits);

            for (unsigned int i = 0; i < airplanes.size(); i++) {
                Airplane *Plane = airplanes[i];

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

    for (unsigned int i = 0; i < airports.size() ; i++) {
        airports[i]->printInfo();

    }

    for (unsigned int i = 0; i < airplanes.size(); i++) {
        airplanes[i]->printInfo();

    }

}
string AirportHandler::getInfo() {

    string s;

    for (unsigned int i = 0; i< airports.size(); i++ ){
        s+= airports[i]->getInfo();

    }

    for (unsigned int i = 0; i< airplanes.size(); i++ ){
        s+= airplanes[i]->getInfo();

    }

    return s;

}
void AirportHandler::fileOutput(const string &fileName) {

    string str = AirportHandler::getInfo();

    fstream file;
    file.open(fileName.c_str(), fstream::out);
    file << str;
    file.close();

}

void AirportHandler::GraphicalAirport2D(const string &iata) {

    REQUIRE(airportExists(iata), "Airport exists");

    string document = iata;
    document += ".txt";
    const char * documentname = document.c_str();

    string s;

    Airport* airport = AirportHandler::getAirport(iata);
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

void AirportHandler::GraphicalAirport3D(const string &iata) {

    REQUIRE(airportExists(iata), "Airport exists");

    string document = "3Doutput" + getTime() + ".ini";
    const char * documentname = document.c_str();

    Airport* airport = AirportHandler::getAirport(iata);
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
        Airplane* airplane = unfinishedAirplanes[i];
        string state = airplane->getState();

        if (state == "Approaching"){
            s += "[Figure" + intToString(i + airport->getRunways().size() + airport->getGates()+longesttaxi->getTaxiPoints().size() + longesttaxi->getTaxiCrossings().size()) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (0, 0, " + intToString(ceil(airplane->getHeight()/200)) + ")\n";
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
                         intToString(20 * (airplane->getAttemptRunway()->getTaxiRoute()->getTaxiPoints().size() -1 + 1)) + intToString(ceil(airplane->getHeight()/200)) + ")\n";
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
                if (airplane->getRunway() == airport->getRunways()[j]){
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
                 intToString(20 * (airplane->getRunway()->getTaxiRoute()->getTaxiPoints().size() -1 + 1) - 5) + ", 0)\n";
            s += "color = (1, 1, 1)\n";
            s += "\n";
        }
        else if (state == "at taxipoint"){
            for (unsigned int j = 0; j < longesttaxi->getTaxiPoints().size(); j++) {
                if (airplane->getTaxiPoint() == longesttaxi->getTaxiPoints()[j]) {
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
        else if (state == "at taxicrossing" && airplane->getCurrentTask() == "going to gate"){
            for (unsigned int j = 0; j < longesttaxi->getTaxiCrossings().size(); j++) {
                if (airplane->getTaxiCrossing() == longesttaxi->getTaxiCrossings()[j]) {
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
        else if (state == "at taxicrossing" && airplane->getCurrentTask() == "going to runway"){
            for (unsigned int j = 0; j < longesttaxi->getTaxiCrossings().size(); j++) {
                if (airplane->getTaxiCrossing() == longesttaxi->getTaxiCrossings()[j]) {
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
                if (airplane->getRunway() == airport->getRunways()[j]){
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
                if (airplane->getRunway() == airport->getRunways()[j]){
                    s += "center = ("+ intToString((airport->getGates()-1)*6 /2  - 10) + ", " + intToString(20*(j+1)) + intToString(ceil(airplane->getHeight()/200)) + ")\n";
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
                 intToString(20 * (airplane->getRunway()->getTaxiRoute()->getTaxiPoints().size())) + ", 0)\n";
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


