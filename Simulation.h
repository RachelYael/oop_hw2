//
// Created by Admin on 5/9/2022.
//

#ifndef HW2_SIMULATION_H
#define HW2_SIMULATION_H
#include "Vehicle.h"
#include "Bus.h"
#include "Sprinter.h"
#include "Tram.h"
#include "Rail.h"

#include "Graph.h"

#include <vector>

class Simulation {
private:
    vector<Vehicle *> vehicle;
public:
    Simulation();

    void test();
   void GraphTest();
};


#endif //HW2_SIMULATION_H
