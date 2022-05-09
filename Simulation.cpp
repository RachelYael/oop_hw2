//
// Created by Admin on 5/9/2022.
//

#include "Simulation.h"

void Simulation::test() {

    Vehicle* v = new Vehicle();
    Bus * b = new Bus();
    Tram * t = new Tram;
    Sprinter * s =new Sprinter;
    Rail *r = new Rail;

    vehicle.push_back(v);
    vehicle.push_back(b);
    vehicle.push_back(t);
    vehicle.push_back(s);
    vehicle.push_back(r);
    for(auto i= (vehicle).begin(); i !=(vehicle).end();i++){
        cout<<(*i)->toString()<<endl;
    }
}