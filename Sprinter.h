//
// Created by Admin on 5/9/2022.
//

#ifndef HW2_SPRINTER_H
#define HW2_SPRINTER_H

#include "Vehicle.h"


class Sprinter : public Vehicle {
public:
    Sprinter() : Vehicle(SPRINTER_TIME, "sprinter") {};
    Sprinter(int time) : Vehicle(time, "sprinter") {};

    string toString() override {
        return "Sprinter def time stop is: " + to_string(getDefStopTime());
    };
};


#endif //HW2_SPRINTER_H
