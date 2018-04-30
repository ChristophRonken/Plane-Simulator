//
// Created by oliviervh on 12.04.18.
//

#include "TaxiRoute.h"

TaxiRoute::TaxiRoute(){
    self = this;
}

void TaxiRoute::addTaxiPoint(const string &taxiPoint){
    TaxiRoute::taxiPoints.push_back(taxiPoint);
}

void TaxiRoute::addCrossing(const string &taxiCrossing){
    TaxiRoute::taxiCrossings.push_back(taxiCrossing);
}

vector<string> TaxiRoute::getTaxiPoints(){
    return TaxiRoute::taxiPoints;
}

vector<string> TaxiRoute::getTaxiCrossings(){
    return TaxiRoute::taxiCrossings;
}

bool TaxiRoute::propperlyInitialised() {
    return (this == TaxiRoute::self);
}

bool TaxiRoute::isValid() {
    if (propperlyInitialised()){
        return !TaxiRoute::taxiPoints.empty();
    }
    return false;
}
