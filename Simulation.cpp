//
// Created by Admin on 5/9/2022.
//

#include "Simulation.h"
Simulation::Simulation() {
    cout << "hello" << endl;

}

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

//void Simulation::GraphTest(){
//    Graph  g = Graph();
//    g.addVertex( Vertex(1,"Slomi"));
//    g.addVertex( Vertex(2,"KOKO"));
//    g.addEdgeByID(1,2,80);
//    g.printGraph();
//
//    bool check = g.checkIfEdgeExistByID(1, 7);
//    if (check == true) {
//        cout << "Vertices are Neigbors (Edge exist)";
//    } else {
//        cout << "Vertices are NOT Neigbors (Edge does NOT exist)";
//    }
//
//
//}
