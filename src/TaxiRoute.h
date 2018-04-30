// author: Ronken Christoph & Van Hautte Olivier
// date: 02/05/2018
// version: 2.0

#ifndef PSE_V1_TAXIROUTE_H
#define PSE_V1_TAXIROUTE_H
#include <vector>
#include <string>

using namespace std;

class TaxiRoute {
    TaxiRoute* self;

    vector<string> taxiPoints;
    vector<string> taxiCrossings;


public:

    TaxiRoute();

    /**
     * Adds a new taxiPoint
     * @param taxiPoint
     */
    void addTaxiPoint(const string &taxiPoint);

    /**
     * Adds a new taxiCrossing
     * @param taxiCrossing
     */
    void addCrossing(const string &taxiCrossing);

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
