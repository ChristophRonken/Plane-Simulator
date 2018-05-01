//
// Created by oliviervh on 12.04.18.
//

#ifndef PSE_V1_TAXIROUTE_H
#define PSE_V1_TAXIROUTE_H
#include <vector>
#include <string>
#include "DesignByContract.h"

using namespace std;

class TaxiRoute {
    vector<string> taxipoints;
    vector<string> taxicrossings;
    TaxiRoute* self;

public:

    /**
     * Constructor
     */
    TaxiRoute();

    /**
     * Adds a taxipoint to the list
     * Postconditions: TaxiRoute::getTaxiPoints()[TaxiRoute::getTaxiPoints().size()-1] == taxipoint
     * @param taxipoint
     */
    void addTaxiPoint(const string &taxiPoint);

    /**
     * Adds a crossing to the list
     * PostConditions: TaxiRoute::getTaxiCrossings()[TaxiRoute::getTaxiCrossings().size()-1] == crossing
     * @param crossing
     */
    void addTaxiCrossing(const string &taxiCrossing);

    /**
     * Returns the list of taxi points
     * @return
     */
    vector<string> getTaxiPoints();

    /**
     * returns the list of taxi crossings
     * @return
     */
    vector<string> getTaxiCrossings();

    /**
     * Checks if the TaxiRoute was propperly initialised
     * @return
     */
    bool properlyInitialised();

    /**
     * Checks if the taxiRoute has at least 1 taxipoint and is propperly initialised
     * @return
     */
    bool isValid();


};


#endif //PSE_V1_TAXIROUTE_H
