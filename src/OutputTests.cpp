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
}
