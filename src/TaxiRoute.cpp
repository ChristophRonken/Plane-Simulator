//
// Created by oliviervh on 12.04.18.
//

#include "TaxiRoute.h"

TaxiRoute::TaxiRoute(){
    self = this;
}

void TaxiRoute::addTaxiPoint(const string &taxipoint){
    TaxiRoute::taxipoints.push_back(taxipoint);
}

void TaxiRoute::addCrossing(const string &crossing){
    TaxiRoute::taxicrossings.push_back(crossing);
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
    if (propperlyInitialised()){
        return !TaxiRoute::taxipoints.empty();
    }
    return false;
}
