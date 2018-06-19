//
// Created by oliviervh on 30.04.18.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "gtest/gtest.h"

#include "Airplane.h"
#include "Airport.h"
#include "AirportHandler.h"
#include "MessageSystem.h"
#include "RunwayClass.h"

namespace {

    class AirportHandlerFunctionDomain : public ::testing::Test{
    protected:
        AirportHandlerFunctionDomain() {

        }

        virtual void SetUp() {
            handler = new AirportHandler();
            planeA = new Airplane();
            planeB = new Airplane();
            airportA = new Airport();
            airportB = new Airport();

        }

        virtual void TearDown() {
            openNewLogFile("DefaultLog.txt");
            openNewLogFile("DefaultCommLog.txt");
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

    TEST_F(AirportHandlerFunctionDomain, Constructor){
        handlerNoInit = new AirportHandler();
        EXPECT_TRUE(handlerNoInit->properlyInitialised());

    }

    TEST_F(AirportHandlerFunctionDomain, AddAirport){

        // No airports yet
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));

        // No Iata
        EXPECT_FALSE(handler->validAirport(airportA));
        EXPECT_DEATH(handler->addAirport(airportA), "Assertion.*failed");

        // Valid iata
        airportA->setIata("Valid Iata");
        EXPECT_TRUE(handler->validAirport(airportA));
        EXPECT_NO_FATAL_FAILURE(handler->addAirport(airportA));

        // Airport added twice
        EXPECT_FALSE(handler->validAirport(airportA));
        EXPECT_DEATH(handler->addAirport(airportA), "Assertion.*failed");

        // Airport added with the same iata
        airportB->setIata("Valid Iata");
        EXPECT_FALSE(handler->validAirport(airportB));
        EXPECT_DEATH(handler->addAirport(airportB), "Assertion.*failed");

    }

    TEST_F(AirportHandlerFunctionDomain, RemoveAirplane){

        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_NO_FATAL_FAILURE(handler->addXmlData("XMLTests/TestVolledigeLuchthaven16.xml"));

        EXPECT_EQ(handler->getAirplanes().size(), unsigned(2));
        EXPECT_NO_FATAL_FAILURE(handler->removeAirplane("BAW466"));
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(1));
        EXPECT_DEATH(handler->removeAirplane("BAW466"), "Assertion.*failed");
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(1));
        EXPECT_NO_FATAL_FAILURE(handler->removeAirplane("BAW467"));
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_DEATH(handler->removeAirplane("BAW467"), "Assertion.*failed");
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));

    }

    TEST_F(AirportHandlerFunctionDomain, AddAirplane){

        // No planes yet
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));



        // No number
        EXPECT_FALSE(handler->validAirplane(planeA));
        EXPECT_DEATH(handler->addAirplane(planeA), "Assertion.*failed");

        // Valid number
        planeA->setNumber("Valid Number");
        EXPECT_TRUE(handler->validAirplane(planeA));
        EXPECT_NO_FATAL_FAILURE(handler->addAirplane(planeA));

        // Airplane added twice
        EXPECT_FALSE(handler->validAirplane(planeA));
        EXPECT_DEATH(handler->addAirplane(planeA), "Assertion.*failed");

        // Airplane added with the same number
        planeB->setNumber("Valid Number");
        EXPECT_FALSE(handler->validAirplane(planeB));
        EXPECT_DEATH(handler->addAirplane(planeB), "Assertion.*failed");

    }

    TEST_F(AirportHandlerFunctionDomain, RemoveAirport){

        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_NO_FATAL_FAILURE(handler->addXmlData("XMLTests/TestVolledigeLuchthaven8.xml"));

        EXPECT_EQ(handler->getAirports().size(), unsigned(1));
        EXPECT_NO_FATAL_FAILURE(handler->removeAirport("ANR"));
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_DEATH(handler->removeAirport("ANR"), "Assertion.*failed");
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));


    }

    TEST_F(AirportHandlerFunctionDomain, SetAirplanes){

        planeA->setNumber("one");
        planeB->setNumber("one");

        vector<Airplane*> planes;

        planes.push_back(planeA);
        planes.push_back(planeB);

        EXPECT_FALSE(handler->validAirplanes(planes));
        EXPECT_DEATH(handler->setAirplanes(planes), "Assertion.*failed");

        planeB->setNumber("two");

        EXPECT_TRUE(handler->validAirplanes(planes));
        EXPECT_NO_FATAL_FAILURE(handler->setAirplanes(planes));


    }

    TEST_F(AirportHandlerFunctionDomain, SetAirports){

        airportA->setIata("one");
        airportB->setIata("one");

        vector<Airport*> airports;

        airports.push_back(airportA);
        airports.push_back(airportB);

        EXPECT_FALSE(handler->validAirports(airports));
        EXPECT_DEATH(handler->setAirports(airports), "Assertion.*failed");

        airportB->setIata("two");

        EXPECT_TRUE(handler->validAirports(airports));
        EXPECT_NO_FATAL_FAILURE(handler->setAirports(airports));

    }


    class RunwayDomain : public ::testing::Test {
    protected:

        RunwayDomain() {

        }

        virtual void SetUp() {
            runway = new Runway();
            taxiRoute = new TaxiRoute();
            airport = new Airport();
        }

        virtual void TearDown() {
            delete runway;
            delete taxiRoute;
        }
        TaxiRoute* taxiRoute;
        Runway *runway;
        string myString;
        Airport* airport;
    };

    TEST_F(RunwayDomain, setType) {
        myString = "grond";
        EXPECT_DEATH(runway->setType(myString), "Assertion.*failed");
        myString = "grass";
        EXPECT_NO_FATAL_FAILURE(runway->setType(myString));
        myString = "asphalt";
        EXPECT_NO_FATAL_FAILURE(runway->setType(myString));
    }

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
        EXPECT_NO_FATAL_FAILURE(runway->setName("Rname"));
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
        int myInt = 200;
        runway->setLength(myInt);
        EXPECT_TRUE(runway->isValid());
    }


    class AirportDomain : public ::testing::Test {
    protected:

        AirportDomain() {

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

    TEST_F(AirportDomain, setGateOccupied) {
        myInt = 5;
        airport->setGates(myInt);
        EXPECT_NO_FATAL_FAILURE(airport->setGateOccupied(myInt-1,true));
        EXPECT_NO_FATAL_FAILURE(airport->getGateOccupied(myInt-1));
        EXPECT_DEATH(airport->setGateOccupied(myInt,true), "Valid gate index");
        EXPECT_DEATH(airport->getGateOccupied(myInt), "Valid gate index");

    }

    TEST_F(AirportDomain, getFreeGates) {
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

    TEST_F(AirportDomain, addRunway) {
        EXPECT_DEATH(airport->addRunway(runway), "Runway bad name");
        runway->setName("name");
        EXPECT_DEATH(airport->addRunway(runway), "Runway bad type");
        runway->setType("asphalt");
        EXPECT_DEATH(airport->addRunway(runway), "Runway bad length");
        runway->setLength(200);
        EXPECT_NO_FATAL_FAILURE(airport->addRunway(runway));
        EXPECT_DEATH(airport->addRunway(runway), "Runway doesn't exist yet");
    }

    TEST_F(AirportDomain, removeRunway) {
        runway->setName("name");
        runway->setType("asphalt");
        runway->setLength(200);
        EXPECT_NO_FATAL_FAILURE(airport->addRunway(runway));
        EXPECT_DEATH(airport->removeRunway(""), "Runway exists");
        EXPECT_NO_FATAL_FAILURE(airport->removeRunway("name"));
        EXPECT_DEATH(airport->removeRunway("name"), "Runway exists");
    }

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
        EXPECT_NO_FATAL_FAILURE(airport = new Airport("name", "iata", "callsign", 5));
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

        AirportHandler *handler;
        AirportHandler *handler2;
        AirportHandler *handler3;
        AirportHandler *handler4;

    };

    TEST_F(AirportHandlerDomain, RunSimulation) {

        // No Airports
        handler->addXmlData("XMLTests/TestVolledigeLuchthaven16.xml");
        EXPECT_DEATH(handler->runSimulation(""), "Assertion.*failed");

        // No runways
        handler3->addXmlData("XMLTests/TestVolledigeLuchthaven2.xml");
        EXPECT_DEATH(handler3->runSimulation("ANR"), "Assertion.*failed");

        // No Airplanes
        handler4->addXmlData("XMLTests/TestVolledigeLuchthaven9.xml");
        EXPECT_DEATH(handler4->runSimulation("ANR"), "Assertion.*failed");

        // Correcte Luchthaven + airplanes
        EXPECT_EQ(handler2->addXmlData("XMLTests/TestVolledigeLuchthaven10.xml"), success);
        EXPECT_NO_FATAL_FAILURE(handler2->runSimulation("ANR"));

    }

    TEST_F(AirportHandlerDomain, SortAirplanes1){

        EXPECT_EQ(handler2->addXmlData("XMLTests/TestVolledigeLuchthaven10.xml"), success);
        vector<Airplane*> planes = handler2->getAirplanes();
        EXPECT_EQ(planes.size(), unsigned (3));

        planes[0]->setSquawkCode(1);
        planes[1]->setSquawkCode(1);
        planes[2]->setSquawkCode(1);

        handler2->sortPlanesBySquawk();

        vector<Airplane*> planes2 = handler2->getAirplanes();

        EXPECT_EQ(planes[0], planes2[0] );
        EXPECT_EQ(planes[1], planes2[1] );
        EXPECT_EQ(planes[2], planes2[2] );

    }

    TEST_F(AirportHandlerDomain, SortAirplanes2){

        EXPECT_EQ(handler2->addXmlData("XMLTests/TestVolledigeLuchthaven10.xml"), success);
        vector<Airplane*> planes = handler2->getAirplanes();
        EXPECT_EQ(planes.size(), unsigned (3));

        planes[0]->setSquawkCode(1);
        planes[1]->setSquawkCode(2);
        planes[2]->setSquawkCode(3);

        handler2->sortPlanesBySquawk();

        vector<Airplane*> planes2 = handler2->getAirplanes();

        EXPECT_EQ(planes[0], planes2[0] );
        EXPECT_EQ(planes[1], planes2[1] );
        EXPECT_EQ(planes[2], planes2[2] );

    }

    TEST_F(AirportHandlerDomain, SortAirplanes3){

        EXPECT_EQ(handler2->addXmlData("XMLTests/TestVolledigeLuchthaven10.xml"), success);
        vector<Airplane*> planes = handler2->getAirplanes();
        EXPECT_EQ(planes.size(), unsigned (3));

        planes[0]->setSquawkCode(1);
        planes[1]->setSquawkCode(3);
        planes[2]->setSquawkCode(2);

        handler2->sortPlanesBySquawk();

        vector<Airplane*> planes2 = handler2->getAirplanes();

        EXPECT_EQ(planes[0], planes2[0] );
        EXPECT_EQ(planes[2], planes2[1] );
        EXPECT_EQ(planes[1], planes2[2] );

    }

    TEST_F(AirportHandlerDomain, SortAirplanes4){

        EXPECT_EQ(handler2->addXmlData("XMLTests/TestVolledigeLuchthaven10.xml"), success);
        vector<Airplane*> planes = handler2->getAirplanes();
        EXPECT_EQ(planes.size(), unsigned (3));

        planes[0]->setSquawkCode(3);
        planes[1]->setSquawkCode(2);
        planes[2]->setSquawkCode(1);

        handler2->sortPlanesBySquawk();

        vector<Airplane*> planes2 = handler2->getAirplanes();

        EXPECT_EQ(planes[0], planes2[2] );
        EXPECT_EQ(planes[1], planes2[1] );
        EXPECT_EQ(planes[2], planes2[0] );

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

        TaxiRoute *taxiRoute;
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

        FlightPlan *flightPlan;
        string myString;
        int myInt;
    };

    TEST_F(FlightPlanDomain, defaultConstructor) {
        EXPECT_TRUE(flightPlan->properlyInitialised());
    }

    TEST_F(FlightPlanDomain, isValid) {
        myString = "destination";
        flightPlan->setInterval(0);
        flightPlan->setDestination(myString);
        EXPECT_FALSE(flightPlan->isValid());
        myInt = 45;
        flightPlan->setInterval(myInt);
        EXPECT_TRUE(flightPlan->isValid());
    }



}
