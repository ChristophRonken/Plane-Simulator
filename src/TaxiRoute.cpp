//
// Created by oliviervh on 12.04.18.
//

#include "TaxiRoute.h"

TaxiRoute::TaxiRoute(){
    self = this;
}

void TaxiRoute::addTaxiPoint(string taxipoint){
    TaxiRoute::taxipoints.push_back(taxipoint);
    ENSURE(TaxiRoute::getTaxiPoints()[TaxiRoute::getTaxiPoints().size()-1] == taxipoint, "" );
}

void TaxiRoute::addCrossing(string crossing){
    TaxiRoute::taxicrossings.push_back(crossing);
    ENSURE(TaxiRoute::getTaxiCrossings()[TaxiRoute::getTaxiCrossings().size()-1] == crossing, "" );
}

vector<string> TaxiRoute::getTaxiPoints(){
    return TaxiRoute::taxipoints;
}

vector<string> TaxiRoute::getTaxiCrossings(){
    return TaxiRoute::taxicrossings;
}

bool TaxiRoute::propperlyInitialised() {
    return (this == TaxiRoute::self);
}

bool TaxiRoute::isValid() {
    if (TaxiRoute::propperlyInitialised()){
        return !TaxiRoute::taxipoints.empty();

    }
    return false;
}
