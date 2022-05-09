//
// Created by Admin on 5/9/2022.
//

#include "Tram.h"
Tram::Tram():Vehicle(TIME){}

string Tram::toString(){
    return "I am Tram def time stop is: "+ to_string(getDefStopTime());
}