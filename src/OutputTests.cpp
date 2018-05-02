//
// Created by oliviervh on 30.04.18.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "gtest/gtest.h"

#include "AirplaneClass.h"
#include "AirportClass.h"
#include "AirportHandler.h"
#include "MessageSystem.h"
#include "RunwayClass.h"

namespace {

    class AirportHandlerFunctionOutput : public ::testing::Test{
    protected:
        AirportHandlerFunctionOutput() {

        }

        virtual void SetUp() {
            handler = new AirportHandler();
            planeA = new Airplane();
            planeB = new Airplane();
            airportA = new Airport();
            airportB = new Airport();
        }

        virtual void TearDown() {
            delete handler;

        }

        AirportHandler* handler;
        AirportHandler* handlerNoInit;
        Airplane* planeA;
        Airplane* planeB;
        Airport* airportA;
        Airport* airportB;
        string filename;

    };

    TEST_F(AirportHandlerFunctionOutput, GetInfo){

        handler->addXmlData("XMLTests/TestVolledigeLuchthaven8.xml");

        string str = handler->getInfo();

        EXPECT_TRUE(!str.empty());

    }

    TEST_F(AirportHandlerFunctionOutput, FileOutput){

        handler->addXmlData("XMLTests/TestVolledigeLuchthaven8.xml");

        // No name given
        handler->fileOutput();
        EXPECT_TRUE(FileCompare("AirportInfo.txt", "AirportInfoResult.txt"));

        // Custom name
        handler->fileOutput("AirportInfoCustom.txt");
        EXPECT_TRUE(FileCompare("AirportInfoCustom.txt", "AirportInfoCustomResult.txt"));

    }

    TEST_F(AirportHandlerFunctionOutput, GraphicalOutput2D){

        handler->addXmlData("XMLTests/TestVolledigeLuchthaven8.xml");

        EXPECT_TRUE(handler->airportExists("ANR"));
        EXPECT_NO_FATAL_FAILURE(handler->GraphicalAirport2D("ANR"));

        EXPECT_FALSE(handler->airportExists("NONONO"));
        EXPECT_DEATH(handler->GraphicalAirport2D("NONONO"), "Assertion.*failed");

        EXPECT_TRUE(FileCompare("ANR.txt", "ANRResult.txt"));

    }

    TEST_F(AirportHandlerFunctionOutput, GraphicalOutput3D){

        handler->addXmlData("XMLTests/TestVolledigeLuchthaven8.xml");

        EXPECT_TRUE(handler->airportExists("ANR"));
        EXPECT_NO_FATAL_FAILURE(handler->GraphicalAirport3D("ANR"));

        EXPECT_FALSE(handler->airportExists("NONONO"));
        EXPECT_DEATH(handler->GraphicalAirport3D("NONONO"), "Assertion.*failed");

        string strTime = getTime();

        EXPECT_TRUE(FileCompare("3Dfiles/3Doutput.ini", "3Dfiles/3DoutputResult.ini"));

    }

    class RunwayOutput : public ::testing::Test {
    protected:

        RunwayOutput() {
        }

        virtual void SetUp() {
            runway = new Runway();
            airport = new Airport();
            taxiRoute = new TaxiRoute();
        }

        virtual void TearDown() {
            delete runway;
            delete airport;
            delete taxiRoute;
        }

        Airport *airport;
        Runway *runway;
        TaxiRoute* taxiRoute;
        string myString;
        int myInt;
    };

    TEST_F(RunwayOutput, setName) {
        myString = "name";
        runway->setName(myString);
        EXPECT_EQ(runway->getName(), "name");
    }

    TEST_F(RunwayOutput, setType) {
        myString = "grass";
        runway->setType(myString);
        EXPECT_EQ(runway->getType(), "grass");
        myString = "asphalt";
        runway->setType(myString);
        EXPECT_EQ(runway->getType(), "asphalt");
    }

    TEST_F(RunwayOutput, setAirport) {
        EXPECT_NO_FATAL_FAILURE(runway->setAirport(airport));
        EXPECT_EQ(runway->getAirport(), airport);
    }

    TEST_F(RunwayOutput, setOccupied) {
        EXPECT_NO_FATAL_FAILURE(runway->setOccupied(true));
        EXPECT_EQ(runway->isOccupied(), true);
    }

    TEST_F(RunwayOutput, setLength) {
        myInt = 500;
        EXPECT_NO_FATAL_FAILURE(runway->setLength(myInt));
        EXPECT_EQ(runway->getLength(), 500);
    }

    TEST_F(RunwayOutput, setTaxiRoute) {
        EXPECT_NO_FATAL_FAILURE(runway->setTaxiRoute(taxiRoute));
        EXPECT_EQ(runway->getTaxiRoute(), taxiRoute);
    }

    TEST_F(RunwayOutput, setHoldingShortOccupied) {
        EXPECT_NO_FATAL_FAILURE(runway->setHoldingShortOccupied(true));
        EXPECT_EQ(runway->getHoldingShortOccupied(), true);
    }

    TEST_F(RunwayOutput, setWaitingOnRunway) {
        EXPECT_NO_FATAL_FAILURE(runway->setWaitingOnRunway(true));
        EXPECT_EQ(runway->getWaitingOnRunway(), true);
    }

    TEST_F(RunwayOutput, setCrossing) {
        EXPECT_NO_FATAL_FAILURE(runway->setCrossing(true));
        EXPECT_EQ(runway->getCrossing(), true);
    }

    TEST_F(RunwayOutput, setPermissionToCross) {
        EXPECT_NO_FATAL_FAILURE(runway->setPermissionToCross(true));
        EXPECT_EQ(runway->getPermissionToCross(), true);
    }

    TEST_F(RunwayOutput, setOnItsWay) {
        EXPECT_NO_FATAL_FAILURE(runway->setOnItsWay(true));
        EXPECT_EQ(runway->getOnItsWay(), true);
    }

    class TaxiRouteOutput : public ::testing::Test {
    protected:

        TaxiRouteOutput() {

        }

        virtual void SetUp() {
            taxiRoute = new TaxiRoute();
        }

        virtual void TearDown() {
            delete taxiRoute;
        }

        Airport *airport;
        Runway *runway;
        TaxiRoute* taxiRoute;
        string myString;
    };

    TEST_F(TaxiRouteOutput, addTaxiPoint) {
        myString = "point";
        EXPECT_NO_FATAL_FAILURE(taxiRoute->addTaxiPoint(myString));
        EXPECT_EQ(taxiRoute->getTaxiPoints()[taxiRoute->getTaxiPoints().size()-1], myString);
    }

    TEST_F(TaxiRouteOutput, addTaxiCrossing) {
        myString = "crossing";
        EXPECT_NO_FATAL_FAILURE(taxiRoute->addTaxiCrossing(myString));
        EXPECT_EQ(taxiRoute->getTaxiCrossings()[taxiRoute->getTaxiCrossings().size()-1], myString);
    }

    class FlightPlanOutput : public ::testing::Test {
    protected:

        FlightPlanOutput() {

        }

        virtual void SetUp() {
            runway = new Runway();
            airport = new Airport();
            taxiRoute = new TaxiRoute();
            flightPlan = new FlightPlan();
        }

        virtual void TearDown() {
            delete runway;
            delete airport;
            delete taxiRoute;
            delete flightPlan;
        }

        Airport *airport;
        Runway *runway;
        TaxiRoute* taxiRoute;
        FlightPlan* flightPlan;
        string myString;
        int myInt;
    };

    TEST_F(FlightPlanOutput, setDestination) {
        myString = "Bahamas";
        EXPECT_NO_FATAL_FAILURE(flightPlan->setDestination(myString));
        EXPECT_EQ(flightPlan->getDestination(), "Bahamas");
    }

    TEST_F(FlightPlanOutput, setDeparture) {
        myInt = 45;
        EXPECT_NO_FATAL_FAILURE(flightPlan->setDeparture(myInt));
        EXPECT_EQ(flightPlan->getDeparture(), 45);
    }

    TEST_F(FlightPlanOutput, setArrival) {
        myInt = 15;
        EXPECT_NO_FATAL_FAILURE(flightPlan->setArrival(myInt));
        EXPECT_EQ(flightPlan->getArrival(), 15);
    }

    TEST_F(FlightPlanOutput, setInterval) {
        myInt = 45;
        EXPECT_NO_FATAL_FAILURE(flightPlan->setInterval(myInt));
        EXPECT_EQ(flightPlan->getInterval(), 45);
    }

    class AirportOutput : public ::testing::Test {
    protected:

        AirportOutput() {

        }

        virtual void SetUp() {
            runway = new Runway();
            runway1 = new Runway();
            airplane = new Airplane();
            airport = new Airport();
            taxiRoute = new TaxiRoute();
        }

        virtual void TearDown() {
            delete airport;
            delete airplane;
            delete taxiRoute;
        }

        Airport *airport;
        Runway *runway;
        Runway * runway1;
        Airplane* airplane;
        TaxiRoute* taxiRoute;
        vector<bool> gatesOccupied;
        vector<Runway*> runways;
        string myString;
        int myInt;
    };

    TEST_F(AirportOutput, setName) {
        myString = "name";
        EXPECT_NO_FATAL_FAILURE(airport->setName(myString));
        EXPECT_EQ(airport->getName(), "name");
    }

    TEST_F(AirportOutput, setIata) {
        myString = "iata";
        EXPECT_NO_FATAL_FAILURE(airport->setIata(myString));
        EXPECT_EQ(airport->getIata(), "iata");
    }

    TEST_F(AirportOutput, setCallsign) {
        myString = "callsign";
        EXPECT_NO_FATAL_FAILURE(airport->setCallsign(myString));
        EXPECT_EQ(airport->getCallsign(), "callsign");
    }

    TEST_F(AirportOutput, setGates) {
        myInt = 6;
        EXPECT_NO_FATAL_FAILURE(airport->setGates(myInt));
        EXPECT_EQ(airport->getGates(), 6);
        EXPECT_EQ(airport->getGatesOccupied().size(), (unsigned) 6);
    }

    TEST_F(AirportOutput, setRunways) {
        runway->setName("name");
        runway->setType("asphalt");
        runway->setLength(200);
        runway1->setName("name1");
        runway1->setType("asphalt");
        runway1->setLength(200);
        runways.push_back(runway);
        runways.push_back(runway1);
        EXPECT_NO_FATAL_FAILURE(airport->setRunways(runways));
        EXPECT_EQ(airport->getRunways(), runways);
    }

    TEST_F(AirportOutput, setGatesOccupied) {
        gatesOccupied.push_back(false);
        gatesOccupied.push_back(true);
        EXPECT_NO_FATAL_FAILURE(airport->setGatesOccupied(gatesOccupied));
        EXPECT_EQ(airport->getGatesOccupied(), gatesOccupied);
    }

    TEST_F(AirportOutput, setWait5000) {
        EXPECT_NO_FATAL_FAILURE(airport->setWait5000(airplane));
        EXPECT_EQ(airport->getWait5000(), airplane);
    }

    TEST_F(AirportOutput, setWait3000) {
        EXPECT_NO_FATAL_FAILURE(airport->setWait3000(airplane));
        EXPECT_EQ(airport->getWait3000(), airplane);
    }

    TEST_F(AirportOutput, setGateOccupied) {
        airport->setGates(4);
        EXPECT_NO_FATAL_FAILURE(airport->setGateOccupied(3,true));
        EXPECT_EQ(airport->getGateOccupied(3), true);
    }

    TEST_F(AirportOutput, getFreeGates) {
        gatesOccupied.push_back(true);
        gatesOccupied.push_back(true);
        airport->setGatesOccupied(gatesOccupied);
        vector<int> freeGates;
        EXPECT_EQ(airport->getFreeGates(),freeGates);
        gatesOccupied.push_back(false);
        airport->setGatesOccupied(gatesOccupied);
        freeGates.push_back(2);
        EXPECT_EQ(airport->getFreeGates(), freeGates);
    }

    TEST_F(AirportOutput, getFreeRunways) {
        runway->setName("name");
        runway->setType("asphalt");
        runway->setLength(200);
        runway1->setName("name1");
        runway1->setType("asphalt");
        runway1->setLength(200);
        runway->setOccupied(true);
        runway1->setOccupied(true);
        airport->addRunway(runway);
        airport->addRunway(runway1);
        vector<int> freeRunways;
        EXPECT_EQ(airport->getFreeRunways(),freeRunways);
        runway->setOccupied(false);
        freeRunways.push_back(0);
        EXPECT_EQ(airport->getFreeRunways(), freeRunways);
    }

    TEST_F(AirportOutput, removeRunway) {
        runway->setName("name");
        runway->setType("asphalt");
        runway->setLength(200);
        airport->addRunway(runway);
        EXPECT_NO_FATAL_FAILURE(airport->removeRunway("name"));
        EXPECT_FALSE(airport->runwayExists("name"));
    }

    class AirplaneOutput: public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        AirplaneOutput() {


        }

        // virtual void SetUp() will be called before each test is run.  You
        // should define it if you need to initialize the variables.
        // Otherwise, this can be skipped.
        virtual void SetUp() {


        }

        // virtual void TearDown() will be called after each test is run.
        // You should define it if there is cleanup work to do.  Otherwise,
        // you don't have to provide it.
        virtual void TearDown() {
        }

        // Declares the variables your tests want to use.
        Airport *airport;
        Airport *airport1;
        Airplane *airplane;
        Airplane *airplane1;
        Airplane *airplane2;
        Runway *runway;
        Runway *runway1;
        FlightPlan* flightPlan;
        TaxiRoute* taxiRoute;
        AirportHandler *D;
    };

    TEST_F(AirplaneOutput, setTechnicalChecked) {
        airplane = new Airplane();
        airplane->setTechnicalChecked(true);
        EXPECT_TRUE(airplane->getTechnicalChecked());
    }

    TEST_F(AirplaneOutput, setNumber) {
        airplane = new Airplane();
        airplane->setNumber("70");
        EXPECT_EQ(airplane->getNumber(), "70");
    }

    TEST_F(AirplaneOutput, setCallsign) {
        airplane = new Airplane();
        airplane->setCallsign("callsign");
        EXPECT_EQ(airplane->getCallsign(), "callsign");
    }

    TEST_F(AirplaneOutput, setModel) {
        airplane = new Airplane();
        airplane->setModel("model");
        EXPECT_EQ(airplane->getModel(), "model");
    }

    TEST_F(AirplaneOutput, setState) {
        airplane = new Airplane();
        airplane->setState("state");
        EXPECT_EQ(airplane->getState(), "state");
    }

    TEST_F(AirplaneOutput, setFuel) {
        airplane = new Airplane();
        airplane->setFuel(5);
        EXPECT_EQ(airplane->getFuel(), 5);
    }

    TEST_F(AirplaneOutput, setHeight) {
        airplane = new Airplane();
        airplane->setHeight(1000);
        EXPECT_EQ(airplane->getHeight(), 1000);
    }

    TEST_F(AirplaneOutput, setFuelCapacity) {
        airplane = new Airplane();
        airplane->setFuelCapacity(10000);
        EXPECT_EQ(airplane->getFuelCapacity(), 10000);
    }

    TEST_F(AirplaneOutput, setPassengers) {
        airplane = new Airplane();
        airplane->setPassengers(100);
        EXPECT_EQ(airplane->getPassengers(), 100);
    }

    TEST_F(AirplaneOutput, setPassengerCapacity) {
        airplane = new Airplane();
        airplane->setPassengerCapacity(100);
        EXPECT_EQ(airplane->getPassengerCapacity(), 100);
    }

    TEST_F(AirplaneOutput, setAirport) {
        airplane = new Airplane();
        airport = new Airport();
        airplane->setAirport(airport);
        EXPECT_EQ(airplane->getAirport(), airport);
    }

    TEST_F(AirplaneOutput, setType) {
        airplane = new Airplane();
        EXPECT_NO_FATAL_FAILURE(airplane->setType("military"));
        EXPECT_EQ(airplane->getType(),"military");
    }

    TEST_F(AirplaneOutput, setEngine) {
        airplane = new Airplane();
        airplane->setEngine("propeller");
        EXPECT_EQ(airplane->getEngine(), "propeller");
    }

    TEST_F(AirplaneOutput, setSize) {
        airplane = new Airplane();
        airplane->setSize("small");
        EXPECT_EQ(airplane->getSize(), "small");
    }

    TEST_F(AirplaneOutput, setOperationTime) {
        airplane = new Airplane();
        airplane->setOperationTime(100);
        EXPECT_EQ(airplane->getOperationTime(), 100);
    }

    TEST_F(AirplaneOutput, setRunway) {
        airplane = new Airplane();
        runway = new Runway();
        airplane->setRunway(runway);
        EXPECT_EQ(airplane->getRunway(), runway);
    }

    TEST_F(AirplaneOutput, setGate) {
        airplane = new Airplane();
        airport = new Airport();
        airplane->setAirport(airport);
        airport->setGates(5);
        airplane->setGate(4);
        EXPECT_EQ(airplane->getGate(), 4);
    }

    TEST_F(AirplaneOutput, setAttemptRunway) {
        airplane = new Airplane();
        runway = new Runway();
        airplane->setAttemptRunway(runway);
        EXPECT_EQ(airplane->getAttemptRunway(), runway);
    }

    TEST_F(AirplaneOutput, setFlightPlan) {
        airplane = new Airplane();
        flightPlan = new FlightPlan();
        airplane->setFlightPlan(flightPlan);
        EXPECT_EQ(airplane->getFlightPlan(), flightPlan);
    }

    TEST_F(AirplaneOutput, setTaxiRoute) {
        airplane = new Airplane();
        taxiRoute = new TaxiRoute();
        airplane->setTaxiRoute(taxiRoute);
        EXPECT_EQ(airplane->getTaxiRoute(), taxiRoute);
    }

    TEST_F(AirplaneOutput, setTaxiPoint) {
        airplane = new Airplane();
        airplane->setTaxiPoint("point");
        EXPECT_EQ(airplane->getTaxiPoint(), "point");
    }

    TEST_F(AirplaneOutput, setTaxiCrossing) {
        airplane = new Airplane();
        airplane->setTaxiCrossing("crossing");
        EXPECT_EQ(airplane->getTaxiCrossing(), "crossing");
    }

    TEST_F(AirplaneOutput, setIfrAuthorised) {
        airplane = new Airplane();
        airplane->setIFRAuthorized(true);
        EXPECT_TRUE(airplane->isIFRAuthorized());
    }

    TEST_F(AirplaneOutput, setPushback) {
        airplane = new Airplane();
        airplane->setPushback(true);
        EXPECT_TRUE(airplane->isPushback());
    }

    TEST_F(AirplaneOutput, setRequestMessageSend) {
        airplane = new Airplane();
        airplane->setRequestMessageSend(true);
        EXPECT_TRUE(airplane->isRequestMessageSend());
    }

    TEST_F(AirplaneOutput, setMessageMessageSend) {
        airplane = new Airplane();
        airplane->setMessageMessageSend(true);
        EXPECT_TRUE(airplane->isMessageMessageSend());
    }

    TEST_F(AirplaneOutput, setConfirmMessageSend) {
        airplane = new Airplane();
        airplane->setConfirmMessageSend(true);
        EXPECT_TRUE(airplane->isConfirmMessageSend());
    }

    TEST_F(AirplaneOutput, setTaxiRequest) {
        airplane = new Airplane();
        airplane->setTaxiRequest(true);
        EXPECT_TRUE(airplane->isTaxiRequest());
    }

    TEST_F(AirplaneOutput, setEmergencyInAirport) {
        airplane = new Airplane();
        airplane->setEmergencyInAirport(true);
        EXPECT_TRUE(airplane->getEmergencyInAirport());
    }

    TEST_F(AirplaneOutput, setSquawkCode) {
        airplane = new Airplane();
        airplane->setSquawkCode();
        EXPECT_NE(airplane->getSquawkCode(), "");
    }

    TEST_F(AirplaneOutput, getDestination) {
        airplane = new Airplane();
        flightPlan = new FlightPlan;
        airplane->setFlightPlan(flightPlan);
        EXPECT_EQ(airplane->getDestination(), "");
    }

    TEST_F(AirplaneOutput, setCurrentTask) {
        airplane = new Airplane();
        airplane->setCurrentTask("task");
        EXPECT_EQ(airplane->getCurrentTask(), "task");
    }

    TEST_F(AirplaneOutput, setSimulationFinished) {
        airplane = new Airplane();
        airplane->setSimulationFinished(true);
        EXPECT_TRUE(airplane->getSimulationFinished());
    }

    TEST_F(AirplaneOutput, setOnItsWay) {
        airplane = new Airplane();
        airplane->setOnItsWay(true);
        EXPECT_TRUE(airplane->isOnItsWay());
    }

    TEST_F(AirplaneOutput, setAttemptGate) {
        airplane = new Airplane();
        airplane->setAttemptGate(3);
        EXPECT_EQ(airplane->getAttemptGate(), 3);
    }

    class GlobalOutput: public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        GlobalOutput() {


        }

        // virtual void SetUp() will be called before each test is run.  You
        // should define it if you need to initialize the variables.
        // Otherwise, this can be skipped.
        virtual void SetUp() {


        }

        // virtual void TearDown() will be called after each test is run.
        // You should define it if there is cleanup work to do.  Otherwise,
        // you don't have to provide it.
        virtual void TearDown() {
        }

        // Declares the variables your tests want to use.
        string myString;
        int myInt;
    };

    TEST_F(GlobalOutput, setTime) {
        myString = "7";
        setTime(myString);
        EXPECT_EQ(getTime(), myString);
    }

    TEST_F(GlobalOutput, setTimePassed) {
        myInt = 6;
        setTimePassed(myInt);
        EXPECT_EQ(getTimePassed(), myInt);
    }

    TEST_F(GlobalOutput, setStartingTime) {
        myInt = 6;
        setStartingTime(myInt);
        EXPECT_EQ(getStartingTime(), myInt);
    }

    class CommunicationOutput: public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        CommunicationOutput() {


        }

        // virtual void SetUp() will be called before each test is run.  You
        // should define it if you need to initialize the variables.
        // Otherwise, this can be skipped.
        virtual void SetUp() {
            openNewCommunicationLogFile("CommTest.txt");

            runway = new Runway();
            runway->setType("grass");
            runway->setLength(5000);
            runway->setName("11R");

            vector<Runway*> runways;
            runways.push_back(runway);

            airport = new Airport();
            airport->setCallsign("portCallsign");
            airport->setIata("iata");
            airport->setGates(5);
            airport->setName("ANR");
            airport->setRunways(runways);

            flightPlan = new FlightPlan();
            flightPlan->setArrival(10);
            flightPlan->setDeparture(20);
            flightPlan->setInterval(1);
            flightPlan->setDestination("Destination");

            plane = new Airplane();
            plane->setNumber("number");
            plane->setFuel(10000);
            plane->setState("Gate");
            plane->setPassengers(70);
            plane->setType("private");
            plane->setSize("small");
            plane->setHeight(300);
            plane->setCallsign("callsign");
            plane->setEngine("propeller");
            plane->setSquawkCode(1234);
            plane->setFlightPlan(flightPlan);
            plane->setAirport(airport);

        }

        // virtual void TearDown() will be called after each test is run.
        // You should define it if there is cleanup work to do.  Otherwise,
        // you don't have to provide it.
        virtual void TearDown() {
            openNewCommunicationLogFile("NewCommLogFile.txt");
            delete plane;
            delete airport;

        }

        // Declares the variables your tests want to use.
        Airplane* plane;
        Airport* airport;
        Runway* runway;
        FlightPlan* flightPlan;

    };


    TEST_F(CommunicationOutput, CommunicationMessageOutput){

        EXPECT_NO_FATAL_FAILURE(EmergencyAbove3000ftMessage(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(initialCommunicationMessage(plane, airport, "00:01"));
        EXPECT_NO_FATAL_FAILURE(descendTo5000ftMessage(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(descendTo5000ftConfirmation(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(waitBeforeDescendMessage(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(waitBeforeDescendConfirmation(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(descendTo3000ftMessage(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(descendTo3000ftConfirmation(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(finalApproachMessage(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(finalApproachConfirmation(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(afterLandingMessage(plane, airport, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(IFRRequest(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(IFRMessage(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(IFRConfirmation(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(pushbackRequest(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(pushbackMessage(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(pushbackConfirmation(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(readyToTaxiMessage(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(holdingShortAtRunway(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(waitAtRunwayMessage(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(waitAtRunwayConfirmation(plane, "00:01"));
        EXPECT_NO_FATAL_FAILURE(lineUpRunwayMessage(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(lineUpRunwayConfirmation(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(clearedForTakeOffMessage(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(clearedForTakeOffConfirmation(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(toHoldingPointMessage(plane,"CrossingA","A", "00:01"));
        EXPECT_NO_FATAL_FAILURE(toHoldingPointConfirmation(plane,"CrossingA","A", "00:01"));
        EXPECT_NO_FATAL_FAILURE(toRunwayMessage(plane, runway,"A", "00:01"));
        EXPECT_NO_FATAL_FAILURE(toRunwayConfirmation(plane, runway,"A", "00:01"));
        EXPECT_NO_FATAL_FAILURE(toGateMessage(plane, 5, "A", "00:01"));
        EXPECT_NO_FATAL_FAILURE(toGateConfirmation(plane, 5, "A", "00:01"));
        EXPECT_NO_FATAL_FAILURE(clearedToCrossRequest(plane,"CrossingA", "00:01" ));
        EXPECT_NO_FATAL_FAILURE(clearedToCrossMessage(plane,"CrossingA", "00:01" ));
        EXPECT_NO_FATAL_FAILURE(clearedToCrossConfirmation("CrossingA", "00:01" ));
        EXPECT_NO_FATAL_FAILURE(EmergencyAbove3000ftRequest(plane, airport, "00:01"));
        EXPECT_NO_FATAL_FAILURE(EmergencyAbove3000ftMessage(plane, runway, "00:01"));
        EXPECT_NO_FATAL_FAILURE(EmergencyBelow3000ftRequest(plane, airport, "00:01"));
        EXPECT_NO_FATAL_FAILURE(EmergencyBelow3000ftMessage(plane, "00:01"));

        EXPECT_TRUE(FileCompare("CommTest.txt", "CommTestResult.txt"));

    }

}