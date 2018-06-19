cmake_minimum_required(VERSION 3.6)
project(LuchthavenV1)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        src/LuchthavenMain.cpp
        src/Airport.cpp
        src/Airport.h
        src/Airplane.h
        src/Airplane.cpp
        xml/tinystr.cpp
        xml/tinystr.h
        xml/tinyxml.cpp
        xml/tinyxml.h
        xml/tinyxmlerror.cpp
        xml/tinyxmlparser.cpp
        src/RunwayClass.cpp
        src/RunwayClass.h
        src/MessageSystem.cpp
        src/MessageSystem.h
        src/AirportHandler.cpp
        src/AirportHandler.h
        src/DesignByContract.h
        src/FlightPlan.cpp
        src/FlightPlan.h
        src/TaxiRoute.cpp
        src/TaxiRoute.h
        src/Utils.cpp
        src/Utils.h
        )


# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        src/LuchthavenDebug.cpp
        src/Airport.cpp
        src/Airport.h
        src/Airplane.h
        src/Airplane.cpp
        xml/tinystr.cpp
        xml/tinystr.h
        xml/tinyxml.cpp
        xml/tinyxml.h
        xml/tinyxmlerror.cpp
        xml/tinyxmlparser.cpp
        src/RunwayClass.cpp
        src/RunwayClass.h
        src/MessageSystem.cpp
        src/MessageSystem.h
        src/AirportHandler.cpp
        src/AirportHandler.h
        gtest
        src/Utils.cpp
        src/Utils.h
        src/DesignByContract.h
        src/FlightPlan.cpp
        src/FlightPlan.h
        src/TaxiRoute.cpp
        src/InputTests.cpp
        src/OutputTests.cpp
        src/DomainTests.cpp
        src/TaxiRoute.h
        )


# Create RELEASE target
add_executable(LuchthavenV1 ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(LuchthavenV1_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(LuchthavenV1_debug gtest)
