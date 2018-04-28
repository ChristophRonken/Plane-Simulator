//
// Created by oliviervh on 12.04.18.
//

#include "TaxiRoute.h"

TaxiRoute::TaxiRoute(){
    self = this;
}

void TaxiRoute::addTaxiPoint(string taxipoint){
    TaxiRoute::taxipoints.push_back(taxipoint);
}

void TaxiRoute::addCrossing(string crossing){
    TaxiRoute::taxicrossings.push_back(crossing);
}

vector<string> TaxiRoute::getTaxiPoints(){
    return TaxiRoute::taxipoints;
}

vector<string> TaxiRoute::getTaxiCrossings(){
    return TaxiRoute::taxicrossings;
}

bool TaxiRoute::propperlyInitialized() {
    return (this == self);
}

bool TaxiRoute::isValid() {
    if (propperlyInitialized()){
        return !taxipoints.empty();

    }
    return false;
}
