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
#include "Runway.h"
#include "Utils.h"

namespace
{

class XMLInput : public ::testing::Test
{
  protected:
    XMLInput()
    {
    }

    virtual void SetUp()
    {
        handler = new AirportHandler();
    }

    virtual void TearDown()
    {
        delete handler;
    }

    AirportHandler *handler;
};

TEST_F(XMLInput, addXmlData1)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(1));
    EXPECT_EQ(handler->getAirports().size(), unsigned(2));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthavenError.txt", "XMLTests/TestVolledigeLuchthavenErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData2)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven2.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
    EXPECT_EQ(handler->getAirports().size(), unsigned(2));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven2Error.txt", "XMLTests/TestVolledigeLuchthaven2ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData3)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven3.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(2));
    EXPECT_EQ(handler->getAirports().size(), unsigned(0));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven3Error.txt", "XMLTests/TestVolledigeLuchthaven3ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData4)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven4.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
    EXPECT_EQ(handler->getAirports().size(), unsigned(2));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven4Error.txt", "XMLTests/TestVolledigeLuchthaven4ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData6)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven6.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
    EXPECT_EQ(handler->getAirports().size(), unsigned(2));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven6Error.txt", "XMLTests/TestVolledigeLuchthaven6ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData7)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven7.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
    EXPECT_EQ(handler->getAirports().size(), unsigned(2));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven7Error.txt", "XMLTests/TestVolledigeLuchthaven7ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData9)
{

    // No airplanes
    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven9.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
    EXPECT_EQ(handler->getAirports().size(), unsigned(1));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven9Error.txt", "XMLTests/TestVolledigeLuchthaven9ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData11)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven11.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
    EXPECT_EQ(handler->getAirports().size(), unsigned(2));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven11Error.txt", "XMLTests/TestVolledigeLuchthaven11ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData15)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven15.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(1));
    EXPECT_EQ(handler->getAirports().size(), unsigned(2));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven15Error.txt", "XMLTests/TestVolledigeLuchthaven15ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData17)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven17.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
    EXPECT_EQ(handler->getAirports().size(), unsigned(1));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven17Error.txt", "XMLTests/TestVolledigeLuchthaven17ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData14)
{

    // Invalid element Name (AIRPLANE, AIRPORT, RUNWAY)
    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven14.xml"), partialImport);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
    EXPECT_EQ(handler->getAirports().size(), unsigned(2));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven14Error.txt", "XMLTests/TestVolledigeLuchthaven14ErrorResult.txt"));
}

// Invalid XML Structure

TEST_F(XMLInput, addXmlData12)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven12.xml"), importAborted);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
    EXPECT_EQ(handler->getAirports().size(), unsigned(0));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven12Error.txt", "XMLTests/TestVolledigeLuchthaven12ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData13)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven13.xml"), importAborted);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
    EXPECT_EQ(handler->getAirports().size(), unsigned(0));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven13Error.txt", "XMLTests/TestVolledigeLuchthaven13ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlDataInvalidFile)
{

    EXPECT_EQ(handler->addXmlData("XMLTests/NonExistentFile.xml"), importAborted);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
    EXPECT_EQ(handler->getAirports().size(), unsigned(0));
    EXPECT_TRUE(FileCompare("XMLTests/NonExistentFileError.txt", "XMLTests/NonExistentFileErrorResult.txt"));
}

// Succesfull XML

TEST_F(XMLInput, addXmlData16)
{

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
    EXPECT_EQ(handler->getAirplanes()[0]->getState(), incoming);
    EXPECT_EQ(handler->getAirplanes()[1]->getState(), gTechnicalCheck);

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

    FlightPlan *F0 = handler->getAirplanes()[0]->getFlightPlan();
    FlightPlan *F1 = handler->getAirplanes()[1]->getFlightPlan();

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

TEST_F(XMLInput, addXmlData10)
{

    // Airplanes, Runways and Airports in random order
    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven10.xml"), success);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(3));
    EXPECT_EQ(handler->getAirports().size(), unsigned(1));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven10Error.txt", "XMLTests/TestVolledigeLuchthaven10ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData8)
{

    // Normal input file
    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven8.xml"), success);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(2));
    EXPECT_EQ(handler->getAirports().size(), unsigned(1));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven8Error.txt", "XMLTests/TestVolledigeLuchthaven8ErrorResult.txt"));
}

TEST_F(XMLInput, addXmlData5)
{

    // No Airports, Runways or Airplanes
    EXPECT_EQ(handler->addXmlData("XMLTests/TestVolledigeLuchthaven5.xml"), success);
    EXPECT_EQ(handler->getAirplanes().size(), unsigned(0));
    EXPECT_EQ(handler->getAirports().size(), unsigned(0));
    EXPECT_TRUE(FileCompare("XMLTests/TestVolledigeLuchthaven5Error.txt", "XMLTests/TestVolledigeLuchthaven5ErrorResult.txt"));
}
} // namespace
