//
// Created by oliviervh on 12.04.18.
//

#ifndef PSE_V1_TAXIROUTE_H
#define PSE_V1_TAXIROUTE_H
#include <vector>
#include <string>

using namespace std;

class TaxiRoute {
    vector<string> taxipoints;
    vector<string> taxicrossings;
    TaxiRoute* self;

public:

    TaxiRoute();

    void addTaxiPoint(string taxipoint);

    void addCrossing(string crossing);

    vector<string> getTaxiPoints();
    vector<string> getTaxiCrossings();

    bool propperlyInitialised();

    bool isValid();


};


#endif //PSE_V1_TAXIROUTE_H
