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
        cout << "ok" << airport->getRunways().size() << endl;
        runway->setName("name");
        runway->setType("asphalt");
        runway->setLength(200);

        EXPECT_NO_FATAL_FAILURE(airport->addRunway(runway));
        EXPECT_NO_FATAL_FAILURE(airport->removeRunway("name"));
        EXPECT_FALSE(airport->runwayExists("name"));
    }
}
