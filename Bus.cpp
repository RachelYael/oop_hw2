//
// Created by Admin on 5/9/2022.
//

#include "Bus.h"
Bus::Bus():Vehicle(TIME){

}

string Bus::toString(){
    return "I am Bus def time stop is: "+ to_string(getDefStopTime());
}