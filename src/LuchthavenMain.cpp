//
// Created by oliviervh on 01.03.18.
//

#include <vector>

#include "AirportHandler.h"

using namespace std;


int main(int argc, char **argv){

    AirportHandler* D = new AirportHandler();

    if (D->addXmlData("TestVolledigeLuchthaven.xml") != 0) { ;

        D->fileOutput();

        cout << D->getAirplanes().size();

        D->runSimulation("ANR");

    }

    delete D;


    return 0;
}