//
// Created by oliviervh on 01.03.18.
//

#include "AirportHandler.h"
#include "AirplaneClass.h"
#include <algorithm>
#include <vector>




AirportHandler::AirportHandler() {
    self = this;

}

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
    return AirportHandler::airports;
}
void AirportHandler::setAirports(const vector<Airport *> &airports) {

    REQUIRE(AirportHandler::validAirports(airports), "Valid airports");

    AirportHandler::airports = airports;
    ENSURE(AirportHandler::airports == airports, "Set airports");

}

const vector<Airplane *> &AirportHandler::getAirplanes() const {
    return AirportHandler::airplanes;
}
void AirportHandler::setAirplanes(const vector<Airplane *> &airplanes) {

    REQUIRE(AirportHandler::validAirplanes(airplanes), "Valid airplanes");

    AirportHandler::airplanes = airplanes;

    ENSURE(AirportHandler::airplanes == airplanes, "airplanes set");

}

Airport *AirportHandler::getAirport(const string &iata) {
    for (unsigned int i = 0; i < AirportHandler::airports.size(); i++){
        if (AirportHandler::airports[i]->getIata() == iata){
            return AirportHandler::airports[i];
        }
    }
    return NULL;
}


//add remove
void AirportHandler::addAirplane(Airplane *airplane) {

    REQUIRE(AirportHandler::validAirplane(airplane), "Valid airplane");

    AirportHandler::airplanes.push_back(airplane);
    ENSURE(AirportHandler::airplaneExists(airplane->getNumber()), "airplane added");

}

void AirportHandler::removeAirplane(const string &number){

    REQUIRE(AirportHandler::airplaneExists(number), "Airplane exists");

    for (unsigned int i = 0; i < AirportHandler::airplanes.size(); i++) {
        if (AirportHandler::airplanes[i]->getNumber() == number) {
            AirportHandler::airplanes[i]->setAirport(NULL);
            delete AirportHandler::airplanes[i];
            AirportHandler::airplanes[i] = AirportHandler::airplanes[AirportHandler::airplanes.size()-1];
            AirportHandler::airplanes.resize(AirportHandler::airplanes.size()-1);

            //succesMessage("Airplane Deleted (" + callsign + ")" );
            return;
        }
    }

    ENSURE(!AirportHandler::airplaneExists(number), "Airplane doesn't exist");

}

void AirportHandler::addAirport(Airport *airport) {

    REQUIRE(AirportHandler::validAirport(airport), "Valid airport");

    AirportHandler::airports.push_back(airport);
    ENSURE(AirportHandler::airportExists(airport->getIata()), "Airport added");

}

void AirportHandler::removeAirport(const string &iata){

    REQUIRE(airportExists(iata), "Airport exists");

    for (unsigned int i = 0; i < AirportHandler::airports.size(); i++) {
        if (AirportHandler::airports[i]->getIata() == iata) {

            const vector<Runway *> Runways;
            AirportHandler::airports[i]->setRunways(Runways);

            const vector<bool> occup;
            AirportHandler::airports[i]->setGatesOccupied(occup);

            delete airports[i];
            AirportHandler::airports[i] = AirportHandler::airports[AirportHandler::airports.size()-1];
            AirportHandler::airports.resize(AirportHandler::airports.size()-1);

            return;

        }
    }

    ENSURE(!AirportHandler::airportExists(iata), "Airport added");

}

ESuccess AirportHandler::addXmlData(const string &fileName) {

    string errorFile = fileName.substr(0, fileName.size() - 4) + "Error.txt";

    ofstream errStream(errorFile.c_str());
    ESuccess endResult = success;

    // Open XML
    const char *cstr = fileName.c_str();
    TiXmlDocument doc(cstr);
    doc.LoadFile();

    if(!doc.LoadFile()) {
        errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << endl;
        return importAborted;
    };


    TiXmlElement* root = doc.FirstChildElement();

    // If Xml isn't empty
    if (root != NULL){
        if (root->ValueTStr() != "AirportInfo"){
            errStream << "XML PARTIAL IMPORT: Expected <AirportInfo> ... </AirportInfo> and got <"
                      << root->Value() <<  "> ... </" << root->Value() << ">." << endl;
            endResult = partialImport;

        }else {

            // airports
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();
                if (elemName == "AIRPORT") {
                    Airport *airport = new Airport();
                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {
                        string AttName = elemAtt->Value();
                        string AttValue = elemAtt->GetText();

                        if (AttName  == "name"){
                            airport->setName(AttValue);

                        }

                        else if (AttName  == "iata"){
                            airport->setIata(AttValue);

                        }

                        else if (AttName  == "callsign"){
                            airport->setCallsign(AttValue);

                        }

                        else if (AttName  == "gates"){
                            if (isNumber(AttValue)){
                                int i;
                                istringstream(AttValue) >> i;
                                airport->setGates(i);
                            }
                        }else{
                            errStream << "XML PARTIAL IMPORT: Invalid attribute name at airport.\n" ;
                            endResult = partialImport;

                        }
                    }

                    if (airport->isValid()){
                        AirportHandler::airports.push_back(airport);

                    }else{
                        errStream << "XML PARTIAL IMPORT: Invalid/Undefined attribute(s) at airport.\n" ;
                        endResult = partialImport;

                    }


                    continue;
                }else{
                    if (elemName != "RUNWAY" && elemName != "AIRPLANE"){
                        errStream << "XML PARTIAL IMPORT: Invalid Element Name (not 'AIRPORT', 'RUNWAY' or 'AIRPLANE').\n" ;
                        endResult = partialImport;

                    }

                }
            }
            // Runways
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {

                string elemName = elem->Value();
                if (elemName == "RUNWAY") {
                    Runway *Runw = new Runway();

                    Airport* tempPort = NULL;

                    // Loop over Variables
                    //attributes
                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {

                        string AttName = elemAtt->Value();
                        if (AttName != "airport" && AttName != "TAXIROUTE") {
                            string AttValue = elemAtt->GetText();

                            if (AttName == "name"){
                                Runw->setName(AttValue);

                            }

                            else if (AttName == "type"){
                                if (AttValue == "grass" || AttValue == "asphalt") {
                                    Runw->setType(AttValue);
                                }
                            }

                            else if (AttName == "length"){
                                if (isNumber(AttValue)) {
                                    int i;
                                    istringstream(AttValue) >> i;
                                    Runw->setLength(i);
                                }
                            }else{
                                errStream << "XML PARTIAL IMPORT: invalid attribute name at runway.\n";
                                endResult = partialImport;

                            }

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
                            for (unsigned int i = 0; i < AirportHandler::airports.size(); i++) {
                                if (AirportHandler::airports[i]->getIata() == AttValue) {
                                    tempPort = AirportHandler::airports[i];
                                    break;
                                }

                            }

                            if (tempPort == NULL) {
                                errStream << "XML PARTIAL IMPORT: Invalid value for attribute airport at Runway.\n" ;
                                endResult = partialImport;

                            }
                        }
                    }

                    if (tempPort == NULL){
                        errStream << "XML PARTIAL IMPORT: failed to create runway.(No/Non existing Airport)\n";
                        endResult = partialImport;
                        delete Runw;
                        continue;
                    }else{
                        if (Runw->getName() != "" && (Runw->getType() == "grass" || Runw->getType() == "asphalt")) {
                            if (!tempPort->runwayExists(Runw->getName())){
                                tempPort->addRunway(Runw);
                            }else{
                                errStream << "XML PARTIAL IMPORT: failed to create runway.(Duplicate name)\n";
                                endResult = partialImport;
                                delete Runw;
                                continue;

                            }
                        }else{
                            errStream << "XML PARTIAL IMPORT: failed to create runway.(No name)\n";
                            endResult = partialImport;
                            delete Runw;
                            continue;

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
                                            Taxi->addTaxiCrossing(SubAttValue);
                                            break;
                                        } else if (i == (signed) Runw->getAirport()->getRunways().size() - 1) {
                                            errStream << "XML PARTIAL IMPORT: failed to create taxipoint.\n";
                                            endResult =  partialImport;

                                        }
                                    }
                                } else {
                                    errStream << "XML PARTIAL IMPORT: failed to create taxiRoute.\n";
                                    endResult =  partialImport;

                                }
                            }

                            Runw->setTaxiRoute(Taxi);
                            continue;
                        }
                    }

                    if (!Runw->isValid()) {
                        errStream << "XML PARTIAL IMPORT: failed to create runway.\n";
                        endResult = partialImport;
                        tempPort->removeRunway(Runw->getName());

                    }
                    continue;

                }
            }

            // airplanes
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string elemName = elem->Value();

                if (elemName == "AIRPLANE") {

                    Airplane *airplane = NULL;

                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {
                        string attName = elemAtt->Value();
                        if (attName == "type") {
                            string attValue = elemAtt->GetText();

                            if (attValue == "private") {
                                airplane = new AirplanePrivate();

                            } else if (attValue == "airline") {
                                airplane = new AirplaneAirline();

                            } else if (attValue == "militairy") {
                                airplane = new AirplaneMilitairy();

                            } else if (attValue == "emergency") {
                                airplane = new AirplaneEmergency();

                            }
                            break;

                        }
                    }

                    if (airplane == NULL){
                        errStream << "XML PARTIAL IMPORT: invalid or no type attribute for plane\n";
                        endResult = partialImport;
                        continue;

                    }

                    for (TiXmlElement *elemAtt = elem->FirstChildElement();
                         elemAtt != NULL; elemAtt = elemAtt->NextSiblingElement()) {
                        string AttName = elemAtt->Value();

                        string type;

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
                                    endResult = partialImport;

                                }
                            }

                            if (!Flight->isValid()){
                                errStream << "XML PARTIAL IMPORT: invalid value of the flightplan\n";
                                endResult = partialImport;
                                delete Flight;
                                Flight = NULL;

                            }

                            airplane->setFlightPlan(Flight);
                            continue;

                        }

                        string AttValue = elemAtt->GetText();

                        if (AttName == "number"){
                            airplane->setNumber(AttValue);

                        } else if (AttName == "model"){
                            airplane->setModel(AttValue);

                        } else if (AttName == "callsign"){
                            airplane->setCallsign(AttValue);

                        } else if (AttName == "status"){
                            if (AttValue == "Gate" ) {
                                airplane->setState(gTechnicalCheck);
                            }
                            else if (AttValue == "Approaching" ) {
                                airplane->setState(incoming);

                            }
                        } else if (AttName == "type"){


                        } else if (AttName == "engine"){
                            if (airplane->validEngineType(AttValue)) {
                                airplane->setEngine(AttValue);

                            }
                        } else if (AttName == "size"){
                            if (airplane->validSize(AttValue)) {
                                airplane->setSize(AttValue);

                            }
                        } else if (AttName == "passengers"){
                            if (isNumber(AttValue)) {
                                int i;
                                istringstream(AttValue) >> i;
                                airplane->setPassengers(i);
                                airplane->setPassengerCapacity(i);
                            }
                        } else if (AttName == "height"){
                            if (isNumber(AttValue)) {
                                int i;
                                istringstream(AttValue) >> i;
                                airplane->setHeight(i);
                            }
                        } else if (AttName == "fuel"){
                            if (isNumber(AttValue)) {
                                int i;
                                istringstream(AttValue) >> i;
                                airplane->setFuel(i);
                                airplane->setFuelCapacity(i);
                            }
                        } else{
                            errStream << "XML PARTIAL IMPORT: invalid attribute names at airplane. \n";
                            endResult = partialImport;
                        }
                    }

                    if (airplane->isValid()) {

                        airplane->setSquawkCode();
                        if (AirportHandler::validAirplane(airplane)) {
                            AirportHandler::airplanes.push_back(airplane);
                        } else {
                            errStream << "XML PARTIAL IMPORT: double defined Airplane\n";
                            endResult = partialImport;
                            delete airplane;
                        }
                    }else{
                        errStream << "XML PARTIAL IMPORT: invalid or non defined Airplane values\n";
                        endResult = partialImport;
                        delete airplane;
                    }

                    continue;
                }
            }
        }
    }

    return endResult;

}


string AirportHandler::timeToString(double passedTimeUnits){

    passedTimeUnits += AirportHandler::gSimulationStartTime*kMinutesPerHour;

    double hour = int(floor(passedTimeUnits/kMinutesPerHour))%kHoursPerDay;
    double minutes = int(passedTimeUnits)%kMinutesPerHour;

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
        string name = airplanes[i]->getNumber();
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
        string name = airports[i]->getIata();
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

    for (unsigned int i = 0; i < AirportHandler::airplanes.size(); i++) {
        if (AirportHandler::airplanes[i]->getNumber() == airplane->getNumber()){
            return false;
        }
    }

    return true;

}
bool AirportHandler::validAirport(Airport* airport) {

    if (airport->getIata() == ""){
        return false;

    }
    for (unsigned int i = 0; i < AirportHandler::airports.size(); i++) {
        if (AirportHandler::airports[i]->getIata() == airport->getIata()){
            return false;

        }
    }

    return true;
}
bool AirportHandler::airportEmpty(Airport *airport) {

    if (airport->getFreeRunways().size() == airport->getRunways().size()){
        if (airport->getFreeGates().size() == unsigned (airport->getGates())){
            for (unsigned int i = 0; i < AirportHandler::airplanes.size(); i++){
                if (AirportHandler::airplanes[i]->getState() != simulationIsFinished) {
                    return false;

                }
            }
            return true;
        }
    }
    return false;
}
bool AirportHandler::airplaneExists(const string &number) {

    for (unsigned int i = 0; i< AirportHandler::airplanes.size(); i++){
        if (AirportHandler::airplanes[i]->getNumber() == number){
            return true;
        }
    }
    return false;

}
bool AirportHandler::airportExists(const string &iata) {
    for (unsigned int i = 0; i< AirportHandler::airports.size(); i++){
        if (AirportHandler::airports[i]->getIata() == iata){
            return true;
        }
    }
    return false;
}


//simulation
void AirportHandler::runSimulation(const string &iata) {
    REQUIRE(!AirportHandler::getAirports().empty(), "an airport to run a simulation on exists");
    REQUIRE(!AirportHandler::getAirplanes().empty(), "an airplane to run a simulation on exists");
    REQUIRE(!AirportHandler::getAirport(iata)->getRunways().empty(), "a runway to land on exists");

    Airport* airport = getAirport(iata);

    for (unsigned int i = 0; i < AirportHandler::airplanes.size(); i++) {
        AirportHandler::airplanes[i]->initSimulation(airport);
    }

    setStartingTime(AirportHandler::gSimulationStartTime);

    double nowtime = time(NULL);
    double startTime = nowtime;

    bool end = false;
    while (!airportEmpty(airport) && !end) {
        double later = time(NULL);
        double deltaTime = difftime(later, nowtime);

        if (deltaTime >= AirportHandler::gTimeUnit){


            nowtime += AirportHandler::gTimeUnit ;

            double passedTimeUnits = (nowtime - startTime)/AirportHandler::gTimeUnit;
            string tijdnu = getTime();
            while (tijdnu == timeToString(passedTimeUnits)){
                nowtime += AirportHandler::gTimeUnit ;
                passedTimeUnits = (nowtime - startTime)/AirportHandler::gTimeUnit;
            }
            setTime(timeToString(passedTimeUnits));
            setTimePassed(passedTimeUnits);

            AirportHandler::GraphicalAirport3D(iata);

            for (unsigned int i = 0; i < AirportHandler::airplanes.size(); i++) {
                Airplane *airplane = AirportHandler::airplanes[i];

                if (airplane->notFinished()) {
                    if (airplane->getHeight() > 0){
                        airplane->useFuel();
                        airplane->useFuel();
                        airplane->useFuel();
                    }

                    if ( (nowtime - startTime)/AirportHandler::gTimeUnit - 1 > 160){
                        cout << "yes" << endl;
                        end = true;
                    };
                    cout << getTime() << ": " << airplane->getCurrentTask() << " " << airplane->getState() << endl;

                    if (airplane->getOperationTime() > 0) {
                        airplane->continueTask(airport);

                    } else {
                        airplane->execTask(airport);
                    }
                    airplane->setOperationTime(airplane->getOperationTime() - 1);
                    cout << "fuel: " << airplane->getFuel() << "/" << airplane->getFuelCapacity() << endl;
                    cout << "passengers: " << airplane->getPassengers() << "/" << airplane->getPassengerCapacity() << endl << endl;

                }
            }

        }
    }
}


string AirportHandler::getInfo() {

    string s;

    for (unsigned int i = 0; i< AirportHandler::airports.size(); i++ ){
        s+= AirportHandler::airports[i]->getInfo();

    }

    for (unsigned int i = 0; i< AirportHandler::airplanes.size(); i++ ){
        s+= AirportHandler::airplanes[i]->getInfo();

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

    REQUIRE(AirportHandler::airportExists(iata), "Airport exists");

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

    REQUIRE(AirportHandler::airportExists(iata), "Airport exists");

    string document = "3Dfiles/3Doutput" + getTime() + ".ini";
    const char * documentname = document.c_str();

    Airport* airport = AirportHandler::getAirport(iata);
    const vector<Runway *> runways = airport->getRunways();

    // makes vector with all airplanes in the simulation
    vector<Airplane*> unfinishedAirplanes;
    for (unsigned int i=0; i<getAirplanes().size(); i++){
        if (getAirplanes()[i]->getState() != simulationIsFinished){
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
    int figureNumber = 0;


    s += "[General]\n";
    s += "size = 1000\n";
    s += "backgroundcolor = (0, 0, 0)\n";
    s += "type = ZBufferedWireframe\n";
    s += "eye = (50, -100, 100)\n";
    s += "nrFigures = " + intToString(aantalfiguren) + "\n";
    s += "\n";

    // draws gates
    for (int i=0; i<airport->getGates(); i++){
        s += "[Figure" + intToString(figureNumber) + "]\n";
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
        figureNumber += 1;
    }

    // draws runways
    for (unsigned int i=0; i<airport->getRunways().size(); i++){
        s += "[Figure" + intToString(figureNumber) + "]\n";
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
        figureNumber += 1;
    }

    // draws all taxipoints
    for (unsigned int i=0; i<longesttaxi->getTaxiPoints().size(); i++){
        s += "[Figure" + intToString(figureNumber) + "]\n";
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
        figureNumber += 1;
    }
    // draws all taxicrossings
    for (unsigned int i=0; i<longesttaxi->getTaxiCrossings().size(); i++){
        s += "[Figure" + intToString(figureNumber) + "]\n";
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
        figureNumber += 1;
    }

    // draws all airplanes
    for (unsigned int i=0; i<unfinishedAirplanes.size(); i++){
        string task = unfinishedAirplanes[i]->getCurrentTask();
        Airplane* airplane = unfinishedAirplanes[i];
        EState state = airplane->getState();

        //incoming
        if (state == init){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (50, 0, " + intToString(ceil(airplane->getHeight()/200)) + ")\n";
            s += "color = (0, 0, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
        //incoming
        if (state == incoming){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (55, 0, " + intToString(ceil(airplane->getHeight()/200)) + ")\n";
            s += "color = (0.2, 0.2, 0.2)\n";
            s += "\n";
            figureNumber += 1;
        }
        //descending
        else if (state == descending || state == descendARMS || state == descendWait || state == descendBRMS || state == descendCRMS){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (50, 0, " + intToString(ceil(airplane->getHeight()/200)) + ")\n";
            s += "color = (0, 1, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
        //emergency (in)
        else if (state == outOfFuel || state == iEmergencyRMS || state == iEmergencyMMS){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (50, 0, " + intToString(ceil(airplane->getHeight()/200)) + ")\n";
            s += "color = (1, 0.5, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
        //emergency (out)
        else if (state == oEmergencyRMS || state == oEmergencyMMS){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (50, 0, " + intToString(ceil(airplane->getHeight()/200)) + ")\n";
            s += "color = (1, 0, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
        //final approach + landing
        else if (state == onFinalApproach || state == landing) {
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2 + 15) + ", " +
                 intToString(20 * (airplane->getAttemptRunway()->getTaxiRoute()->getTaxiPoints().size() -1 + 1))
                 + ", " + intToString(ceil(airplane->getHeight()/200)) + ")\n";
            s += "color = (1, 1, 1)\n";
            figureNumber += 1;
        }
        //emergency refuel
        else if (state == eRefuel){
            s += "[Figure" + intToString(figureNumber) + "]\n";
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
            figureNumber += 1;
        }
        //normal refuel
        else if (state == gRefuel){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate() * 6) + ", 0, 0)\n";
            s += "color = (1, 0.5, 1)\n";
            s += "\n";
            figureNumber += 1;
        }
        //inGate and taxiRequest
        else if (state == inGate || state == taxiRequest){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate() * 6) + ", 0, 0)\n";
            s += "color = (0, 1, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
        //eLanded
        else if (state == eLanded){
            s += "[Figure" + intToString(figureNumber) + "]\n";
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
            s += "color = (1, 0.5, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
        //eUnboardingPassengers
        else if (state == eUnboardingPassengers){
            s += "[Figure" + intToString(figureNumber) + "]\n";
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
            figureNumber += 1;
        }
        // gUnboardingPassengers
        else if (state == gUnboardingPassengers){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate()*6) +", 0, 0)\n";
            s += "color = (1, 1, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
       //eTechnicalCheck
        else if (state == eTechnicalCheck){
            s += "[Figure" + intToString(figureNumber) + "]\n";
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
            figureNumber += 1;
        }
        //gTechnicalCheck
        else if (state == gTechnicalCheck){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate()*6) +", 0, 0)\n";
            s += "color = (1, 0, 1)\n";
            s += "\n";
            figureNumber += 1;
        }
        //holding point (unfinished)
        else if (state == onHoldingPoint || state == holdingPointRMS || state == holdingPointMMS || state == holdingpointCMS){
            s += "[Figure" + intToString(figureNumber) + "]\n";
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
            figureNumber += 1;
        }
        //on taxipoint
        else if (state == onTaxiPoint || state == taxiPointMMS || state == taxiPointCMS){
            for (unsigned int j = 0; j < longesttaxi->getTaxiPoints().size(); j++) {
                if (airplane->getTaxiPoint() == longesttaxi->getTaxiPoints()[j]) {
                    s += "[Figure" + intToString(figureNumber) + "]\n";
                    s += "type = \"Sphere\"\n";
                    s += "n = 2\n";
                    s += "scale = 2\n";
                    s += "rotateX = 0\n";
                    s += "rotateY = 0\n";
                    s += "rotateZ = 0\n";
                    s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2 + 10) + ", " +
                    intToString(20 * (j + 1) - 5) + ", 0)\n";
                    s += "color = (1, 1, 1)\n";
                    s += "\n";
                    figureNumber += 1;
                }
            }
        }
        //board passengers
        else if (state == boardPassengers){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate()*6) +", 0, 0)\n";
            s += "color = (1, 1, 0.5)\n";
            s += "\n";
            figureNumber += 1;
        }

        else if (state == ifr ||  state == ifrRMS || state == ifrMMS || state == ifrCMS || state == pushbackRMS || state == pushbackMMS || state == pushbackCMS){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString(unfinishedAirplanes[i]->getGate()*6) +", 0, 0)\n";
            s += "color = (0.75, 0.25, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
        //onRunway
        else if (state == onRunway){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            s += "center = (" + intToString((airport->getGates() - 1) * 6 / 2 + 15) + ", " +
                 intToString(20 * (airplane->getRunway()->getTaxiRoute()->getTaxiPoints().size())) + ", 0)\n";
            s += "color = (0, 1, 0)\n";
            s += "\n";
            figureNumber += 1;
        }
        //ascending
        else if (state == ascending){
            s += "[Figure" + intToString(figureNumber) + "]\n";
            s += "type = \"Sphere\"\n";
            s += "n = 2\n";
            s += "scale = 2\n";
            s += "rotateX = 0\n";
            s += "rotateY = 0\n";
            s += "rotateZ = 0\n";
            for (unsigned int j=0; j<airport->getRunways().size(); j++){
                if (airplane->getRunway() == airport->getRunways()[j]){
                    s += "center = ("+ intToString((airport->getGates()-1)*6 /2  - 10) + ", "
                         + intToString(20*(j+1)) + ", " + intToString(ceil(airplane->getHeight()/200)) + ")\n";
                }
            }
            s += "color = (1, 1, 1)\n";
            s += "\n";
            figureNumber += 1;
        }
        //onTaxiCrossing, going to gate
        else if ((state == onTaxiCrossing || state == taxiCrossingRMS || state == taxiCrossingMMS || state == taxiCrossingCMS) && airplane->getCurrentTask() == "going to gate") {
            for (unsigned int j = 0; j < longesttaxi->getTaxiCrossings().size(); j++) {
                if (airplane->getTaxiCrossing() == longesttaxi->getTaxiCrossings()[j]) {
                    s += "[Figure" + intToString(figureNumber) + "]\n";
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
                    figureNumber += 1;
                }
            }
        }
        //onTaxiCrossing, going to runway
        else if ((state == onTaxiCrossing || state == taxiCrossingRMS || state == taxiCrossingMMS || state == taxiCrossingCMS) && airplane->getCurrentTask() == "going to runway"){
            for (unsigned int j = 0; j < longesttaxi->getTaxiCrossings().size(); j++) {
                if (airplane->getTaxiCrossing() == longesttaxi->getTaxiCrossings()[j]) {
                    s += "[Figure" + intToString(figureNumber) + "]\n";
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
                    figureNumber += 1;
                }
            }
        }
        // crossing
        else if (state == taxiCrossingNF){
            for (unsigned int j = 0; j < longesttaxi->getTaxiCrossings().size(); j++) {
                if (unfinishedAirplanes[i]->getTaxiCrossing() == longesttaxi->getTaxiCrossings()[j]) {
                    s += "[Figure" + intToString(figureNumber) + "]\n";
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
                    figureNumber += 1;
                }
            }
        }

           /*





           else if (state == "lined up"){
               s += "[Figure" + intToString(i + airport->getRunways().size()
                                            + airport->getGates()+longesttaxi->getTaxiPoints().size()
                                            + longesttaxi->getTaxiCrossings().size()) + "]\n";
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


            */
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
    return (this == AirportHandler::self);
}

void AirportHandler::sortPlanesBySquawk() {

    for (unsigned int i = 0; i < airplanes.size(); i++){
        for (unsigned int j = airplanes.size() - i; j > 1; j--){
            if (airplanes[i]->getSquawkCode() < airplanes[i-1]->getSquawkCode() ){
                Airplane* a = airplanes[i];
                airplanes[i] = airplanes[j];
                airplanes[j] = a;
            }
        }
    }

}


