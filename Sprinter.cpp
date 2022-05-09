//
// Created by Admin on 5/9/2022.
//

#include "Sprinter.h"
Sprinter::Sprinter():Vehicle(TIME){}

string Sprinter::toString(){
    return "I am Sprinter def time stop is: "+ to_string(getDefStopTime());
}