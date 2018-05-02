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

    class AirplaneInput: public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        AirplaneInput() {


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
        AirportHandler *D;
    };


    TEST_F(AirplaneInput, setType) {
        airplane = new Airplane();
        EXPECT_DEATH(airplane->setType(""), "Valid type?");
        EXPECT_DEATH(airplane->setType("falsetype"), "Valid type?");
        EXPECT_NO_FATAL_FAILURE(airplane->setType("military"));
        EXPECT_NO_FATAL_FAILURE(airplane->setType("private"));
        EXPECT_NO_FATAL_FAILURE(airplane->setType("emergency"));
        EXPECT_NO_FATAL_FAILURE(airplane->setType("airline"));

    }

    TEST_F(AirplaneInput, setEngine) {
        airplane = new Airplane();
        EXPECT_DEATH(airplane->setEngine(""), "valid Engine");
        EXPECT_DEATH(airplane->setEngine("falsetype"), "valid Engine");
        EXPECT_NO_FATAL_FAILURE(airplane->setEngine("propeller"));
        EXPECT_NO_FATAL_FAILURE(airplane->setEngine("jet"));
    }

    TEST_F(AirplaneInput, setSize) {
        airplane = new Airplane();
        EXPECT_DEATH(airplane->setSize(""), "valid size");
        EXPECT_DEATH(airplane->setSize("falsetype"), "valid size");
        EXPECT_NO_FATAL_FAILURE(airplane->setSize("small"));
        EXPECT_NO_FATAL_FAILURE(airplane->setSize("medium"));
        EXPECT_NO_FATAL_FAILURE(airplane->setSize("large"));
    }

    TEST_F(AirplaneInput, setGate) {
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

    TEST_F(AirplaneInput, getDestination) {
        airplane = new Airplane();
        flightPlan = new FlightPlan();
        EXPECT_DEATH(airplane->getDestination(), "has a flightPlan");
        airplane->setFlightPlan(flightPlan);
        EXPECT_NO_FATAL_FAILURE(airplane->getDestination());
    }

    TEST_F(AirplaneInput, pushBack) {
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

    TEST_F(AirplaneInput, exitPlane) {
        airplane = new Airplane();
        airplane->setCurrentTask("wrong task");
        EXPECT_DEATH(airplane->exitPlane();, "correct state");
        airplane->setCurrentTask("exit passengers");
        EXPECT_DEATH(airplane->exitPlane();, "at gate");
        airport = new Airport();
        airport->setGates(5);
        airplane->setAirport(airport);
        airplane->setGate(3);
        EXPECT_NO_FATAL_FAILURE(airplane->exitPlane(););
    }

    TEST_F(AirplaneInput, enterPlane) {
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

    TEST_F(AirplaneInput, technicalCheck) {
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

    TEST_F(AirplaneInput, refuel) {
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
        EXPECT_NO_FATAL_FAILURE(airplane->refuel(););
    }


}
