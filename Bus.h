//
// Created by Rachel&Yael on 5/9/2022.
//

#ifndef HW2_BUS_H
#define HW2_BUS_H

#include "Vehicle.h"


class Bus : public Vehicle {
public:
    Bus() : Vehicle(BUS_TIME, "bus") {};
    Bus(int time) : Vehicle(time, "bus") {};

    string toString() override {
        return "Bus def time stop is: " + to_string(getDefStopTime());
    };
};


#endif //HW2_BUS_H
