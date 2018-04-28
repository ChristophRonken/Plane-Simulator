//
// Created by oliviervh on 01.03.18.
//

#include <vector>

#include "AirportHandler.h"

using namespace std;


int main(int argc, char **argv){

    AirportHandler* D = new AirportHandler();

    if (D->addXmlData("LuchthavenV1.xml") != 0) { ;

        D->fileOutput();

        D->runSimulation("ANR");

    }

    delete D;


    return 0;
}