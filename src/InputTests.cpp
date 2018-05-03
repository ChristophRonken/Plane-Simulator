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
#include "Utils.h"

namespace {

    class XMLInput : public ::testing::Test{
    protected:
        XMLInput() {

        }

        virtual void SetUp() {
            handler = new AirportHandler();
        }

        virtual void TearDown() {
            delete handler;

        }

        AirportHandler* handler;

    };

    TEST_F(XMLInput, addXmlData1 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(1));
        EXPECT_EQ(handler->getAirports().size(), unsigned(2));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthavenError.txt", "XMLTests/TestVolledigeLuchthavenErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData2 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven2.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
        EXPECT_EQ(handler->getAirports().size(), unsigned(2));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven2Error.txt", "XMLTests/TestVolledigeLuchthaven2ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData3 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven3.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(2));
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven3Error.txt", "XMLTests/TestVolledigeLuchthaven3ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData4 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven4.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
        EXPECT_EQ(handler->getAirports().size(), unsigned(2));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven4Error.txt", "XMLTests/TestVolledigeLuchthaven4ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData6 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven6.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_EQ(handler->getAirports().size(), unsigned(2));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven6Error.txt", "XMLTests/TestVolledigeLuchthaven6ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData7 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven7.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_EQ(handler->getAirports().size(), unsigned(2));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven7Error.txt", "XMLTests/TestVolledigeLuchthaven7ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData9 ){

        // No airplanes
        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven9.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_EQ(handler->getAirports().size(), unsigned(1));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven9Error.txt", "XMLTests/TestVolledigeLuchthaven9ErrorResult.txt"));

    }

    TEST_F(XMLInput, addXmlData11 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven11.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
        EXPECT_EQ(handler->getAirports().size(), unsigned(2));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven11Error.txt", "XMLTests/TestVolledigeLuchthaven11ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData15 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven15.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(1));
        EXPECT_EQ(handler->getAirports().size(), unsigned(2));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven15Error.txt", "XMLTests/TestVolledigeLuchthaven15ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData17 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven17.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
        EXPECT_EQ(handler->getAirports().size(), unsigned(1));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven17Error.txt", "XMLTests/TestVolledigeLuchthaven17ErrorResult.txt"));

    }

    TEST_F(XMLInput, addXmlData14 ){

        // Invalid element Name (AIRPLANE, AIRPORT, RUNWAY)
        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven14.xml"), partialImport);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
        EXPECT_EQ(handler->getAirports().size(), unsigned(2));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven14Error.txt", "XMLTests/TestVolledigeLuchthaven14ErrorResult.txt"));


    }


    // Invalid XML Structure

    TEST_F(XMLInput, addXmlData12 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven12.xml"), importAborted);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven12Error.txt", "XMLTests/TestVolledigeLuchthaven12ErrorResult.txt"));

    }

    TEST_F(XMLInput, addXmlData13 ){

        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven13.xml"), importAborted);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven13Error.txt", "XMLTests/TestVolledigeLuchthaven13ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlDataInvalidFile){

        EXPECT_EQ(handler->addXmlData("XMLTests/NonExistentFile.xml"), importAborted);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_TRUE(FileCompare("XMLTests/NonExistentFileError.txt", "XMLTests/NonExistentFileErrorResult.txt"));

    }


    // Succesfull XML

    TEST_F(XMLInput, addXmlData16 ){

        // Only Airplanes
        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven16.xml"), success);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(2));
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven16Error.txt", "XMLTests/TestVolledigeLuchthaven16ErrorResult.txt"));

        // Name right
        EXPECT_EQ(handler->getAirplanes()[0]->getNumber(), "BAW466");
        EXPECT_EQ(handler->getAirplanes()[1]->getNumber(), "BAW467");

        // Type right
        EXPECT_EQ(handler->getAirplanes()[0]->getType(), "airline");
        EXPECT_EQ(handler->getAirplanes()[1]->getType(), "private");

        // Callsign right
        EXPECT_EQ(handler->getAirplanes()[0]->getCallsign(), "Speedbird 466");
        EXPECT_EQ(handler->getAirplanes()[1]->getCallsign(), "Speedbird 467");

        // Engine right
        EXPECT_EQ(handler->getAirplanes()[0]->getEngine(), "jet");
        EXPECT_EQ(handler->getAirplanes()[1]->getEngine(), "propeller");

        // Model right
        EXPECT_EQ(handler->getAirplanes()[0]->getModel(), "Boeing 737");
        EXPECT_EQ(handler->getAirplanes()[1]->getModel(), "Boeing 737");

        // Status right
        EXPECT_EQ(handler->getAirplanes()[0]->getState(), "Approaching");
        EXPECT_EQ(handler->getAirplanes()[1]->getState(), "Gate");

        // Size right
        EXPECT_EQ(handler->getAirplanes()[0]->getSize(), "medium");
        EXPECT_EQ(handler->getAirplanes()[1]->getSize(), "small");

        // Passengers right
        EXPECT_EQ(handler->getAirplanes()[0]->getPassengers(), 60);
        EXPECT_EQ(handler->getAirplanes()[1]->getPassengers(), 60);
        EXPECT_EQ(handler->getAirplanes()[0]->getPassengerCapacity(), 60);
        EXPECT_EQ(handler->getAirplanes()[1]->getPassengerCapacity(), 60);

        // Fuel right
        EXPECT_EQ(handler->getAirplanes()[0]->getFuel(), 100000);
        EXPECT_EQ(handler->getAirplanes()[1]->getFuel(), 100000);
        EXPECT_EQ(handler->getAirplanes()[0]->getFuelCapacity(), 100000);
        EXPECT_EQ(handler->getAirplanes()[1]->getFuelCapacity(), 100000);

        // Unique flightplan
        EXPECT_NE(handler->getAirplanes()[0]->getFlightPlan(), handler->getAirplanes()[1]->getFlightPlan());

        FlightPlan* F0 = handler->getAirplanes()[0]->getFlightPlan();
        FlightPlan* F1 = handler->getAirplanes()[1]->getFlightPlan();


        // Flightplan right
        EXPECT_EQ(F0->getDestination(), "LCY");
        EXPECT_EQ(F0->getDeparture(), 15);
        EXPECT_EQ(F0->getArrival(), 45);
        EXPECT_EQ(F0->getInterval(), 1);

        EXPECT_EQ(F1->getDestination(), "LCY2");
        EXPECT_EQ(F1->getDeparture(), 20);
        EXPECT_EQ(F1->getArrival(), 40);
        EXPECT_EQ(F1->getInterval(), 2);

    }

    TEST_F(XMLInput, addXmlData10 ){

        // Airplanes, Runways and Airports in random order
        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven10.xml"), success);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
        EXPECT_EQ(handler->getAirports().size(), unsigned(1));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven10Error.txt", "XMLTests/TestVolledigeLuchthaven10ErrorResult.txt"));

    }

    TEST_F(XMLInput, addXmlData8 ){

        // Normal input file
        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven8.xml"), success);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(2));
        EXPECT_EQ(handler->getAirports().size(), unsigned(1));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven8Error.txt", "XMLTests/TestVolledigeLuchthaven8ErrorResult.txt"));


    }

    TEST_F(XMLInput, addXmlData5 ){

        // No Airports, Runways or Airplanes
        EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven5.xml"), success);
        EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven5Error.txt", "XMLTests/TestVolledigeLuchthaven5ErrorResult.txt"));


    }

    class AirportHandlerFunctionInput : public ::testing::Test{
    protected:
        AirportHandlerFunctionInput() {

        }

        virtual void SetUp() {
            handler = new AirportHandler();
            planeA = new Airplane();
            planeB = new Airplane();
            airportA = new Airport();
            airportB = new Airport();
        }

        virtual void TearDown() {
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

    TEST_F(AirportHandlerFunctionInput, Constructor){
        handlerNoInit = new AirportHandler();
        EXPECT_TRUE(handlerNoInit->propperlyInitialised());

    }

    TEST_F(AirportHandlerFunctionInput, AddAirport){

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

    TEST_F(AirportHandlerFunctionInput, RemoveAirplane){

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

    TEST_F(AirportHandlerFunctionInput, AddAirplane){

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

    TEST_F(AirportHandlerFunctionInput, RemoveAirport){

        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_NO_FATAL_FAILURE(handler->addXmlData("XMLTests/TestVolledigeLuchthaven8.xml"));

        EXPECT_EQ(handler->getAirports().size(), unsigned(1));
        EXPECT_NO_FATAL_FAILURE(handler->removeAirport("ANR"));
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));
        EXPECT_DEATH(handler->removeAirport("ANR"), "Assertion.*failed");
        EXPECT_EQ(handler->getAirports().size(), unsigned(0));


    }

    TEST_F(AirportHandlerFunctionInput, SetAirplanes){

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

    TEST_F(AirportHandlerFunctionInput, SetAirports){

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
        TaxiRoute* taxiRoute;
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

    TEST_F(AirplaneInput, taxiToRunway) {
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

        EXPECT_DEATH(airplane->taxiToRunway(), "correct state");
        airplane->setCurrentTask("going to runway");
        EXPECT_DEATH(airplane->taxiToRunway();, "destination runway was set");
        airplane->setAttemptRunway(runway1);
        EXPECT_DEATH(airplane->taxiToRunway();, "");
        runway1->setTaxiRoute(taxiRoute);
        EXPECT_NO_FATAL_FAILURE(airplane->taxiToRunway());
    }


}
