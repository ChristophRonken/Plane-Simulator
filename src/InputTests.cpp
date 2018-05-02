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


    class RunwayInput : public ::testing::Test {
    protected:

        RunwayInput() {

        }

        virtual void SetUp() {
            runway = new Runway();
        }

        virtual void TearDown() {
            delete runway;
        }

        Runway *runway;
        string myString;
    };

    TEST_F(RunwayInput, setType) {
        myString = "grond";
        EXPECT_DEATH(runway->setType(myString), "Assertion.*failed");
        myString = "grass";
        EXPECT_NO_FATAL_FAILURE(runway->setType(myString));
        myString = "asphalt";
        EXPECT_NO_FATAL_FAILURE(runway->setType(myString));
    }

    class AirportInput : public ::testing::Test {
    protected:

        AirportInput() {

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

    TEST_F(AirportInput, setGateOccupied) {
        myInt = 5;
        airport->setGates(myInt);
        EXPECT_NO_FATAL_FAILURE(airport->setGateOccupied(myInt-1,true));
        EXPECT_NO_FATAL_FAILURE(airport->getGateOccupied(myInt-1));
        EXPECT_DEATH(airport->setGateOccupied(myInt,true), "Valid gate index");
        EXPECT_DEATH(airport->getGateOccupied(myInt), "Valid gate index");

    }

    TEST_F(AirportInput, getFreeGates) {
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


    TEST_F(AirportInput, addRunway) {
        EXPECT_DEATH(airport->addRunway(runway), "Runway bad name");
        runway->setName("name");
        EXPECT_DEATH(airport->addRunway(runway), "Runway bad type");
        runway->setType("asphalt");
        EXPECT_DEATH(airport->addRunway(runway), "Runway bad length");
        runway->setLength(200);
        EXPECT_NO_FATAL_FAILURE(airport->addRunway(runway));
        EXPECT_DEATH(airport->addRunway(runway), "Runway doesn't exist yet");
    }

    TEST_F(AirportInput, removeRunway) {
        runway->setName("name");
        runway->setType("asphalt");
        runway->setLength(200);
        EXPECT_NO_FATAL_FAILURE(airport->addRunway(runway));
        EXPECT_DEATH(airport->removeRunway(""), "Runway exists");
        EXPECT_NO_FATAL_FAILURE(airport->removeRunway("name"));
        EXPECT_DEATH(airport->removeRunway("name"), "Runway exists");
    }
}
