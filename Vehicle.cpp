//
// Created by Admin on 5/9/2022.
//

#include "Vehicle.h"
Vehicle::Vehicle(){
    defaultStopTime =0; // maybe -1? להדגיש שאין ערך
}
Vehicle::Vehicle(int defStopTime){
    this->defaultStopTime = defStopTime;
}

string Vehicle::toString(){
    return "I am a Vehicle def stop time is: "+ to_string(defaultStopTime);
}

int Vehicle::getDefStopTime(){
    return this->defaultStopTime;
}
void Vehicle::setDefStopTime(int newStopTime){
    this->defaultStopTime = newStopTime;
}