//
// Created by Rachel&Yael on 5/9/2022.
//

#ifndef HW2_VEHICLE_H
#define HW2_VEHICLE_H
#include <iostream>
using namespace std;

class Vehicle {
private:
    int defaultStopTime;
public:
    Vehicle();
    Vehicle(int defStopTime);
    virtual string toString();
    virtual int getDefStopTime();
    virtual void setDefStopTime(int newStopTime);
};


#endif //HW2_VEHICLE_H
