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

    class AirportHandlerDomain : public ::testing::Test {
    protected:

        AirportHandlerDomain() {

        }

        virtual void SetUp() {
            openNewLogFile("SimulationTests.txt");
            openNewCommunicationLogFile("SimulationCommTests.txt");

            handler = new AirportHandler();
            handler2 = new AirportHandler();
            handler3 = new AirportHandler();
            handler4 = new AirportHandler();

        }

        virtual void TearDown() {
            openNewLogFile("DefaultLog.txt");
            openNewLogFile("DefaultCommLog.txt");

            delete handler;
            delete handler2;
            delete handler3;
            delete handler4;

        }

        AirportHandler* handler;
        AirportHandler* handler2;
        AirportHandler* handler3;
        AirportHandler* handler4;

    };

    TEST_F(AirportHandlerDomain, RunSimulation){

        // No Airports
        handler->addXmlData("XMLTests/TestVolledigeLuchthaven16.xml");
        EXPECT_DEATH(handler->runSimulation(""), "Assertion.*failed");

        cout << "1" << endl;
        // Correcte Luchthaven + airplanes
        handler2->addXmlData("XMLTests/TestVolledigeLuchthaven10.xml");
        EXPECT_NO_FATAL_FAILURE(handler2->runSimulation("ANR"));

        cout << "2" << endl;

        // No runways
        handler3->addXmlData("XMLTests/TestVolledigeLuchthaven2.xml");
        EXPECT_DEATH(handler3->runSimulation("ANR"), "Assertion.*failed");

        cout << "3" << endl;

        // No Airplanes
        handler4->addXmlData("XMLTests/TestVolledigeLuchthaven9.xml");
        EXPECT_DEATH(handler4->runSimulation("ANR"), "Assertion.*failed");

    }


    class RunwayDomain : public ::testing::Test {
    protected:

        RunwayDomain() {

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

    TEST_F(RunwayDomain, defaultConstructor) {
        EXPECT_TRUE(runway->properlyInitialised());
        EXPECT_EQ(runway->getName(), "");
        EXPECT_EQ(runway->isOccupied(), false);
        EXPECT_EQ(runway->getLength(), 0);
        EXPECT_EQ(runway->getHoldingShortOccupied(), false);
        EXPECT_EQ(runway->getWaitingOnRunway(), false);
        EXPECT_TRUE(runway->getAirport() == NULL);
        EXPECT_TRUE(runway->getTaxiRoute() == NULL);
        EXPECT_EQ(runway->getPermissionToCross(), true);
        EXPECT_EQ(runway->getCrossing(), false);
        EXPECT_EQ(runway->getOnItsWay(), false);
    }

    TEST_F(RunwayDomain, nonDefaultConstructor) {
        myString = "name";
        EXPECT_NO_FATAL_FAILURE(runway = new Runway(myString, airport));
        EXPECT_TRUE(runway->properlyInitialised());
        EXPECT_EQ(runway->getName(), "name");
        EXPECT_EQ(runway->isOccupied(), false);
        EXPECT_EQ(runway->getLength(), 0);
        EXPECT_EQ(runway->getHoldingShortOccupied(), false);
        EXPECT_EQ(runway->getWaitingOnRunway(), false);
        EXPECT_EQ(runway->getAirport(), airport);
        EXPECT_TRUE(runway->getTaxiRoute() == NULL);
        EXPECT_EQ(runway->getPermissionToCross(), true);
        EXPECT_EQ(runway->getCrossing(), false);
        EXPECT_EQ(runway->getOnItsWay(), false);
    }

    TEST_F(RunwayDomain, setVar) {
        EXPECT_NO_FATAL_FAILURE(runway->setName( "Rname"));
        EXPECT_DEATH(runway->setType("Rtype"), "Assertion.*failed");
        EXPECT_NO_FATAL_FAILURE(runway->setLength(200));
        EXPECT_EQ(runway->getName(), "Rname");
        EXPECT_NE(runway->getType(), "Rtype");
        EXPECT_EQ(runway->getLength(), 200);
    }

    TEST_F(RunwayDomain, isValid) {
        EXPECT_FALSE(runway->isValid());
        taxiRoute->addTaxiPoint("point");
        runway->setTaxiRoute(taxiRoute);
        myString = "Rname";
        runway->setName(myString);
        myString = "asphalt";
        runway->setType(myString);
        myInt = 200;
        runway->setLength(myInt);
        EXPECT_TRUE(runway->isValid());
    }


    class TaxiRouteDomain : public ::testing::Test {
    protected:

        TaxiRouteDomain() {

        }

        virtual void SetUp() {
            taxiRoute = new TaxiRoute();
        }

        virtual void TearDown() {
            delete taxiRoute;
        }

        TaxiRoute* taxiRoute;
        string myString;
    };

    TEST_F(TaxiRouteDomain, defaultConstructor) {
        EXPECT_TRUE(taxiRoute->properlyInitialised());
    }

    TEST_F(TaxiRouteDomain, isValid) {
        taxiRoute->addTaxiPoint("point");
        EXPECT_TRUE(taxiRoute->isValid());
    }


    class FlightPlanDomain : public ::testing::Test {
    protected:

        FlightPlanDomain() {

        }

        virtual void SetUp() {
            openNewLogFile("AirplaneLog.txt");
            openNewCommunicationLogFile("AirplaneCommLog.txt");
            flightPlan = new FlightPlan();
        }

        virtual void TearDown() {
            delete flightPlan;
        }

        FlightPlan* flightPlan;
        string myString;
        int myInt;
    };

    TEST_F(FlightPlanDomain, defaultConstructor) {
        EXPECT_TRUE(flightPlan->properlyInitialised());
    }

    TEST_F(FlightPlanDomain, isValid){
        myString = "destination";
        flightPlan->setInterval(0);
        flightPlan->setDestination(myString);
        EXPECT_FALSE(flightPlan->isValid());
        myInt = 45;
        flightPlan->setInterval(myInt);
        EXPECT_TRUE(flightPlan->isValid());
    }


    class AirportDomain : public ::testing::Test {
    protected:

        AirportDomain() {

        }

        virtual void SetUp() {
            runway = new Runway();
            airport = new Airport();
            taxiRoute = new TaxiRoute();
        }

        virtual void TearDown() {
            delete airport;
            delete taxiRoute;
        }

        Airport *airport;
        Runway *runway;
        TaxiRoute* taxiRoute;
        vector<bool> gatesOccupied;
        vector<Runway*> runways;
        string myString;
        int myInt;
    };

    TEST_F(AirportDomain, defaultConstructor) {
        EXPECT_TRUE(airport->properlyInitialised());
        EXPECT_EQ(airport->getName(), "");
        EXPECT_EQ(airport->getIata(), "");
        EXPECT_EQ(airport->getCallsign(), "");
        EXPECT_EQ(airport->getGates(), 0);
        EXPECT_EQ(airport->getGatesOccupied(), gatesOccupied);
        EXPECT_TRUE(airport->getWait5000() == NULL);
        EXPECT_TRUE(airport->getWait3000() == NULL);
        EXPECT_EQ(airport->getRunways(), runways);
    }

    TEST_F(AirportDomain, nonDefaultConstructor) {
        EXPECT_NO_FATAL_FAILURE(airport = new Airport("name","iata", "callsign", 5));
        EXPECT_TRUE(airport->properlyInitialised());
        EXPECT_EQ(airport->getName(), "name");
        EXPECT_EQ(airport->getIata(), "iata");
        EXPECT_EQ(airport->getCallsign(), "callsign");
        EXPECT_EQ(airport->getGates(), 5);
        EXPECT_EQ(airport->getGatesOccupied(), gatesOccupied);
        EXPECT_TRUE(airport->getWait5000() == NULL);
        EXPECT_TRUE(airport->getWait3000() == NULL);
        EXPECT_EQ(airport->getRunways(), runways);
    }

    TEST_F(AirportDomain, getRunway) {
        runway->setName("name");
        runway->setType("asphalt");
        runway->setLength(200);
        airport->addRunway(runway);
        EXPECT_EQ(airport->getRunway("name"), runway);
    }

    TEST_F(AirportDomain, runwayExists) {
        EXPECT_FALSE(airport->runwayExists("name"));
        runway->setName("name");
        runway->setType("asphalt");
        runway->setLength(200);
        airport->addRunway(runway);
        EXPECT_TRUE(airport->getRunway("name"));
    }

    TEST_F(AirportDomain, validGateIndex) {
        airport->setGates(5);
        EXPECT_TRUE(airport->validGateIndex(-1));
        EXPECT_FALSE(airport->validGateIndex(5));
        EXPECT_TRUE(airport->validGateIndex(0));
        EXPECT_TRUE(airport->validGateIndex(4));
    }

    TEST_F(AirportDomain, isValid) {
        airport->setName("name");
        EXPECT_FALSE(airport->isValid());
        airport->setIata("iata");
        EXPECT_FALSE(airport->isValid());
        airport->setCallsign("callsign");
        EXPECT_FALSE(airport->isValid());
        airport->setGates(5);
        EXPECT_TRUE(airport->isValid());
    }


    class AirplaneDomain : public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        AirplaneDomain() {


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
        Airplane *airplane3;
        Airplane *airplane4;
        Airplane *airplane5;
        Airplane *airplane6;
        Airplane *airplane7;
        Airplane *airplane8;
        FlightPlan* flightPlan;
        Runway *runway;
        Runway *runway1;
        AirportHandler *D;
    };

    TEST_F(AirplaneDomain, defaultConstructor) {
        airplane = new Airplane();
        EXPECT_TRUE(airplane->properlyInitialised());
        EXPECT_EQ(airplane->getNumber(), "");
        EXPECT_EQ(airplane->getCallsign(), "");
        EXPECT_EQ(airplane->getModel(), "");
        EXPECT_EQ(airplane->getState(), "");
        EXPECT_EQ(airplane->getType(), "");
        EXPECT_EQ(airplane->getEngine(), "");
        EXPECT_EQ(airplane->getSize(), "");
        EXPECT_EQ(airplane->getSquawkCode(), "");
        EXPECT_TRUE(airplane->getAirport() == NULL);
        EXPECT_TRUE(airplane->getRunway() == NULL);
        EXPECT_TRUE(airplane->getFlightPlan() == NULL);
        EXPECT_TRUE(airplane->getTaxiRoute() == NULL);
        EXPECT_TRUE(airplane->getAttemptRunway() == NULL);
        EXPECT_EQ(airplane->getGate(), -1);
        EXPECT_EQ(airplane->getFuel(), 0);
        EXPECT_EQ(airplane->getPassengers(), 0);
        EXPECT_EQ(airplane->getPassengerCapacity(), 0);
        EXPECT_EQ(airplane->getHeight(), 0);
        EXPECT_EQ(airplane->getOperationTime(), 0);
        EXPECT_EQ(airplane->getAttemptGate(), -1);
        EXPECT_EQ(airplane->getCurrentTask(), "");
        EXPECT_EQ(airplane->getTaxiCrossing(), "");
        EXPECT_EQ(airplane->getTaxiPoint(), "");
        EXPECT_FALSE(airplane->getTechnicalChecked());
        EXPECT_FALSE(airplane->isIFRAuthorized());
        EXPECT_FALSE(airplane->isRequestMessageSend());
        EXPECT_FALSE(airplane->isConfirmMessageSend());
        EXPECT_FALSE(airplane->isConfirmMessageSend());
        EXPECT_FALSE(airplane->isPushback());
        EXPECT_FALSE(airplane->isTaxiRequest());
        EXPECT_FALSE(airplane->getEmergencyInAirport());
        EXPECT_FALSE(airplane->isOnItsWay());
        EXPECT_FALSE(airplane->getSimulationFinished());
        EXPECT_FALSE(airplane->isCrossed());
        EXPECT_FALSE(airplane->isAlreadyLinedUp());
        EXPECT_FALSE(airplane->isWaitAtRunway());
        EXPECT_FALSE(airplane->isWaitOnRunway());
        EXPECT_FALSE(airplane->isPermissionToTakeOff());
    }

    TEST_F(AirplaneDomain, isReadyForDeparture) {
        airplane = new Airplane();
        airplane->setPassengers(50);
        airplane->setPassengerCapacity(150);
        airplane->setFuel(10);
        airplane->setFuelCapacity(100);
        EXPECT_FALSE(airplane->isReadyForDeparture());
        airplane->setPassengerCapacity(50);
        EXPECT_FALSE(airplane->isReadyForDeparture());
        airplane->setPassengerCapacity(150);
        EXPECT_FALSE(airplane->isReadyForDeparture());
        airplane->setFuelCapacity(10);
        EXPECT_FALSE(airplane->isReadyForDeparture());
        airplane->setPassengerCapacity(50);
        EXPECT_TRUE(airplane->isReadyForDeparture());
    }

    TEST_F(AirplaneDomain, readyForTakeOff) {
        airplane = new Airplane();
        airplane->setPassengers(50);
        airplane->setPassengerCapacity(50);
        airplane->setFuel(10);
        airplane->setFuelCapacity(10);
        EXPECT_FALSE(airplane->readyForTakeOff());
        airport = new Airport();
        airplane->setAirport(airport);
        EXPECT_FALSE(airplane->readyForTakeOff());
        runway = new Runway();
        airplane->setRunway(runway);
        EXPECT_FALSE(airplane->readyForTakeOff());
        airplane->setState("Waiting for departure");
        EXPECT_TRUE(airplane->readyForTakeOff());
    }

    TEST_F(AirplaneDomain, atAirport) {
        airplane = new Airplane();
        EXPECT_FALSE(airplane->atAirport());
        airport = new Airport;
        airplane->setAirport(airport);
        EXPECT_TRUE(airplane->atAirport());
    }

    TEST_F(AirplaneDomain, atGate) {
        airplane = new Airplane();
        EXPECT_FALSE(airplane->atGate());
        airport = new Airport;
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);
        airplane->setState("Waiting for departure");
        EXPECT_TRUE(airplane->atGate());
    }

    TEST_F(AirplaneDomain, validSize) {
        airplane = new Airplane();
        EXPECT_FALSE(airplane->validSize("wrongsize"));
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_TRUE(airplane->validSize("medium"));
        EXPECT_TRUE(airplane->validSize("large"));

        airplane->setType("private");
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_TRUE(airplane->validSize("medium"));
        EXPECT_FALSE(airplane->validSize("large"));

        airplane->setType("airline");
        EXPECT_FALSE(airplane->validSize("small"));
        EXPECT_TRUE(airplane->validSize("medium"));
        EXPECT_TRUE(airplane->validSize("large"));

        airplane->setType("military");
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_FALSE(airplane->validSize("medium"));
        EXPECT_TRUE(airplane->validSize("large"));

        airplane->setType("emergency");
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_FALSE(airplane->validSize("medium"));
        EXPECT_FALSE(airplane->validSize("large"));

        airplane = new Airplane();
        airplane->setType("private");
        airplane->setEngine("jet");
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_TRUE(airplane->validSize("medium"));
        EXPECT_FALSE(airplane->validSize("large"));

        airplane1 = new Airplane();
        airplane1->setType("private");
        airplane1->setEngine("propeller");
        EXPECT_TRUE(airplane1->validSize("small"));
        EXPECT_FALSE(airplane1->validSize("medium"));
        EXPECT_FALSE(airplane1->validSize("large"));

        airplane2 = new Airplane();
        airplane2->setType("airline");
        airplane2->setEngine("jet");
        EXPECT_FALSE(airplane2->validSize("small"));
        EXPECT_TRUE(airplane2->validSize("medium"));
        EXPECT_TRUE(airplane2->validSize("large"));

        airplane3 = new Airplane();
        airplane3->setType("airline");
        airplane3->setEngine("propeller");
        EXPECT_FALSE(airplane3->validSize("small"));
        EXPECT_TRUE(airplane3->validSize("medium"));
        EXPECT_FALSE(airplane3->validSize("large"));

        airplane4 = new Airplane();
        airplane4->setType("military");
        airplane4->setEngine("jet");
        EXPECT_TRUE(airplane4->validSize("small"));
        EXPECT_FALSE(airplane4->validSize("medium"));
        EXPECT_FALSE(airplane4->validSize("large"));

        airplane5 = new Airplane();
        airplane5->setType("military");
        airplane5->setEngine("propeller");
        EXPECT_FALSE(airplane5->validSize("small"));
        EXPECT_FALSE(airplane5->validSize("medium"));
        EXPECT_TRUE(airplane5->validSize("large"));

        airplane6 = new Airplane();
        airplane6->setType("emergency");
        airplane6->setEngine("propeller");
        EXPECT_TRUE(airplane6->validSize("small"));
        EXPECT_FALSE(airplane6->validSize("medium"));
        EXPECT_FALSE(airplane6->validSize("large"));
    }

    TEST_F(AirplaneDomain, validEngineType) {
        airplane = new Airplane();
        EXPECT_FALSE(airplane->validEngineType("wrongengine"));
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane->setType("private");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane->setType("airline");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane->setType("military");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane->setType("emergency");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_FALSE(airplane->validEngineType("jet"));

        airplane = new Airplane();
        airplane->setType("private");
        airplane->setSize("small");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane1 = new Airplane();
        airplane1->setType("private");
        airplane1->setSize("medium");
        EXPECT_FALSE(airplane1->validEngineType("propeller"));
        EXPECT_TRUE(airplane1->validEngineType("jet"));

        airplane2 = new Airplane();
        airplane2->setType("airline");
        airplane2->setSize("medium");
        EXPECT_TRUE(airplane2->validEngineType("propeller"));
        EXPECT_TRUE(airplane2->validEngineType("jet"));

        airplane3 = new Airplane();
        airplane3->setType("airline");
        airplane3->setSize("large");
        EXPECT_FALSE(airplane3->validEngineType("propeller"));
        EXPECT_TRUE(airplane3->validEngineType("jet"));

        airplane4 = new Airplane();
        airplane4->setType("military");
        airplane4->setSize("small");
        EXPECT_FALSE(airplane4->validEngineType("propeller"));
        EXPECT_TRUE(airplane4->validEngineType("jet"));

        airplane5 = new Airplane();
        airplane5->setType("military");
        airplane5->setSize("large");
        EXPECT_TRUE(airplane5->validEngineType("propeller"));
        EXPECT_FALSE(airplane5->validEngineType("jet"));

        airplane6 = new Airplane();
        airplane6->setType("emergency");
        airplane6->setSize("small");
        EXPECT_TRUE(airplane6->validEngineType("propeller"));
        EXPECT_FALSE(airplane6->validEngineType("jet"));
    }

    TEST_F(AirplaneDomain, validPlaneType) {
        airplane = new Airplane();
        EXPECT_FALSE(airplane->validPlaneType("wrongtype"));
        EXPECT_TRUE(airplane->validPlaneType("private"));
        EXPECT_TRUE(airplane->validPlaneType("airline"));
        EXPECT_TRUE(airplane->validPlaneType("military"));
        EXPECT_TRUE(airplane->validPlaneType("emergency"));

        airplane->setType("military");
        airplane->setSize("small");
        airplane->setEngine("jet");
        EXPECT_FALSE(airplane->validPlaneType("emergency"));
    }

    TEST_F(AirplaneDomain, validGate){
        airplane = new Airplane();
        EXPECT_TRUE(airplane->validGate(-1));
        EXPECT_DEATH(airplane->validGate(5), "");
        airport = new Airport();
        airplane->setAirport(airport);
        airport->setGates(5);
        EXPECT_TRUE(airplane->validGate(3));
        airport->setGateOccupied(3, true);
        EXPECT_FALSE(airplane->validGate(3));
        airplane->setAttemptGate(3);
        EXPECT_TRUE(airplane->validGate(3));
    }

    TEST_F(AirplaneDomain, validRunway){
        airplane = new Airplane();
        airplane->setSize("medium");
        airplane->setEngine("propeller");
        runway = new Runway();
        runway->setLength(5000);
        runway->setType("asphalt");
        EXPECT_TRUE(airplane->validRunway(runway));
        runway->setLength(200);
        EXPECT_FALSE(airplane->validRunway(runway));
        runway->setLength(5000);
        runway->setType("grass");
        EXPECT_FALSE(airplane->validRunway(runway));
    }

    TEST_F(AirplaneDomain, validLandingSpot){
        airplane = new Airplane();
        airplane->setSize("medium");
        airplane->setEngine("propeller");
        runway = new Runway();
        runway->setLength(5000);
        runway->setType("asphalt");
        runway->setName("name");
        airport = new Airport();
        airport->addRunway(runway);
        EXPECT_TRUE(airplane->validLandingSpot(airport, runway));
        runway->setOccupied(true);
        EXPECT_FALSE(airplane->validLandingSpot(airport, runway));
        runway->setOccupied(false);
        runway->setLength(200);
        EXPECT_FALSE(airplane->validLandingSpot(airport, runway));
        runway->setLength(5000);
        runway->setType("grass");
        EXPECT_FALSE(airplane->validLandingSpot(airport, runway));
    }

    TEST_F(AirplaneDomain, permissionToDescend){
        airplane = new Airplane();
        airplane->setHeight(10000);
        airplane1 = new Airplane;
        runway = new Runway();
        airport = new Airport();
        runway->setName("naam");
        runway->setType("asphalt");
        runway->setLength(3000);
        airport->addRunway(runway);
        airport->setWait5000(airplane1);
        EXPECT_FALSE(airplane->permissionToDescend(airplane->getHeight(), airport, runway));
        airport->setWait5000(NULL);
        airport->setWait3000(airplane1);
        EXPECT_TRUE(airplane->permissionToDescend(airplane->getHeight(), airport, runway));
        airplane->setHeight(5000);
        EXPECT_FALSE(airplane->permissionToDescend(airplane->getHeight(), airport, runway));
        airplane->setHeight(3000);
        runway->setOccupied(true);
        EXPECT_FALSE(airplane->permissionToDescend(airplane->getHeight(), airport, runway));
        runway->setOccupied(false);
        EXPECT_TRUE(airplane->permissionToDescend(airplane->getHeight(), airport, runway));
    }

    TEST_F(AirplaneDomain, isValid) {
        airplane = new Airplane();
        EXPECT_FALSE(airplane->isValid());
        airplane->setSize("small");
        EXPECT_FALSE(airplane->isValid());
        airplane->setFuel(200);
        EXPECT_FALSE(airplane->isValid());
        airplane->setType("private");
        EXPECT_FALSE(airplane->isValid());
        airplane->setModel("model");
        EXPECT_FALSE(airplane->isValid());
        airplane->setNumber("52");
        EXPECT_FALSE(airplane->isValid());
        airplane->setCallsign("callsign");
        EXPECT_FALSE(airplane->isValid());
        airplane->setState("tired");
        EXPECT_FALSE(airplane->isValid());
        airplane->setEngine("propeller");
        EXPECT_TRUE(airplane->isValid());
    }

    TEST_F(AirplaneDomain, pushBack) {
        runway = new Runway();
        runway->setName("naam");
        runway->setType("asphalt");
        runway->setLength(3000);

        airport = new Airport();
        airport->addRunway(runway);

        flightPlan = new FlightPlan();

        airplane = new Airplane();
        airplane->setEngine("propeller");
        airplane->setSize("large");
        airplane->setAirport(airport);
        airplane->setCurrentTask("IFR");
        airplane->setFlightPlan(flightPlan);

        runway->setOccupied(true);
        EXPECT_DEATH(airplane->pushBack(), "Valid runway");
        runway->setOccupied(false);
        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_EQ(airplane->getState(), "pushback");
        EXPECT_TRUE(airplane->isRequestMessageSend());
        EXPECT_FALSE(airplane->isMessageMessageSend());
        EXPECT_FALSE(airplane->isConfirmMessageSend());

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_TRUE(airplane->isRequestMessageSend());
        EXPECT_TRUE(airplane->isMessageMessageSend());
        EXPECT_FALSE(airplane->isConfirmMessageSend());

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_EQ(airplane->getCurrentTask(), "pushback");
        EXPECT_FALSE(airplane->isRequestMessageSend());
        EXPECT_FALSE(airplane->isMessageMessageSend());
        EXPECT_FALSE(airplane->isConfirmMessageSend());

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_TRUE(airplane->isRequestMessageSend());
        EXPECT_FALSE(airplane->isMessageMessageSend());
        EXPECT_FALSE(airplane->isConfirmMessageSend());

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_TRUE(airplane->isRequestMessageSend());
        EXPECT_TRUE(airplane->isMessageMessageSend());
        EXPECT_FALSE(airplane->isConfirmMessageSend());

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_EQ(airplane->getCurrentTask(), "request taxi");
        EXPECT_FALSE(airplane->isRequestMessageSend());
        EXPECT_FALSE(airplane->isMessageMessageSend());
        EXPECT_FALSE(airplane->isConfirmMessageSend());
        EXPECT_TRUE(airplane->isPushback());

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_EQ(airplane->getCurrentTask(), "going to runway");
        EXPECT_FALSE(airplane->isPushback());
    }

    TEST_F(AirplaneDomain, exitPlane) {
        airport = new Airport();
        airport->setGates(5);

        airplane = new Airplane();
        airplane->setAirport(airport);
        airplane->setGate(3);
        airplane->setEngine("propeller");
        airplane->setSize("large");
        airplane->setAirport(airport);
        airplane->setCurrentTask("IFR");
        airplane->setFlightPlan(flightPlan);
        airplane->setPassengerCapacity(100);
        airplane->setPassengers(0);
        airplane->setEmergencyInAirport(true);
        airplane->setCurrentTask("exit passengers");
        airplane->exitPlane();
        EXPECT_EQ(airplane->getCurrentTask(), "technical check");
        EXPECT_EQ(airplane->getState(), "emergency check");
        airplane->setCurrentTask("exit passengers");
        airplane->setEmergencyInAirport(false);
        airplane->exitPlane();
        EXPECT_EQ(airplane->getCurrentTask(), "technical check");
        EXPECT_EQ(airplane->getState(), "technical check");
        airplane->setCurrentTask("exit passengers");
        airplane->setPassengers(100);
        airplane->exitPlane();
        EXPECT_TRUE(airplane->getOperationTime() > 0);
        EXPECT_TRUE(airplane->getPassengers() < 100);

    }

    TEST_F(AirplaneDomain, enterPlane) {
        airport = new Airport();
        airport->setGates(5);

        airplane = new Airplane();
        airplane->setAirport(airport);
        airplane->setGate(3);
        airplane->setEngine("propeller");
        airplane->setSize("large");
        airplane->setPassengerCapacity(100);
        airplane->setPassengers(100);
        airplane->setCurrentTask("board passengers");
        airplane->enterPlane();
        EXPECT_EQ(airplane->getCurrentTask(), "IFR");
        EXPECT_EQ(airplane->getState(), "pushback");
        airplane->setCurrentTask("board passengers");
        airplane->setPassengers(50);
        airplane->enterPlane();
        EXPECT_TRUE(airplane->getOperationTime() > 0);
        EXPECT_TRUE(airplane->getPassengers() > 50);
    }

    TEST_F(AirplaneDomain, technicalCheck) {
        airplane = new Airplane();
        airplane->setCurrentTask("technical check");
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);

        airplane->setFuelCapacity(200000);
        airplane->setFuel(200000);


        airplane->technicalCheck();
        EXPECT_TRUE(airplane->getTechnicalChecked());

        airplane->setEmergencyInAirport(true);
        airplane->technicalCheck();
        EXPECT_EQ(airplane->getCurrentTask(), "taxi to gate");

        airplane->setCurrentTask("technical check");
        airplane->setFuelCapacity(200000);
        airplane->setFuel(100000);

        airplane->setEmergencyInAirport(true);
        airplane->technicalCheck();
        EXPECT_EQ(airplane->getCurrentTask(), "refueling");
        EXPECT_EQ(airplane->getState(), "emergency refuel");
        EXPECT_TRUE(airplane->getOperationTime() > 0);

        airplane->setCurrentTask("technical check");
        airplane->setFuelCapacity(200000);
        airplane->setFuel(200000);

        airplane->setEmergencyInAirport(false);
        airplane->technicalCheck();
        EXPECT_EQ(airplane->getCurrentTask(), "board passengers");
        EXPECT_EQ(airplane->getState(), "board passengers");

        airplane->setCurrentTask("technical check");
        airplane->setFuelCapacity(200000);
        airplane->setFuel(100000);

        airplane->setEmergencyInAirport(false);
        airplane->technicalCheck();
        EXPECT_EQ(airplane->getCurrentTask(), "refueling");
        EXPECT_EQ(airplane->getState(), "refuel");
        EXPECT_TRUE(airplane->getOperationTime() > 0);
    }

    TEST_F(AirplaneDomain, refuel) {
        airplane = new Airplane();
        airplane->setCurrentTask("refueling");
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);
        flightPlan = new FlightPlan();
        airplane->setFlightPlan(flightPlan);
        airplane->setEmergencyInAirport(true);
        airplane->refuel();
        EXPECT_EQ(airplane->getCurrentTask(), "taxi to gate");
        airplane->setEmergencyInAirport(false);
        airplane->setCurrentTask("refueling");
        flightPlan->setDeparture(300);
        airplane->refuel();
        EXPECT_EQ(airplane->getCurrentTask(), "idle");
        flightPlan->setDeparture(0);
        airplane->setCurrentTask("refueling");
        airplane->refuel();
        EXPECT_EQ(airplane->getCurrentTask(), "board passengers");
    }

    TEST_F(AirplaneDomain, descend){
        airplane = new Airplane();
        airplane->setEngine("jet");
        airplane->setHeight(2000);
        airport = new Airport();
        airplane->descend(airport);
        EXPECT_EQ(airplane->getHeight(), 1000);
        airplane->setEngine("propeller");
        airplane->descend(airport);
        EXPECT_EQ(airplane->getHeight(), 500);
    }

    TEST_F(AirplaneDomain, ascend){
        airplane = new Airplane();
        airplane->setEngine("propeller");
        airplane->setHeight(2500);
        airport = new Airport();
        airplane->ascend(airport);
        EXPECT_EQ(airplane->getHeight(), 3000);
        airplane->setEngine("jet");
        airplane->ascend(airport);
        EXPECT_EQ(airplane->getHeight(), 4000);
        airplane->ascend(airport);
        EXPECT_EQ(airplane->getCurrentTask(), "finished");
    }

    TEST_F(AirplaneDomain, notFinished) {
    airplane = new Airplane();
    EXPECT_TRUE(airplane->notFinished());
    airplane->setCurrentTask("finished");
    EXPECT_FALSE(airplane->notFinished());
    }
}
