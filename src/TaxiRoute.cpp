//
// Created by oliviervh on 12.04.18.
//

#include "TaxiRoute.h"

TaxiRoute::TaxiRoute(){
    TaxiRoute::self = this;
}

void TaxiRoute::addTaxiPoint(const string &taxipoint){
    TaxiRoute::taxipoints.push_back(taxipoint);
    ENSURE(TaxiRoute::getTaxiPoints()[TaxiRoute::getTaxiPoints().size()-1] == taxipoint, "" );
}

void TaxiRoute::addTaxiCrossing(const string &crossing){
    TaxiRoute::taxicrossings.push_back(crossing);
    ENSURE(TaxiRoute::getTaxiCrossings()[TaxiRoute::getTaxiCrossings().size()-1] == crossing, "" );
}

vector<string> TaxiRoute::getTaxiPoints(){
    return TaxiRoute::taxipoints;
}

vector<string> TaxiRoute::getTaxiCrossings(){
    return TaxiRoute::taxicrossings;
}

bool TaxiRoute::properlyInitialised() {
    return (this == TaxiRoute::self);
}

bool TaxiRoute::isValid() {
    if (TaxiRoute::properlyInitialised()){
        return !TaxiRoute::taxipoints.empty();

    }
    return false;
}
