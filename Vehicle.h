//
// Created by Rachel&Yael on 5/9/2022.
//

#ifndef HW2_VEHICLE_H
#define HW2_VEHICLE_H
#include <iostream>

#define BUS_TIME 1
#define TRAM_TIME 2
#define SPRINTER_TIME 3
#define RAIL_TIME 5
using namespace std;

class Vehicle {
private:
    int defaultStopTime;
    string type;
public:
    const string &getType() const;
    Vehicle();
    explicit Vehicle(int defStopTime, string type);
    virtual string toString();
    virtual int getDefStopTime();
    virtual void setDefStopTime(int newStopTime);
};


#endif //HW2_VEHICLE_H
