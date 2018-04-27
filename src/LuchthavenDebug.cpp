// Created by oliviervh on 01.03.18.
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

    class AirplaneTest : public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        AirplaneTest() {


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
        Airplane *plane;
        Airplane *plane1;
        Airplane *plane2;
        Runway *runway;
        Runway *runway1;
        AirportHandler *D;
    };

    TEST_F(AirplaneTest, constructor) {
        plane = new Airplane();

        EXPECT_EQ(-1, plane->getGate());
        EXPECT_EQ(NULL, plane->getRunway());
        EXPECT_EQ(125, plane->getPassengers());
        EXPECT_EQ(125, plane->getPassengerCapacity());
    }

    TEST_F(AirplaneTest, getset_Type) {
        plane = new Airplane();

        plane->setType("Boeing");
        EXPECT_EQ("Boeing", plane->getType());
    }

    TEST_F(AirplaneTest, getset_Number) {
        plane = new Airplane();

        plane->setNumber("5");
        EXPECT_EQ("5", plane->getNumber());
    }

    TEST_F(AirplaneTest, getset_Callsign) {
        plane = new Airplane();

        plane->setCallsign("callTest");
        EXPECT_EQ("callTest", plane->getCallsign());
    }

    TEST_F(AirplaneTest, getset_Model) {
        plane = new Airplane();

        plane->setModel("Boeing 747");
        EXPECT_EQ("Boeing 747", plane->getModel());
    }

    TEST_F(AirplaneTest, getset_State) {
        plane = new Airplane();

        plane->setState("Standing at gate");
        EXPECT_EQ("Standing at gate", plane->getState());
    }

    TEST_F(AirplaneTest, getset_Airport) {
        plane = new Airplane();

        plane->setAirport(airport);
        EXPECT_EQ(airport, plane->getAirport());
    }

    TEST_F(AirplaneTest, getset_Runway) {
        plane = new Airplane();

        plane->setRunway(runway);
        EXPECT_EQ(runway, plane->getRunway());
    }

    TEST_F(AirplaneTest, getset_Fuel) {
        plane = new Airplane();

        plane->setFuel(5);
        EXPECT_EQ(5, plane->getFuel());
    }

    TEST_F(AirplaneTest, getset_Height){
        plane = new Airplane();

        plane->setHeight(200);
        EXPECT_EQ(200, plane->getHeight());
    }

    TEST_F(AirplaneTest, getset_Engine){
        plane = new Airplane();

        plane->setEngine("4-cilinderige motor");
        EXPECT_EQ("4-cilinderige motor", plane->getEngine());
    }

    TEST_F(AirplaneTest, getset_Size){
        plane = new Airplane();

        plane->setSize("groot");
        EXPECT_EQ("groot", plane->getSize());
    }

    TEST_F(AirplaneTest, getset_Opperationtime){
        plane = new Airplane();

        plane->setOpperationTime(10);
        EXPECT_EQ(10, plane->getOpperationTime());
    }

    TEST_F(AirplaneTest, getset_Passengers) {
        plane = new Airplane();

        plane->setPassengers(5);
        EXPECT_EQ(5, plane->getPassengers());
    }

    TEST_F(AirplaneTest, getset_PassengerCapacity) {
        plane = new Airplane();

        plane->setPassengerCapacity(5);
        EXPECT_EQ(5, plane->getPassengerCapacity());
    }

    TEST_F(AirplaneTest, getset_Vars) {
        plane = new Airplane();

        EXPECT_DEATH(plane->setVar("foutief type", "9ab"), "Assertion.*failed");
        plane->setVar("number", "7");
        plane->setVar("model", "TufTuf");
        plane->setVar("callsign", "J420");
        plane->setVar("status", "in brand");
        EXPECT_EQ("7", plane->getNumber());
        EXPECT_EQ("TufTuf", plane->getModel());
        EXPECT_EQ("J420", plane->getCallsign());
        EXPECT_EQ("in brand", plane->getState());
    }

    TEST_F(AirplaneTest, getInfo) {
        plane = new Airplane();

        plane->setVar("number", "7");
        plane->setVar("model", "TufTuf");
        plane->setVar("callsign", "J420");
        plane->setVar("status", "in brand");

        string str = "\nAirplane:\t";
        str += "J420";
        str += " (";
        str += "7";
        str += ")\n";
        str += "->model:\t";
        str += "TufTuf";
        str += "\n";
        str += "->type:\t\n->engine:\t\n->size:\t\n";
        EXPECT_EQ(str, plane->getInfo());
    }

    TEST_F(AirplaneTest, isReadyForDeparture) {
        plane = new Airplane();
        plane1 = new Airplane();

        plane->setCallsign("J420");
        plane1->setCallsign("65A5B");

        airport = new Airport();
        airport->setCallsign("AntwerpAir");
        airport->setGates(2);

        plane->setAirport(airport);
        plane1->setAirport(airport);

        // plane goes to gate 0
        plane->toGate();

        //plane1 has no valid gate
        EXPECT_FALSE(plane1->getReadyForDeparture());
        EXPECT_DEATH(plane1->prepareForDeparture(), "Assertion.*failed");

        //has a valid gate
        EXPECT_FALSE(plane->getReadyForDeparture());
        plane->prepareForDeparture();
        EXPECT_TRUE(plane->getReadyForDeparture());
    }

    TEST_F(AirplaneTest, toGate) {
        plane = new Airplane();
        Airplane* plane1 = new Airplane();
        Airplane* plane2 = new Airplane();

        plane->setCallsign("J420");
        plane1->setCallsign("65A5B");
        plane2->setCallsign("H4L0");

        airport = new Airport();
        airport->setCallsign("AntwerpAir");
        airport->setGates(2);

        plane->setAirport(airport);
        plane1->setAirport(airport);
        plane2->setAirport(airport);


        // plane tries to go to gate which doesn't exist
        EXPECT_DEATH(plane->toGate(10), "Assertion.*failed");

        // plane tries to go to gate 1
        plane->toGate(1);
        EXPECT_EQ(1, plane->getGate());

        // plane1 tries to go to occupied gate
        EXPECT_DEATH(plane1->toGate(1), "Assertion.*failed");

        // plane goes to first open gate
        plane->toGate();

        // plane1 goes to first open gate
        plane1->toGate();
        // plane2 tries to go to first open gate, but no free gates
        EXPECT_DEATH(plane2->toGate(), "Assertion.*failed");

        // plane & plane1 are in correct gates, plane2 isn't in a gate
        EXPECT_EQ(0, plane->getGate());
        EXPECT_EQ(1, plane1->getGate());
        EXPECT_EQ(-1, plane2->getGate());

        EXPECT_EQ("Standing at gate", plane->getState());
        EXPECT_EQ("Standing at gate", plane1->getState());
        EXPECT_NE("Standing at gate", plane2->getState());
    }

    TEST_F(AirplaneTest, toRunway){
        plane = new Airplane();
        plane1 = new Airplane();
        plane2 = new Airplane();

        D = new AirportHandler();
        D->addXmlData("TestVolledigeLuchthaven.xml");
        airport = D->getAirports()[0];

        runway = new Runway;
        runway = airport->getRunways()[0];

        runway1 = new Runway;
        runway1 = airport->getRunways()[1];

        plane = D->getAirplanes()[0];
        plane1 = D->getAirplanes()[1];
        plane2 = D->getAirplanes()[2];

        plane->setAirport(airport);
        plane1->setAirport(airport);
        plane2->setAirport(airport);

        // planes go to gates
        plane->toGate();
        plane1->toGate();
        plane2->toGate();


        //plane2 gaat naar de eerste vrije (appropriate) runway (1)
        EXPECT_NO_FATAL_FAILURE(plane2->toRunway());
        EXPECT_EQ(runway1, plane2->getRunway());

        //plane probeert te gaan naar occupied runway (0)
        EXPECT_DEATH(plane->toRunway(runway1), "Assertion.*failed");

        //plane2 gaat naar de eerste vrije (appropriate) runway (0)
        EXPECT_NO_FATAL_FAILURE(plane->toRunway());

        //no free runways
        EXPECT_DEATH(plane1->toRunway(), "Assertion.*failed");
    }

    TEST_F(AirplaneTest, takeOff){
        D = new AirportHandler();
        D->addXmlData("TestVolledigeLuchthaven.xml");

        airport = new Airport();
        airport = D->getAirports()[0];

        runway = new Runway();
        runway = airport->getRunways()[0];

        plane = new Airplane();
        plane = D->getAirplanes()[0];
        plane->setAirport(airport);

        // plane goes to gate 0
        plane->toGate();

        //plane not ready for departure
        EXPECT_DEATH(plane->takeOff(), "Assertion.*failed");
        plane->prepareForDeparture();

        //plane not on a runway
        EXPECT_DEATH(plane->takeOff(), "Assertion.*failed");
        plane->setRunway(runway);

        //plane is ready for takeoff
        EXPECT_NO_FATAL_FAILURE(plane->takeOff());

        //plane does no longer belong to an airport
        EXPECT_EQ(NULL, plane->getAirport());
    }

    TEST_F(AirplaneTest, land) {
        D = new AirportHandler();
        D->addXmlData("TestVolledigeLuchthaven.xml");

        airport = new Airport();
        airport = D->getAirports()[0];

        airport1 = new Airport();
        airport1 = D->getAirports()[1];

        runway = new Runway();
        runway = airport->getRunways()[0];

        runway1 = new Runway();
        runway1 = airport->getRunways()[1];

        plane = new Airplane();
        plane = D->getAirplanes()[0];

        plane1 = new Airplane();
        plane1 = D->getAirplanes()[2];

        plane->setState("Airborne");
        plane1->setState("Airborne");

        // airport1 heeft geen runways
        EXPECT_DEATH(plane->land(airport1), "Assertion.*failed");

        // airport heeft 2 vrije runways
        EXPECT_EQ((unsigned)2, airport->getFreeRunways().size());
        EXPECT_NO_FATAL_FAILURE(plane->land(airport, runway1));
        EXPECT_EQ((unsigned)1, airport->getFreeRunways().size());
        //plane is no longer airborne, cannot land twice
        EXPECT_DEATH(plane->land(airport, runway), "Assertion.*failed");

        EXPECT_EQ((unsigned)1, airport->getFreeRunways().size());
        //airport heeft geen vrije appropriate Runway
        EXPECT_DEATH(plane1->land(airport, runway), "Assertion.*failed");
        EXPECT_DEATH(plane1->land(airport), "Assertion.*failed");
    }

    TEST_F(AirplaneTest, goinair){
        airport = new Airport();
        runway = new Runway;
        runway->setType("asphalt");
        runway->setLength(2000);
        runway->setName("dezeRunway");
        plane = new Airplane();
        plane1 = new Airplane();

        airport->addRunway(runway);
        airport->setGates(5);

        plane->setAirport(airport);
        plane->setEngine("propeller");
        plane->setSize("medium");
        plane->setCallsign("plane1");
        plane->setNumber("1");
        plane->setState("At runway");
        plane->setModel("model");
        plane->setRunway(runway);
        plane->setHeight(0);
        plane->setReadyForDeparture(true);

        plane1->setAirport(airport);
        plane1->setEngine("propeller");
        plane1->setSize("medium");
        plane1->setCallsign("plane2");
        plane1->setNumber("2");
        plane1->setState("At runway");
        plane1->setModel("model");
        plane1->setRunway(runway);
        plane1->setHeight(0);
        plane1->setReadyForDeparture(true);
        while(plane1->getHeight() == 0) {
            cout << "ok" << endl;
            if (plane->getHeight() ==0) {
                EXPECT_NO_FATAL_FAILURE(plane->takeOff());
            }
            EXPECT_NO_FATAL_FAILURE(plane1->takeOff());
        }
        closeFile();
    }



    class AirportTest : public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        AirportTest() {

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
        Airplane *plane;
        Airplane *plane1;
        Runway *runway;
        Runway *runway1;
        Runway *runway2;
        Runway *runway3;
        AirportHandler *D;
    };

    TEST_F(AirportTest, constructor) {
        airport = new Airport("naam", "hallo", "A750", 5);

        EXPECT_EQ("naam", airport->getName());
        EXPECT_EQ("hallo", airport->getIata());
        EXPECT_EQ("A750", airport->getCallsign());
        EXPECT_EQ(5, airport->getGates());
    }

    TEST_F(AirportTest, getFreeGates){
        plane = new Airplane();
        Airplane* plane1 = new Airplane();

        plane->setCallsign("J420");
        plane1->setCallsign("65A5B");

        airport = new Airport();
        airport->setCallsign("AntwerpAir");
        airport->setGates(1);

        plane->setAirport(airport);
        plane1->setAirport(airport);


        unsigned int free_gates = (int) airport->getFreeGates().size();

        // plane goes to gate 0 and plane1 tries going to gate 1 (which is non-existent)
        plane->toGate();
        EXPECT_DEATH(plane1->toGate(), "Assertion.*failed");

        //amount of free gates reduces
        EXPECT_EQ(free_gates-1, airport->getFreeGates().size());
    }

    TEST_F(AirportTest, getset_Name) {
        airport = new Airport();

        airport->setName("privevlieghaven");
        EXPECT_EQ("privevlieghaven", airport->getName());
    }

    TEST_F(AirportTest, getset_Iata) {
        airport = new Airport();

        airport->setIata("dierentuin");
        EXPECT_EQ("dierentuin", airport->getIata());
    }

    TEST_F(AirportTest, getset_Callsign) {
        airport = new Airport();

        airport->setCallsign("dier4U");
        EXPECT_EQ("dier4U", airport->getCallsign());
    }

    TEST_F(AirportTest, getset_Gates) {
        airport = new Airport();

        airport->setGates(3);
        EXPECT_EQ(3, airport->getGates());
    }

    TEST_F(AirportTest, getset_Vars) {
        airport = new Airport();

        EXPECT_DEATH(airport->setVar("foutief type", "9ab"),  "Assertion.*failed");
        airport->setVar("name", "7");
        airport->setVar("iata", "TufTuf");
        airport->setVar("callsign", "J420");
        airport->setVar("gates", "5");
        EXPECT_EQ("7", airport->getName());
        EXPECT_EQ("TufTuf", airport->getIata());
        EXPECT_EQ("J420", airport->getCallsign());
        EXPECT_EQ(5, airport->getGates());
    }

    TEST_F(AirportTest, getInfo) {
        airport = new Airport();

        airport->setVar("name", "7");
        airport->setVar("iata", "TufTuf");
        airport->setVar("callsign", "J420");
        airport->setVar("gates", "5");

        string str = "\nAirport:\t";
        str += "7 (TufTuf)\n->callsign:\tJ420\n->gates:\t";
        str += intToString(5) + "\n";
        str += "->runways:\t";
        str += intToString(0);
        str += "\n";
        EXPECT_EQ(str, airport->getInfo());
    }

    TEST_F(AirportTest, addremove_Runway){
        airport = new Airport();
        airport->setCallsign("AntwerpAir");

        runway = new Runway();
        runway1 = new Runway();
        runway2 = new Runway();
        runway3 = new Runway();

        runway->setName("11R");
        runway1->setName("13R");
        runway2->setName("13R");

        runway->setLength(1000);
        runway1->setLength(1000);
        runway2->setLength(1000);

        runway->setType("asphalt");
        runway1->setType("asphalt");
        runway2->setType("asphalt");


        airport->addRunway(runway);
        airport->addRunway(runway1);
        airport->removeRunway("11R");
        EXPECT_EQ((unsigned)1,  airport->getRunways().size());
        EXPECT_DEATH(airport->removeRunway("11R"), "Assertion.*failed");
        EXPECT_DEATH(airport->addRunway(runway2), "Assertion.*failed");
        EXPECT_DEATH(airport->addRunway(runway3), "Assertion.*failed");
    }

    TEST_F(AirportTest, setRunways) {
        airport = new Airport();
        runway = new Runway();
        runway1 = new Runway();

        //runway1 has no name
        runway->setName("11R");
        runway->setLength(500);
        runway->setType("asphalt");

        vector<Runway *> allrunways;
        allrunways.push_back(runway);
        allrunways.push_back(runway1);
        const vector<Runway *> final = allrunways;
        EXPECT_DEATH(airport->setRunways(final),"Assertion.*failed");

        //runways have same name
        runway1->setName("11R");
        runway1->setLength(500);
        runway1->setType("asphalt");

        allrunways.clear();
        allrunways.push_back(runway);
        allrunways.push_back(runway1);
        const vector<Runway *> final1 = allrunways;
        EXPECT_DEATH(airport->setRunways(final1),"Assertion.*failed");

        //runways have unique name
        runway1->setName("12R");

        allrunways.clear();
        allrunways.push_back(runway);
        allrunways.push_back(runway1);
        const vector<Runway *> final2 = allrunways;
        EXPECT_NO_FATAL_FAILURE(airport->setRunways(final2));
    }

    TEST_F(AirportTest, getFreeRunways) {
        airport = new Airport();
        runway = new Runway();
        runway1 = new Runway();
        plane = new Airplane();

        plane->setType("DitType");
        plane->setCallsign("CS");
        plane->setNumber("5");
        plane->setSize("small");
        plane->setEngine("propeller");
        plane->setAirport(airport);

        runway->setName("11R");
        runway->setLength(500);
        runway->setType("asphalt");

        runway1->setName("12R");
        runway1->setLength(500);
        runway1->setType("asphalt");

        airport->addRunway(runway);
        airport->addRunway(runway1);

        //getFreeRunways
        EXPECT_EQ((unsigned) 2, airport->getFreeRunways().size());
        plane->toRunway(runway1);
        EXPECT_EQ((unsigned) 1, airport->getFreeRunways().size());
    }

    TEST_F(AirportTest, getset_GateOccupied) {
        airport = new Airport();

        runway->setName("11R");
        runway1->setName("12R");

        plane = new Airplane;
        plane1 = new Airplane;

        plane->setAirport(airport);
        plane1->setAirport(airport);

        airport->setGates(5);

        //check gate occupied
        plane->toGate(1);
        EXPECT_TRUE(airport->getGateOccupied(1));
        EXPECT_FALSE(airport->getGateOccupied(0));
        plane->toGate(0);

        EXPECT_TRUE(airport->getGateOccupied(0));
        EXPECT_FALSE(airport->getGateOccupied(1));

        plane1->toGate(1);

        EXPECT_DEATH(airport->getGateOccupied(6), "Assertion.*failed");
        EXPECT_TRUE(airport->getGateOccupied(1));

        airport->setGateOccupied(1, false);
        EXPECT_FALSE(airport->getGateOccupied(1));
        airport->setGateOccupied(1, true);

    }

    TEST_F(AirportTest, getset_GatesOccupied) {
        airport = new Airport();

        vector<bool> boolvector;
        boolvector.push_back(true);
        boolvector.push_back(false);
        const vector<bool> finalevector = boolvector;

        airport->setGatesOccupied(finalevector);
        EXPECT_EQ(finalevector, airport->getGatesOccupied());
    }


    class RunwayTest : public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        RunwayTest() {

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
        Runway *runway;
    };

    TEST_F(RunwayTest, constructor) {
        airport = new Airport();
        runway = new Runway("Freddy", airport);
        EXPECT_EQ("Freddy", runway->getName());
        EXPECT_EQ(airport, runway->getAirport());
        EXPECT_FALSE(runway->isOccupied());
    }

    TEST_F(RunwayTest, getset_Airport) {
        airport = new Airport();
        runway = new Runway();
        runway->setAirport(airport);
        EXPECT_EQ(airport, runway->getAirport());
    }

    TEST_F(RunwayTest, getset_Name) {
        runway = new Runway();
        runway->setName("Primair");
        EXPECT_EQ("Primair", runway->getName());
    }

    TEST_F(RunwayTest, getset_Type) {
        runway = new Runway();
        runway->setType("Primair");
        EXPECT_EQ("Primair", runway->getType());
    }

    TEST_F(RunwayTest, getset_Length) {
        runway = new Runway();
        runway->setLength(500);
        EXPECT_EQ(500, runway->getLength());
    }

    TEST_F(RunwayTest, isOccupied) {
        runway = new Runway();

        EXPECT_FALSE(runway->isOccupied());
        runway->setOccupied(true);
        EXPECT_TRUE(runway->isOccupied());
        runway->setOccupied(false);
        EXPECT_FALSE(runway->isOccupied());
    }


    class HandlerTest : public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        HandlerTest() {

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
        Airplane *plane;
        Airplane *plane1;
        Airplane *plane2;
        Runway *runway;
        Runway *runway1;
        Runway *runway2;
        AirportHandler *D;
        vector<Airport *> airports;
        vector<Airplane *> airplanes;
    };

    TEST_F(HandlerTest, addremove_Airplane){
        D = new AirportHandler();

        plane = new Airplane();
        plane1 = new Airplane();

        //plane has no callsign
        EXPECT_DEATH(D->addAirplane(plane), "Assertion.*failed");

        //plane has a callsign
        plane->setCallsign("original");
        plane1->setCallsign("original");
        EXPECT_NO_FATAL_FAILURE(D->addAirplane(plane));

        //plane1's callsign is a duplicate
        EXPECT_DEATH(D->addAirplane(plane1), "Assertion.*failed");

        //plane's callsign is no duplicate
        plane1->setCallsign("different");
        EXPECT_NO_FATAL_FAILURE(D->addAirplane(plane1));

        //removeplane
        unsigned int numberAirplanes = (int) D->getAirplanes().size();
        EXPECT_NO_FATAL_FAILURE(D->removeAirplane("different"));
        EXPECT_DEATH(D->removeAirplane("different"), "Assertion.*failed");
        EXPECT_EQ((unsigned) numberAirplanes-1, D->getAirplanes().size());
    }

    TEST_F(HandlerTest, getset_Airplanes){
        D = new AirportHandler();

        plane = new Airplane();
        plane1 = new Airplane();

        // plane1 has no callsign
        plane->setCallsign("original");
        airplanes.push_back(plane);
        airplanes.push_back(plane1);
        const vector<Airplane *> myAirplaneVector = airplanes;
        EXPECT_DEATH(D->setAirplanes(myAirplaneVector), "Assertion.*failed");

        // plane1 has duplicate callsign
        plane1->setCallsign("original");
        airplanes.clear();
        airplanes.push_back(plane);
        airplanes.push_back(plane1);
        const vector<Airplane *> myAirplaneVector1 = airplanes;
        EXPECT_DEATH(D->setAirplanes(myAirplaneVector1), "Assertion.*failed");

        // plane1 has no duplicate callsign
        plane1->setCallsign("new");
        airplanes.clear();
        airplanes.push_back(plane);
        airplanes.push_back(plane1);
        const vector<Airplane *> myAirplaneVector2 = airplanes;
        EXPECT_NO_FATAL_FAILURE(D->setAirplanes(myAirplaneVector2));
        EXPECT_EQ(myAirplaneVector2, D->getAirplanes());
    }

    TEST_F(HandlerTest, addremove_Airport){
        D = new AirportHandler();

        airport = new Airport();
        airport1 = new Airport();

        //airport has no callsign
        EXPECT_DEATH(D->addAirport(airport), "Assertion.*failed");

        //airport has a callsign
        airport->setCallsign("original");
        EXPECT_NO_FATAL_FAILURE(D->addAirport(airport));

        //airport1's callsign is a duplicate
        airport1->setCallsign("original");
        EXPECT_DEATH(D->addAirport(airport1), "Assertion.*failed");

        //airport1's callsign is no duplicate
        airport->setCallsign("different");
        EXPECT_NO_FATAL_FAILURE(D->addAirport(airport1));

        //removeAirport
        int numberAirports = (int) D->getAirports().size();
        EXPECT_NO_FATAL_FAILURE(D->removeAirport("different"));
        EXPECT_DEATH(D->removeAirport("different"), "Assertion.*failed");
        EXPECT_EQ((unsigned) numberAirports-1, D->getAirports().size());
    }

    TEST_F(HandlerTest, getset_Airports){
        D = new AirportHandler();

        airport = new Airport();
        airport1 = new Airport();

        //airport1 has no callsign
        airport->setCallsign("original");
        airports.push_back(airport);
        airports.push_back(airport1);
        const vector<Airport *> myAirportVector = airports;
        EXPECT_DEATH(D->setAirports(myAirportVector), "Assertion.*failed");

        //airport1 has duplicate callsign
        airport1->setCallsign("original");
        airports.clear();
        airports.push_back(airport);
        airports.push_back(airport1);
        const vector<Airport *> myAirportVector1 = airports;
        EXPECT_DEATH(D->setAirports(myAirportVector1), "Assertion.*failed");

        //airport1 has no duplicate callsign
        airport1->setCallsign("new");
        airports.clear();
        airports.push_back(airport);
        airports.push_back(airport1);
        const vector<Airport *> myAirportVector2 = airports;
        EXPECT_NO_FATAL_FAILURE(D->setAirports(myAirportVector2));
        EXPECT_EQ(myAirportVector2, D->getAirports());
    }

    TEST_F(HandlerTest, getInfo){
        D = new AirportHandler();

        plane = new Airplane();
        airport = new Airport();

        airport->setName("ZavLucht");
        airport->setIata("Tito");
        airport->setCallsign("J400");
        airport->setGates(5);

        string str = "\nAirport:\t";
        str += "ZavLucht (Tito)\n->callsign:\tJ400\n->gates:\t";
        str += intToString(5) + "\n";
        str += "->runways:\t";
        str += intToString(0);
        str += "\n";

        plane->setNumber("7");
        plane->setModel("TufTuf");
        plane->setCallsign("J420");
        plane->setState("in brand");

        str += "\nAirplane:\t";
        str += "J420";
        str += " (";
        str += "7";
        str += ")\n";
        str += "->model:\t";
        str += "TufTuf";
        str += "\n";
        str += "->type:\t\n->engine:\t\n->size:\t\n";


        D->addAirplane(plane);
        D->addAirport(airport);

        EXPECT_EQ(str, D->getInfo());
    }




class CommunicationTests : public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    CommunicationTests() {

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
    Airplane *plane;
    Airplane *plane1;
    Airplane *plane2;
    Runway *runway;
    Runway *runway1;
    AirportHandler *D;
    TaxiRoute* taxi;
    TaxiRoute* taxi1;
    FlightPlan* flight;
};

TEST_F(CommunicationTests, taxiToRunway) {

    airport = new Airport;
    taxi = new TaxiRoute();

    string alpha = "runway1cross";
    taxi->addCrossing(alpha);
    alpha = "runway2cross";
    taxi->addCrossing(alpha);
    alpha = "runway3cross";
    taxi->addCrossing(alpha);
    alpha = "runway4cross";
    taxi->addCrossing(alpha);
    alpha = "runway5cross";
    taxi->addCrossing(alpha);
    alpha = "runway6cross";
    taxi->addCrossing(alpha);

    alpha = "alpha";
    taxi->addTaxiPoint(alpha);
    alpha = "bravo";
    taxi->addTaxiPoint(alpha);
    alpha = "charlie";
    taxi->addTaxiPoint(alpha);
    alpha = "delta";
    taxi->addTaxiPoint(alpha);
    alpha = "epsilon";
    taxi->addTaxiPoint(alpha);
    alpha = "franko";
    taxi->addTaxiPoint(alpha);


    runway = new Runway;
    runway->setType("asphalt");
    runway->setLength(2000);
    runway->setName("dezeRunway");
    runway->setTaxiRoute(taxi);
    plane = new Airplane();

    airport->addRunway(runway);
    airport->setGates(5);
    Runway* attemptrunway = runway;
    attemptrunway->setTaxiRoute(taxi);

    plane->setAirport(airport);
    plane->setEngine("propeller");
    plane->setSize("medium");
    plane->setCallsign("callsign");
    plane->setNumber("87");
    plane->setState("at Gate");
    plane->setModel("model");
    plane->toGate(3);
    cout << "ok" << endl;
    int i= 0;

    while (plane->getRunway()!= runway){
        i+=1;
        plane->taxiToRunway(runway);
        cout << i << endl;
    }

    cout << "i is nu " << i << endl;

    while (plane->getGate() != 3){
        i-=1;
        plane->taxiToGate(3);
        cout << i << endl;
    }

    closeFile();

}


    class XMLReaderTest : public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        XMLReaderTest() {

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
        Airplane *plane;
        Airplane *plane1;
        Airplane *plane2;
        Runway *runway;
        Runway *runway1;
        AirportHandler *D;
        TaxiRoute* taxi;
        TaxiRoute* taxi1;
        FlightPlan* flight;
    };


    TEST_F(XMLReaderTest, xmlInput) {
        D = new AirportHandler();
        airport = new Airport();
        runway = new Runway();
        runway1 = new Runway();
        plane = new Airplane();
        plane1 = new Airplane();
        plane2 = new Airplane();

        EXPECT_NO_FATAL_FAILURE(D->addXmlData("TestVolledigeLuchthaven.xml"));

        EXPECT_NO_FATAL_FAILURE(airport = D->getAirports()[0]);
        EXPECT_NO_FATAL_FAILURE(runway = airport->getRunways()[0]);
        EXPECT_NO_FATAL_FAILURE(runway1 = airport->getRunways()[1]);
        EXPECT_NO_FATAL_FAILURE(plane = D->getAirplanes()[0]);
        EXPECT_NO_FATAL_FAILURE(plane1 = D->getAirplanes()[1]);
        EXPECT_NO_FATAL_FAILURE(plane2 = D->getAirplanes()[2]);
        EXPECT_NO_FATAL_FAILURE(taxi = runway->getTaxiRoute());
        EXPECT_NO_FATAL_FAILURE(taxi1 = runway1->getTaxiRoute());
        EXPECT_NO_FATAL_FAILURE(flight = plane2->getFlightPlan());

        EXPECT_EQ(2,(signed)D->getAirports().size());
        EXPECT_EQ(3,(signed)D->getAirplanes().size());
        EXPECT_EQ(2,(signed)airport->getRunways().size());

        EXPECT_EQ("Antwerp International Airport",airport->getName());
        EXPECT_EQ(10,airport->getGates());
        EXPECT_EQ("ANR",airport->getIata());
        EXPECT_EQ("Antwerp Tower",airport->getCallsign());

        EXPECT_EQ("11R",runway->getName());
        EXPECT_EQ("ANR",runway->getAirport()->getIata());
        EXPECT_EQ(1000,runway->getLength());

        EXPECT_EQ("11L",runway1->getName());
        EXPECT_EQ("ANR",runway1->getAirport()->getIata());
        EXPECT_EQ(2500,runway1->getLength());

        EXPECT_EQ("N11842",plane->getNumber());
        EXPECT_EQ("Cessna 842",plane->getCallsign());
        EXPECT_EQ("Cessna 340",plane->getModel());
        EXPECT_EQ("Approaching",plane->getState());

        EXPECT_EQ("N11843",plane1->getNumber());
        EXPECT_EQ("Cessna 843",plane1->getCallsign());
        EXPECT_EQ("Cessna 340",plane1->getModel());
        EXPECT_EQ("Gate",plane1->getState());

        EXPECT_EQ("BAW466",plane2->getNumber());
        EXPECT_EQ("Speedbird 466",plane2->getCallsign());
        EXPECT_EQ("Boeing 737",plane2->getModel());
        EXPECT_EQ("broken",plane2->getState());
        EXPECT_EQ("jet",plane2->getEngine());
        EXPECT_EQ("medium",plane2->getSize());
        EXPECT_EQ(60,plane2->getPassengers());
        EXPECT_EQ("LCY",flight->getDestination());
        EXPECT_EQ(45,flight->getArrival());
        EXPECT_EQ(15,flight->getDeparture());
        EXPECT_EQ(1,flight->getInterval());
    }

    TEST_F(XMLReaderTest, GraphicalAirport2D) {
        D = new AirportHandler();
        D->addXmlData("TestVolledigeLuchthaven.xml");
        string iata = D->getAirports()[0]->getIata();
        D->getAirplanes()[0]->setAirport(D->getAirports()[0]);
        D->getAirplanes()[0]->toGate(6);
        D->GraphicalAirport2D(iata);
    }

    TEST_F(XMLReaderTest, xmlOutput) {
        D = new AirportHandler();
        EXPECT_DEATH(D->addXmlData("foutiefbestand.xml"), "Assertion.*failed");
        D->addXmlData("TestVolledigeLuchthaven.xml");

        D->fileOutput();

        ofstream *OutputTxt = getText();

        *OutputTxt << "End";

        OutputTxt->close();

        EXPECT_FALSE(OutputTxt->is_open());

        delete D;
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
