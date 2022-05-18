//
// Created by Admin on 5/9/2022.
//

#ifndef HW2_RAIL_H
#define HW2_RAIL_H

#include "Vehicle.h"


class Rail : public Vehicle {
public:
    Rail() : Vehicle(RAIL_TIME, "rail") {};
    Rail(int time) : Vehicle(time, "rail") {};

    string toString() override {
        return "Rail def time stop is: " + to_string(getDefStopTime());
    };
};


#endif //HW2_RAIL_H
