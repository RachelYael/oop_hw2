//
// Created by Rachel&Yael on 5/9/2022.
//

#ifndef HW2_TRAM_H
#define HW2_TRAM_H

#include "Vehicle.h"


class Tram : public Vehicle {
public:
    Tram() : Vehicle(TRAM_TIME, "tram") {};
    Tram(int time) : Vehicle(time, "tram") {};
    string toString() override {
        return "Tram def time stop is: " + to_string(getDefStopTime());
    };
};


#endif //HW2_TRAM_H
