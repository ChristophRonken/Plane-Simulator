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
        myString = "point";
        taxiRoute->addTaxiPoint(myString);
        EXPECT_TRUE(taxiRoute->isValid());
    }

    class FlightPlanDomain : public ::testing::Test {
    protected:

        FlightPlanDomain() {

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

    TEST_F(FlightPlanDomain, defaultConstructor) {
        EXPECT_TRUE(flightPlan->properlyInitialised());
    }

    TEST_F(FlightPlanDomain, isValid){
        myString = "destination";
        flightPlan->setDestination(myString);
        myInt = 45;
        flightPlan->setInterval(myInt);
        EXPECT_TRUE(flightPlan->isValid());
    }
}
