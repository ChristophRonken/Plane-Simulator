//
// Created by oliviervh on 01.03.18.
//

#include "AirportHandler.h"
#include <algorithm>

void AirportHandler::addXmlData(string fileName) {

    REQUIRE(validFileName(fileName), "Valid file name");

    // Open XML
    const char *cstr = fileName.c_str();
    TiXmlDocument doc(cstr);
    doc.LoadFile();

    TiXmlElement* root = doc.FirstChildElement();

    // If Xml isn't empty
    if (root != NULL){
        // Airports
        for ( TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement() ){
            string elemName = elem->Value();
            if (elemName == "AIRPORT"){
                Airport* Port = new Airport();
                for (TiXmlElement* elemAtt = elem->FirstChildElement(); elemAtt!= NULL; elemAtt = elemAtt->NextSiblingElement()){
                    string AttName = elemAtt->Value();
                    string AttValue = elemAtt->GetText();

                    Port->setVar(AttName, string(AttValue));
                }

                Airports.push_back(Port);
                succesMessage("Airport added (" + Port->getName() + ")");
                //Port->printValues();
                continue;
            }
        }
        // Runways
        for ( TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement() ){

            string elemName = elem->Value();
            if (elemName == "RUNWAY"){
                Runway* Runw = new Runway();

                // Loop over Variables
                //attributes
                for (TiXmlElement* elemAtt = elem->FirstChildElement(); elemAtt!= NULL; elemAtt = elemAtt->NextSiblingElement()){

                    string AttName = elemAtt->Value();
                    if (AttName != "airport" && AttName != "TAXIROUTE"){
                        string AttValue = elemAtt->GetText();
                        Runw->setVar(AttName, string(AttValue));
                    }
                    else{
                        continue;
                    }
                }
                //airport
                for (TiXmlElement* elemAtt = elem->FirstChildElement(); elemAtt!= NULL; elemAtt = elemAtt->NextSiblingElement()){
                    string AttName = elemAtt->Value();
                    if (AttName == "airport"){
                        string AttValue = elemAtt->GetText();
                        for (unsigned int i = 0; i < Airports.size(); i++){
                            if (Airports[i]->getIata() == AttValue){
                                Airports[i]->addRunway(Runw);
                                break;
                            }

                        }

                        if (Runw->getAirport() == NULL){
                            errorMessage("Failed to add runway, no such airport.");
                            delete Runw;
                        }
                    }
                }
                //taxipoint
                for (TiXmlElement* elemAtt = elem->FirstChildElement(); elemAtt!= NULL; elemAtt = elemAtt->NextSiblingElement()){
                    string AttName = elemAtt->Value();
                    if (AttName == "TAXIROUTE"){
                        TaxiRoute* Taxi = new TaxiRoute();

                        for (TiXmlElement* SubelemAtt = elemAtt->FirstChildElement(); SubelemAtt!= NULL; SubelemAtt = SubelemAtt->NextSiblingElement()) {

                            string SubAttName = SubelemAtt->Value();
                            string SubAttValue = SubelemAtt->GetText();

                            if (SubAttName == "taxipoint"){
                                Taxi->addTaxiPoint(SubAttValue);
                            }
                            else if (SubAttName == "crossing") {
                                for (int i=0; i< (signed) Runw->getAirport()->Runways.size(); i++){
                                    if (Runw->getAirport()->Runways[i]->getName() == SubAttValue){
                                        Taxi->addCrossing(SubAttValue);
                                        break;
                                    }
                                    else if (i == (signed) Runw->getAirport()->Runways.size()-1){
                                        errorMessage("Failed to create taxicrossing.");
                                        delete Taxi;
                                    }
                                }
                            }
                            else {
                                errorMessage("Failed to create taxiroute.");
                                delete Taxi;
                            }
                        }
                        Runw->setTaxiRoute(Taxi);
                        continue;
                    }
                }

                succesMessage("Runway added (" + Runw->getName() + ")");

                continue;
            }
        }
        // Airplanes
        for ( TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement() ){
            string elemName = elem->Value();

            if (elemName == "AIRPLANE") {
                Airplane *Plane = new Airplane();

                for (TiXmlElement* elemAtt = elem->FirstChildElement(); elemAtt!= NULL; elemAtt = elemAtt->NextSiblingElement()){
                    string AttName = elemAtt->Value();


                    if (AttName == "FLIGHTPLAN"){
                        FlightPlan* Flight = new FlightPlan();
                        for (TiXmlElement* SubelemAtt = elemAtt->FirstChildElement(); SubelemAtt!= NULL; SubelemAtt = SubelemAtt->NextSiblingElement()) {
                            string SubAttName = SubelemAtt->Value();
                            string SubAttValue = SubelemAtt->GetText();

                            if (SubAttName == "destination"){
                                Flight->setDestination(SubAttValue);
                            }
                            else if (SubAttName == "departure") {
                                int i;
                                istringstream(SubAttValue) >> i;
                                Flight->setDeparture(i);
                            }
                            else if (SubAttName == "arrival") {
                                int i;
                                istringstream(SubAttValue) >> i;
                                Flight->setArrival(i);
                            }
                            else if (SubAttName == "interval") {
                                int i;
                                istringstream(SubAttValue) >> i;
                                Flight->setInterval(i);
                            }
                            else {
                                errorMessage("Failed to create flightplan.");
                                delete Flight;
                            }
                        }
                        Plane->setFlightPlan(Flight);
                        continue;
                    }
                    string AttValue = elemAtt->GetText();
                    Plane->setVar(AttName, string(AttValue));
                }

                Airplanes.push_back(Plane);

                succesMessage("Plane added (" + Plane->getCallsign() + ")");

                continue;
            }
        }
    }
}

AirportHandler::AirportHandler() {}

AirportHandler::~AirportHandler() {

    for (unsigned int i = 0; i < Airplanes.size(); i++){
        delete Airplanes[i];

    }

    for (unsigned int i = 0; i < Airports.size(); i++) {
        delete Airports[i];

    }
}

const vector<Airport *> &AirportHandler::getAirports() const {
    return Airports;
}

void AirportHandler::setAirports(const vector<Airport *> &Airports) {

    REQUIRE(validAirports(Airports), "Valid airports");

    AirportHandler::Airports = Airports;
    ENSURE(Airports == AirportHandler::Airports, "Set Airports");

}

const vector<Airplane *> &AirportHandler::getAirplanes() const {
    return Airplanes;
}

void AirportHandler::setAirplanes(const vector<Airplane *> &Airplanes) {

    REQUIRE(validAirplanes(Airplanes), "Valid airplanes");

    AirportHandler::Airplanes = Airplanes;

}

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

void AirportHandler::fileOutput() {

    string str = AirportHandler::getInfo();

    fstream file;
    file.open("test.txt", fstream::out);
    file << str;
    file.close();

}

void AirportHandler::addAirplane(Airplane *Plane) {

    REQUIRE(validAiplane(Plane), "Valid airplane");

    Airplanes.push_back(Plane);
    ENSURE(Airplanes[Airplanes.size()-1] == Plane, "Plane added");

}

void AirportHandler::removeAirplane(string callsign){

    REQUIRE(airplaneExists(callsign), "Airplane exists");

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        if (Airplanes[i]->getCallsign() == callsign) {
            Airplanes[i]->setAirport(NULL);
            delete Airplanes[i];
            Airplanes[i] = Airplanes[Airplanes.size()-1];
            Airplanes.resize(Airplanes.size()-1);

            succesMessage("Airplane Deleted (" + callsign + ")" );
            return;
        }
    }

}

Airport *AirportHandler::getAirport(string iata) {
    for (unsigned int i = 0; i < Airports.size(); i++){
        if (Airports[i]->getIata() == iata){
            return Airports[i];
        }
    }
    return NULL;
}

void AirportHandler::addAirport(Airport *Port) {

    REQUIRE(validAirport(Port), "Valid airport");

    Airports.push_back(Port);
    ENSURE(Airports[Airports.size()-1] == Port, "Airport added");

}

void AirportHandler::removeAirport(string callsign){

    REQUIRE(airportExists(callsign), "Airport exists");

    for (unsigned int i = 0; i < Airports.size(); i++) {
        if (Airports[i]->getCallsign() == callsign) {

            const vector<Runway *> Runways;
            Airports[i]->setRunways(Runways);

            const vector<bool> occup;
            Airports[i]->setGatesOccupied(occup);

            delete Airports[i];
            Airports[i] = Airports[Airports.size()-1];
            Airports.resize(Airports.size()-1);

            succesMessage("Airplane Deleted (" + callsign + ")" );
            return;

        }
    }

}

bool AirportHandler::airplaneExists(string callsign) {

    for (unsigned int i = 0; i< Airplanes.size(); i++){
        if (Airplanes[i]->getCallsign() == callsign){
            return true;
        }
    }
    return false;

}

bool AirportHandler::airportExists(string callsign) {
    for (unsigned int i = 0; i< Airports.size(); i++){
        if (Airports[i]->getCallsign() == callsign){
            return true;
        }
    }
    return false;
}

bool AirportHandler::validFileName(string name) {
    const char *cstr = name.c_str();
    TiXmlDocument doc(cstr);

    return doc.LoadFile();

}

bool AirportHandler::validAirplanes(vector<Airplane *> Planes) {

    vector<string> names;
    for (unsigned int i = 0; i< Planes.size(); i++){
        string name = Planes[i]->getCallsign();
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

bool AirportHandler::validAiplane(Airplane *Plane) {

    if (Plane->getCallsign() == ""){
        return false;

    }

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        if (Airplanes[i]->getCallsign() == Plane->getCallsign()){
            return false;
        }
    }

    return true;

}

bool AirportHandler::validAirport(Airport* Port) {

    if (Port->getCallsign() == ""){
        return false;

    }
    for (unsigned int i = 0; i < Airports.size(); i++) {
        if (Airports[i]->getCallsign() == Port->getCallsign()){
            return false;

        }
    }

    return true;
}

void AirportHandler::runSimulation(string name) {

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        Airplanes[i]->initSimulation(Airports[0]);

    }

    double nowtime = time(NULL);
    double startTime = nowtime;

    Airport* Port = getAirport(name);

    while (!airportEmpty(Airports[0])) {

        double later = time(NULL);
        double deltaTime = difftime(later, nowtime);

        if (deltaTime >= TimeUnit){

            nowtime += TimeUnit ;

            double passedTimeUnits = (nowtime - startTime)/TimeUnit;

            cout << timeToString(passedTimeUnits);

            for (unsigned int i = 0; i < Airplanes.size(); i++) {
                Airplane *Plane = Airplanes[i];
                if (Plane->notFinished(Port)) {
                    if (Plane->getTime() > 0) {

                        Plane->execTask(Port);

                    } else {
                        Plane->finishtask(Port);
                        Plane->nextTask(Port);

                    }
                }
            }
        }
    }

}

bool AirportHandler::airportEmpty(Airport *Port) {

    if (Port->getFreeRunways().size() == Port->getRunways().size()){
        if (Port->getFreeGates().size() == unsigned (Port->getGates())){
            return true;
        }
    }
    return false;

}

void AirportHandler::printAirport(string & AirportIata) {

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

string AirportHandler::timeToString(double passedTimeUnits){

    passedTimeUnits += simulationStartTime*60;

    double hour = floor(passedTimeUnits/60);
    double minutes = int(passedTimeUnits)%60;

    stringstream ss;

    if (minutes < 10){
        ss << hour << ":0" << minutes << endl;

    }else{
        if (minutes == 0){
            ss << hour << ":" << "00" << endl;

        }else{
            ss << hour << ":" << minutes << endl;

        }
    }

    return ss.str();

}
