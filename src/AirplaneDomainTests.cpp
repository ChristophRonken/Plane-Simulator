//
// Created by oliviervh on 19.06.18.
//


#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "gtest/gtest.h"

#include "Airplane.h"
#include "Airport.h"
#include "AirportHandler.h"
#include "MessageSystem.h"
#include "Runway.h"
namespace {
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
            openNewCommunicationLogFile("AirplaneDomain.txt");

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
        Runway *runway;
        Runway *runway1;
        FlightPlan *flightPlan;
        TaxiRoute *taxiRoute;
        AirportHandler *D;
    };

    TEST_F(AirplaneDomain, setEngine1) {
        airplane = new Airplane();
        EXPECT_DEATH(airplane->setEngine(""), "Assertion.*failed");
        EXPECT_DEATH(airplane->setEngine("falsetype"), "Assertion.*failed");
        EXPECT_NO_FATAL_FAILURE(airplane->setEngine("propeller"));
        EXPECT_NO_FATAL_FAILURE(airplane->setEngine("jet"));
    }

    TEST_F(AirplaneDomain, setSize1) {
        airplane = new Airplane();
        EXPECT_DEATH(airplane->setSize(""), "Assertion.*failed");
        EXPECT_DEATH(airplane->setSize("falsetype"), "Assertion.*failed");
        EXPECT_NO_FATAL_FAILURE(airplane->setSize("small"));
        EXPECT_NO_FATAL_FAILURE(airplane->setSize("medium"));
        EXPECT_NO_FATAL_FAILURE(airplane->setSize("large"));
    }

    TEST_F(AirplaneDomain, setGate1) {
        airplane = new Airplane();
        airport = new Airport();
        EXPECT_NO_FATAL_FAILURE(airplane->setGate(-1));
        EXPECT_DEATH(airplane->setGate(6), "at Airport");
        airplane->setAirport(airport);
        airport->setGates(5);
        EXPECT_NO_FATAL_FAILURE(airplane->setGate(-1));
        EXPECT_NO_FATAL_FAILURE(airplane->setGate(3));
        EXPECT_DEATH(airplane->setGate(6), "validGate");
    }

    TEST_F(AirplaneDomain, getDestination1) {
        airplane = new Airplane();
        flightPlan = new FlightPlan();
        EXPECT_DEATH(airplane->getDestination(), "has a flightPlan");
        airplane->setFlightPlan(flightPlan);
        EXPECT_NO_FATAL_FAILURE(airplane->getDestination());
    }

    TEST_F(AirplaneDomain, pushBack1) {
        airplane = new Airplane();
        airplane->setEngine("propeller");
        airplane->setSize("large");

        runway = new Runway();
        runway->setLength(200);
        runway->setName("naam");
        runway->setType("asphalt");

        airport = new Airport();
        airport->addRunway(runway);

        airplane->setCurrentTask("wrong state");
        EXPECT_DEATH(airplane->pushBack(), "correct state");
        airplane->setCurrentTask("IFR");
        EXPECT_DEATH(airplane->pushBack(), "At airport");
        airplane->setCurrentTask("pushback");
        EXPECT_DEATH(airplane->pushBack(), "At airport");
        airplane->setCurrentTask("request taxi");
        EXPECT_DEATH(airplane->pushBack(), "At airport");
        airplane->setAirport(airport);
        EXPECT_DEATH(airplane->pushBack(), "Valid runway");
        runway->setLength(3000);
        EXPECT_DEATH(airplane->pushBack(), "flightplan assigned");
        flightPlan = new FlightPlan();
        airplane->setFlightPlan(flightPlan);
        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());

    }

    TEST_F(AirplaneDomain, exitPlane1) {
        airplane = new Airplane();
        airplane->setCurrentTask("wrong task");
        EXPECT_DEATH(airplane->exitPlane();, "Assertion.*failed");
        airplane->setCurrentTask("exit passengers");
        EXPECT_DEATH(airplane->exitPlane();, "at gate");
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);
        EXPECT_NO_FATAL_FAILURE(airplane->exitPlane(););
    }

    TEST_F(AirplaneDomain, enterPlane1) {
        airplane = new Airplane();
        airplane->setCurrentTask("wrong task");
        EXPECT_DEATH(airplane->enterPlane();, "correct state");
        airplane->setCurrentTask("board passengers");
        EXPECT_DEATH(airplane->enterPlane();, "at gate");
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);
        EXPECT_NO_FATAL_FAILURE(airplane->enterPlane(););
    }

    TEST_F(AirplaneDomain, technicalCheck1) {
        airplane = new Airplane();
        airplane->setCurrentTask("wrong task");
        EXPECT_DEATH(airplane->technicalCheck();, "correct state");
        airplane->setCurrentTask("technical check");
        EXPECT_DEATH(airplane->technicalCheck();, "at gate");
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);
        EXPECT_NO_FATAL_FAILURE(airplane->technicalCheck(););
    }

    TEST_F(AirplaneDomain, refuel1) {
        airplane = new Airplane();
        airplane->setCurrentTask("wrong task");
        EXPECT_DEATH(airplane->refuel();, "correct state");
        airplane->setCurrentTask("refueling");
        EXPECT_DEATH(airplane->refuel();, "at gate");
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);
        EXPECT_DEATH(airplane->refuel();, "flightplan assigned");
        flightPlan = new FlightPlan();
        airplane->setFlightPlan(flightPlan);
        EXPECT_NO_FATAL_FAILURE(airplane->refuel());
    }

    TEST_F(AirplaneDomain, taxiToRunway1) {
        runway = new Runway();
        runway->setLength(5000);
        runway->setType("asphalt");
        runway->setName("name");

        runway1 = new Runway();
        runway1->setLength(5000);
        runway1->setType("asphalt");
        runway1->setName("name1");

        airport = new Airport();
        airport->addRunway(runway);
        airport->addRunway(runway1);
        airport->setGates(7);

        airplane = new Airplane();
        airplane->setAirport(airport);

        airplane->setGate(5);

        taxiRoute = new TaxiRoute();
        taxiRoute->addTaxiPoint("point");
        taxiRoute->addTaxiCrossing("name");
        taxiRoute->addTaxiCrossing("name1");

        EXPECT_DEATH(airplane->taxiToRunway(), "correct state");
        airplane->setCurrentTask("going to runway");
        EXPECT_DEATH(airplane->taxiToRunway();, "destination runway was set");
        airplane->setAttemptRunway(runway1);
        EXPECT_DEATH(airplane->taxiToRunway();, "");
        runway1->setTaxiRoute(taxiRoute);
        EXPECT_NO_FATAL_FAILURE(airplane->taxiToRunway());

    }

    TEST_F(AirplaneDomain, takeOff1) {
        runway = new Runway();
        runway->setLength(5000);
        runway->setType("asphalt");
        runway->setName("name");

        runway1 = new Runway();
        runway1->setLength(5000);
        runway1->setType("asphalt");
        runway1->setName("name1");

        airport = new Airport();
        airport->addRunway(runway);
        airport->addRunway(runway1);
        airport->setGates(7);

        airplane = new Airplane();
        airplane->setAirport(airport);
        airplane->setCurrentTask("wrong task");

        flightPlan = new FlightPlan();
        airplane->setRunway(runway1);
        EXPECT_DEATH(airplane->takeOff();, "");
        airplane->setHeight(200);
        airplane->setCurrentTask("at holding point");
        EXPECT_DEATH(airplane->takeOff();, "");
        airplane->setCurrentTask("taking off");
        airplane->setState(holdingpointCMS);
        EXPECT_DEATH(airplane->takeOff();, "");
        airplane->setHeight(0);
        EXPECT_NO_FATAL_FAILURE(airplane->takeOff());
    }

    TEST_F(AirplaneDomain, taxiToGate1) {
        runway = new Runway();
        runway->setLength(5000);
        runway->setType("asphalt");
        runway->setName("name");

        runway1 = new Runway();
        runway1->setLength(5000);
        runway1->setType("asphalt");
        runway1->setName("name1");

        airport = new Airport();
        airport->addRunway(runway);
        airport->addRunway(runway1);
        airport->setGates(7);

        airplane = new Airplane();
        airplane->setAirport(airport);
        airplane->setRunway(runway1);

        taxiRoute = new TaxiRoute();
        taxiRoute->addTaxiPoint("point");
        taxiRoute->addTaxiPoint("point1");
        taxiRoute->addTaxiCrossing("name");

        runway1->setTaxiRoute(taxiRoute);

        EXPECT_DEATH(airplane->taxiToGate(3), "correct task");
        airplane->setCurrentTask("going to gate");
        EXPECT_DEATH(airplane->taxiToGate(9);, "valid gate number");
        EXPECT_NO_FATAL_FAILURE(airplane->taxiToGate(5));
    }

    TEST_F(AirplaneDomain, land1) {
        runway1 = new Runway();
        runway1->setLength(10000);
        runway1->setType("asphalt");
        runway1->setName("name1");

        airport = new Airport();
        airport->addRunway(runway1);

        airplane = new Airplane();
        airplane->setCallsign("callsign");
        airplane->setHeight(3000);
        airplane->setSize("medium");
        airplane->setEngine("jet");
        airplane->setCurrentTask("wrong task");
        airplane->setState(incoming);
        EXPECT_DEATH(airplane->land(airport);, "correct task");
        airplane->setCurrentTask("try to land");
        EXPECT_NO_FATAL_FAILURE(airplane->land(airport));
        EXPECT_NO_FATAL_FAILURE(airplane->land(airport));
        airplane->setCurrentTask("descending to 5000ft.");
        EXPECT_NO_FATAL_FAILURE(airplane->land(airport));
        airplane->setCurrentTask("descending to 3000ft.");
        EXPECT_NO_FATAL_FAILURE(airplane->land(airport));
        airplane->setCurrentTask("descending to 0ft.");
        EXPECT_NO_FATAL_FAILURE(airplane->land(airport));

    }

    TEST_F(AirplaneDomain, defaultConstructor) {
        airplane = new Airplane();
        EXPECT_TRUE(airplane->properlyInitialised());
        EXPECT_EQ(airplane->getNumber(), "");
        EXPECT_EQ(airplane->getCallsign(), "");
        EXPECT_EQ(airplane->getModel(), "");
        EXPECT_EQ(airplane->getState(), init);
        EXPECT_EQ(airplane->getType(), "none");
        EXPECT_EQ(airplane->getEngine(), "");
        EXPECT_EQ(airplane->getSize(), "");
        EXPECT_EQ(airplane->getSquawkCode(), 0);
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
        EXPECT_FALSE(airplane->getSimulationFinished());
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
        airplane->setState(holdingpointCMS);
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
        airplane->setState(onRunway);
        EXPECT_TRUE(airplane->atGate());
    }

    TEST_F(AirplaneDomain, validSize) {
        airplane = new AirplanePrivate();
        EXPECT_FALSE(airplane->validSize("wrongsize"));
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_TRUE(airplane->validSize("medium"));
        EXPECT_FALSE(airplane->validSize("large"));
        delete airplane;

        airplane = new AirplanePrivate();
//airplane->setType("private");
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_TRUE(airplane->validSize("medium"));
        EXPECT_FALSE(airplane->validSize("large"));
        delete airplane;

        airplane = new AirplaneAirline();
//airplane->setType("airline");
        EXPECT_FALSE(airplane->validSize("small"));
        EXPECT_TRUE(airplane->validSize("medium"));
        EXPECT_TRUE(airplane->validSize("large"));
        delete airplane;

        airplane = new AirplaneMilitairy();
//airplane->setType("military");
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_FALSE(airplane->validSize("medium"));
        EXPECT_TRUE(airplane->validSize("large"));
        delete airplane;

        airplane = new AirplaneEmergency();
//airplane->setType("emergency");
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_FALSE(airplane->validSize("medium"));
        EXPECT_FALSE(airplane->validSize("large"));
        delete airplane;

        airplane = new AirplanePrivate();
//airplane->setType("private");
        airplane->setEngine("jet");
        EXPECT_TRUE(airplane->validSize("small"));
        EXPECT_TRUE(airplane->validSize("medium"));
        EXPECT_FALSE(airplane->validSize("large"));
        delete airplane;

        airplane1 = new AirplanePrivate();
//airplane1->setType("private");
        airplane1->setEngine("propeller");
        EXPECT_TRUE(airplane1->validSize("small"));
        EXPECT_FALSE(airplane1->validSize("medium"));
        EXPECT_FALSE(airplane1->validSize("large"));
        delete airplane;

        airplane2 = new AirplaneAirline();
//airplane2->setType("airline");
        airplane2->setEngine("jet");
        EXPECT_FALSE(airplane2->validSize("small"));
        EXPECT_TRUE(airplane2->validSize("medium"));
        EXPECT_TRUE(airplane2->validSize("large"));
        delete airplane;

        airplane3 = new AirplaneAirline();
//airplane3->setType("airline");
        airplane3->setEngine("propeller");
        EXPECT_FALSE(airplane3->validSize("small"));
        EXPECT_TRUE(airplane3->validSize("medium"));
        EXPECT_FALSE(airplane3->validSize("large"));
        delete airplane;

        airplane4 = new AirplaneMilitairy();
//airplane4->setType("military");
        airplane4->setEngine("jet");
        EXPECT_TRUE(airplane4->validSize("small"));
        EXPECT_FALSE(airplane4->validSize("medium"));
        EXPECT_FALSE(airplane4->validSize("large"));
        delete airplane;

        airplane5 = new AirplaneMilitairy();
//airplane5->setType("military");
        airplane5->setEngine("propeller");
        EXPECT_FALSE(airplane5->validSize("small"));
        EXPECT_FALSE(airplane5->validSize("medium"));
        EXPECT_TRUE(airplane5->validSize("large"));
        delete airplane;

        airplane6 = new AirplaneEmergency();
//airplane6->setType("emergency");
        airplane6->setEngine("propeller");
        EXPECT_TRUE(airplane6->validSize("small"));
        EXPECT_FALSE(airplane6->validSize("medium"));
        EXPECT_FALSE(airplane6->validSize("large"));
        delete airplane;
    }

    TEST_F(AirplaneDomain, validEngineType) {
        airplane = new AirplanePrivate();
        EXPECT_FALSE(airplane->validEngineType("wrongengine"));
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane = new AirplanePrivate();
//airplane->setType("private");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane = new AirplaneAirline();
//airplane->setType("airline");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane = new AirplaneMilitairy();
//airplane->setType("military");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane = new AirplaneEmergency();
//airplane->setType("emergency");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_FALSE(airplane->validEngineType("jet"));

        airplane = new AirplanePrivate();
//airplane->setType("private");
        airplane->setSize("small");
        EXPECT_TRUE(airplane->validEngineType("propeller"));
        EXPECT_TRUE(airplane->validEngineType("jet"));

        airplane1 = new AirplanePrivate();
//airplane1->setType("private");
        airplane1->setSize("medium");
        EXPECT_FALSE(airplane1->validEngineType("propeller"));
        EXPECT_TRUE(airplane1->validEngineType("jet"));

        airplane2 = new AirplaneAirline();
//airplane2->setType("airline");
        airplane2->setSize("medium");
        EXPECT_TRUE(airplane2->validEngineType("propeller"));
        EXPECT_TRUE(airplane2->validEngineType("jet"));

        airplane3 = new AirplaneAirline();
//airplane3->setType("airline");
        airplane3->setSize("large");
        EXPECT_FALSE(airplane3->validEngineType("propeller"));
        EXPECT_TRUE(airplane3->validEngineType("jet"));

        airplane4 = new AirplaneMilitairy();
//airplane4->setType("military");
        airplane4->setSize("small");
        EXPECT_FALSE(airplane4->validEngineType("propeller"));
        EXPECT_TRUE(airplane4->validEngineType("jet"));

        airplane5 = new AirplaneMilitairy();
//airplane5->setType("military");
        airplane5->setSize("large");
        EXPECT_TRUE(airplane5->validEngineType("propeller"));
        EXPECT_FALSE(airplane5->validEngineType("jet"));

        airplane6 = new AirplaneEmergency();
        airplane6->setSize("small");
        EXPECT_TRUE(airplane6->validEngineType("propeller"));
        EXPECT_FALSE(airplane6->validEngineType("jet"));
    }

    TEST_F(AirplaneDomain, validGate) {
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

    TEST_F(AirplaneDomain, validRunway) {
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

    TEST_F(AirplaneDomain, validLandingSpot) {
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

    TEST_F(AirplaneDomain, permissionToDescend) {
        airplane = new Airplane();
        airplane->setHeight(10000);
        airplane->setSize("large");
        airplane->setEngine("jet");
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
//airplane->setType("private");
        EXPECT_FALSE(airplane->isValid());
        airplane->setModel("model");
        EXPECT_FALSE(airplane->isValid());
        airplane->setNumber("52");
        EXPECT_FALSE(airplane->isValid());
        airplane->setCallsign("callsign");
        EXPECT_FALSE(airplane->isValid());
        airplane->setState(incoming);
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
        airplane->setState(ifr);
        airplane->setFlightPlan(flightPlan);

        runway->setOccupied(true);
        EXPECT_DEATH(airplane->pushBack(), "Valid runway");
        runway->setOccupied(false);
        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_EQ(airplane->getState(), ifrRMS);

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_EQ(airplane->getCurrentTask(), "pushback");

        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());


        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());


        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_EQ(airplane->getCurrentTask(), "request taxi");


        EXPECT_NO_FATAL_FAILURE(airplane->pushBack());
        EXPECT_EQ(airplane->getCurrentTask(), "going to runway");

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
        airplane->setState(ifr);
        airplane->setFlightPlan(flightPlan);
        airplane->setPassengerCapacity(100);
        airplane->setPassengers(0);
        airplane->setCurrentTask("exit passengers");
        airplane->exitPlane();
        EXPECT_EQ(airplane->getCurrentTask(), "technical check");
        EXPECT_EQ(airplane->getState(), ifr);
        airplane->setCurrentTask("exit passengers");
        airplane->exitPlane();
        EXPECT_EQ(airplane->getCurrentTask(), "technical check");
        EXPECT_EQ(airplane->getState(), ifr);
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
        EXPECT_EQ(airplane->getState(), ifr);
        airplane->setCurrentTask("board passengers");
        airplane->setPassengers(50);
        airplane->enterPlane();
        EXPECT_TRUE(airplane->getOperationTime() > 0);
        EXPECT_TRUE(airplane->getPassengers() > 50);
    }

    TEST_F(AirplaneDomain, technicalCheck) {
        airplane = new Airplane();
        airplane->setCurrentTask("technical check");
        airplane->setState(gTechnicalCheck);
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);

        airplane->setFuelCapacity(200000);
        airplane->setFuel(200000);


        airplane->technicalCheck();
        EXPECT_TRUE(airplane->getTechnicalChecked());

        airplane->technicalCheck();
        EXPECT_EQ(airplane->getCurrentTask(), "refueling");

        airplane->setCurrentTask("technical check");
        airplane->setFuelCapacity(200000);
        airplane->setFuel(100000);

        airplane->technicalCheck();
        EXPECT_EQ(airplane->getCurrentTask(), "technical check");
        EXPECT_EQ(airplane->getState(), gRefuel);
        EXPECT_TRUE(airplane->getOperationTime() > 0);

        airplane->setCurrentTask("technical check");
        airplane->setFuelCapacity(200000);
        airplane->setFuel(200000);

        airplane->technicalCheck();
        EXPECT_EQ(airplane->getCurrentTask(), "technical check");
        EXPECT_EQ(airplane->getState(), gRefuel);

        airplane->setCurrentTask("technical check");
        airplane->setFuelCapacity(200000);
        airplane->setFuel(100000);

        airplane->technicalCheck();
        EXPECT_EQ(airplane->getCurrentTask(), "technical check");
        EXPECT_EQ(airplane->getState(), gRefuel);
        EXPECT_TRUE(airplane->getOperationTime() > 0);
    }

    TEST_F(AirplaneDomain, refuel) {
        airplane = new Airplane();
        airplane->setCurrentTask("refueling");
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);
        airplane->setState(inGate);
        flightPlan = new FlightPlan();
        airplane->setFlightPlan(flightPlan);
        airplane->refuel();
        EXPECT_EQ(airplane->getCurrentTask(), "board passengers");
        airplane->setCurrentTask("refueling");
        flightPlan->setDeparture(300);
        airplane->refuel();
        EXPECT_EQ(airplane->getCurrentTask(), "board passengers");
        flightPlan->setDeparture(0);
        airplane->setCurrentTask("refueling");
        airplane->refuel();
        EXPECT_EQ(airplane->getCurrentTask(), "board passengers");
    }

    TEST_F(AirplaneDomain, descend) {
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

    TEST_F(AirplaneDomain, ascend) {
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
        airplane->setState(simulationIsFinished);
        EXPECT_FALSE(airplane->notFinished());

    }

    TEST_F(AirplaneDomain, taxiToRunway) {
        runway = new Runway();
        runway->setLength(5000);
        runway->setType("asphalt");
        runway->setName("name");

        runway1 = new Runway();
        runway1->setLength(5000);
        runway1->setType("asphalt");
        runway1->setName("name1");

        airport = new Airport();
        airport->addRunway(runway);
        airport->addRunway(runway1);
        airport->setGates(7);

        airplane = new Airplane();
        airplane->setAirport(airport);

        airplane->setGate(5);

        taxiRoute = new TaxiRoute();
        taxiRoute->addTaxiPoint("point");
        taxiRoute->addTaxiCrossing("name");
        taxiRoute->addTaxiPoint("point1");


        airplane->setCurrentTask("going to runway");
        airplane->setAttemptRunway(runway1);
        runway1->setTaxiRoute(taxiRoute);
        runway1->setOnItsWay(true);

        airplane->taxiToRunway();
        EXPECT_EQ(airplane->getGate(), -1);
        EXPECT_EQ(airplane->getState(), onTaxiPoint);
        EXPECT_EQ(airplane->getTaxiPoint(), "point");
        EXPECT_EQ(airplane->getTaxiCrossing(), "");

        airplane->taxiToRunway();

        airplane->taxiToRunway();

        airplane->taxiToRunway();
        EXPECT_EQ(airplane->getState(), onTaxiCrossing);
        EXPECT_EQ(airplane->getTaxiPoint(), "");
        EXPECT_EQ(airplane->getTaxiCrossing(), "name");

        airplane->taxiToRunway();

        runway->setPermissionToCross(false);
        airplane->taxiToRunway();

        airplane->taxiToRunway();

        runway->setPermissionToCross(true);
        airplane->taxiToRunway();

        airplane->taxiToRunway();
        EXPECT_FALSE(runway->getCrossing());

        airplane->taxiToRunway();
        EXPECT_EQ(airplane->getState(), taxiCrossingNF);


        airplane->taxiToRunway();
        EXPECT_EQ(airplane->getState(), onTaxiPoint);
        EXPECT_EQ(airplane->getTaxiPoint(), "point1");
        EXPECT_EQ(airplane->getTaxiCrossing(), "");

        airplane->taxiToRunway();

        airplane->taxiToRunway();

        airplane->taxiToRunway();
        EXPECT_EQ(airplane->getRunway(), runway1);
        EXPECT_EQ(airplane->getState(), onHoldingPoint);
        EXPECT_EQ(airplane->getCurrentTask(), "at holding point");
        EXPECT_FALSE(runway1->getOnItsWay());
        EXPECT_TRUE(runway1->getHoldingShortOccupied());
        EXPECT_TRUE(airplane->getAttemptRunway() == NULL);
    }

    TEST_F(AirplaneDomain, taxitoGate) {
        runway = new Runway();
        runway->setLength(5000);
        runway->setType("asphalt");
        runway->setName("name");

        runway1 = new Runway();
        runway1->setLength(5000);
        runway1->setType("asphalt");
        runway1->setName("name1");

        airport = new Airport();
        airport->addRunway(runway);
        airport->addRunway(runway1);
        airport->setGates(7);

        airplane = new Airplane();
        airplane->setAirport(airport);

        taxiRoute = new TaxiRoute();
        taxiRoute->addTaxiPoint("point");
        taxiRoute->addTaxiCrossing("name");
        taxiRoute->addTaxiPoint("point1");


        airplane->setCurrentTask("going to gate");
        runway1->setTaxiRoute(taxiRoute);
        airplane->setRunway(runway1);

        airplane->taxiToGate();
        EXPECT_EQ(airplane->getState(), onTaxiPoint);
        EXPECT_EQ(airplane->getTaxiPoint(), "point1");
        EXPECT_EQ(airplane->getTaxiCrossing(), "");


        airplane->taxiToGate();

        airplane->taxiToGate();

        airplane->taxiToGate();
        EXPECT_EQ(airplane->getState(), onTaxiCrossing);
        EXPECT_EQ(airplane->getTaxiPoint(), "");
        EXPECT_EQ(airplane->getTaxiCrossing(), "name");

        airplane->taxiToGate();
        airplane->taxiToGate();
        EXPECT_FALSE(runway->getCrossing());

        airplane->taxiToGate();
        airplane->taxiToGate();

        EXPECT_EQ(airplane->getState(), taxiCrossingNF);

        airplane->taxiToGate();
        EXPECT_EQ(airplane->getState(), onTaxiPoint);

        EXPECT_EQ(airplane->getState(), onTaxiPoint);
        EXPECT_EQ(airplane->getTaxiPoint(), "point");
        EXPECT_EQ(airplane->getTaxiCrossing(), "");

        airplane->taxiToGate();

        airplane->taxiToGate();

        airplane->taxiToGate();
        EXPECT_EQ(airplane->getGate(), airplane->getAttemptGate());
        EXPECT_FALSE(runway1->getOnItsWay());

    }

    TEST_F(AirplaneDomain, takeOff) {

        runway1 = new Runway();
        runway1->setLength(5000);
        runway1->setType("asphalt");
        runway1->setName("name1");

        airport = new Airport();
        airport->addRunway(runway1);

        airplane = new Airplane();
        airplane->setAirport(airport);

        airplane->setCurrentTask("at holding point");
        airplane->setHeight(0);
        airplane->setRunway(runway1);
        runway1->setOnItsWay(true);
        runway1->setHoldingShortOccupied(true);

//situation after taxiToRunway

        airplane->takeOff();
        EXPECT_TRUE(runway1->getOnItsWay());
        EXPECT_FALSE(airplane->isWaitAtRunway());
        EXPECT_FALSE(runway1->getHoldingShortOccupied());

//runway is occupied
        airplane->setHeight(0);
        runway1->setCrossing(false);
        runway1->setWaitingOnRunway(false);
        runway1->setOccupied(true);
        airplane->takeOff();
        EXPECT_FALSE(airplane->isWaitAtRunway());

        airplane->setHeight(0);
        airplane->setRunway(runway1);
        airplane->setAirport(airport);
        airplane->takeOff();
        EXPECT_FALSE(airplane->isWaitAtRunway());
        EXPECT_FALSE(runway1->getHoldingShortOccupied());

//something is crossing
        runway1->setCrossing(true);
        runway1->setOccupied(false);
        airplane->setHeight(0);
        airplane->setRunway(runway1);
        airplane->setAirport(airport);
        airplane->takeOff();
        EXPECT_FALSE(airplane->isPermissionToTakeOff());
        EXPECT_FALSE(airplane->isWaitOnRunway());
        EXPECT_TRUE(runway1->isOccupied());
        EXPECT_TRUE(runway1->getPermissionToCross());

        airplane->setHeight(0);
        airplane->setRunway(runway1);
        airplane->setAirport(airport);
        airplane->takeOff();
        EXPECT_FALSE(airplane->isPermissionToTakeOff());
        EXPECT_FALSE(airplane->isWaitOnRunway());


    }

    TEST_F(AirplaneDomain, TakeOfff) {

        airplane = new Airplane();
        EXPECT_DEATH(airplane->takeOff(), "Assertion.*failed");

        airport = new Airport();
        airplane->setAirport(airport);
        EXPECT_DEATH(airplane->takeOff(), "Assertion.*failed");
    }

    TEST_F(AirplaneDomain, land) {
        runway = new Runway();
        runway->setLength(5000);
        runway->setType("asphalt");
        runway->setName("name");

        runway1 = new Runway();
        runway1->setLength(5000);
        runway1->setType("asphalt");
        runway1->setName("name1");

        airport = new Airport();
        airport->addRunway(runway1);
        airport->addRunway(runway);

        airplane = new Airplane();
        airplane->setSize("medium");
        airplane->setEngine("jet");
        airplane->setState(descendARMS);

        airplane->setCurrentTask("try to land");
        airplane->setHeight(10000);
        airplane->land(airport);
        airplane->land(airport);
        airplane->land(airport);
        airplane->land(airport);
        airplane->land(airport);
        EXPECT_EQ(airplane->getCurrentTask(), "descending to 5000ft.");

        airplane->setHeight(5000);
        airplane->land(airport);
        airplane->land(airport);
        airplane->land(airport);
        EXPECT_EQ(airplane->getCurrentTask(), "descending to 3000ft.");


        airplane->setHeight(3000);
        airplane->land(airport);
        airplane->land(airport);
        airplane->land(airport);
        airplane->land(airport);
        EXPECT_EQ(airplane->getCurrentTask(), "descending to 0ft.");
        EXPECT_EQ(airplane->getAttemptRunway(), runway1);

        airplane->setHeight(1000);
        airplane->land(airport);
        EXPECT_EQ(airplane->getCurrentTask(), "descending to 0ft.");

        airplane->setHeight(0);
        airplane->land(airport);
        EXPECT_EQ(airplane->getCurrentTask(), "landing");

    }
}
