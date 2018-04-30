//
// Created by oliviervh on 12.04.18.
//

#ifndef PSE_V1_TAXIROUTE_H
#define PSE_V1_TAXIROUTE_H
#include <vector>
#include <string>

using namespace std;

class TaxiRoute {
    TaxiRoute* self;

    vector<string> taxipoints;
    vector<string> taxicrossings;


public:

    TaxiRoute();

    /**
     * Adds a new taxipoint
     * @param taxipoint
     */
    void addTaxiPoint(const string &taxipoint);

    /**
     * Adds a new taxicrossing
     * @param crossing
     */
    void addCrossing(const string &crossing);

    /**
     * Get a vector with all taxipoints
     * @return taxipoints
     */
    vector<string> getTaxiPoints();

    /**
     * Get a vector with all taxicrossings
     * @return taxicrossings
     */
    vector<string> getTaxiCrossings();

    /**
     * Check if the TaxiRoute is properly initialised
     * @return bool
     */
    bool propperlyInitialised();

    /**
     * Check if the values of the TaxiRoute are propperly initialised
     * @return bool
     */
    bool isValid();


};


#endif //PSE_V1_TAXIROUTE_H
