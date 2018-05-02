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
        myString = "name";
        EXPECT_NO_FATAL_FAILURE(runway->setVar(myString, "Rname"));
        myString = "type";
        EXPECT_NO_FATAL_FAILURE(runway->setVar(myString, "Rtype"));
        myString = "length";
        EXPECT_NO_FATAL_FAILURE(runway->setVar(myString, "200"));
        EXPECT_EQ(runway->getName(), "Rname");
        EXPECT_EQ(runway->getType(), "Rtype");
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
}
