//
// Created by Admin on 5/9/2022.
//

#include "Rail.h"
Rail::Rail():Vehicle(TIME){}

string Rail::toString(){
    return "I am Rail def time stop is: "+ to_string(getDefStopTime());
}