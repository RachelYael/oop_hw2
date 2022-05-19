//
// Created by rache on 14/05/2022.
//

#ifndef HW2_GRAPHHELPER_H
#define HW2_GRAPHHELPER_H

#include <iostream>
#include <list>

using namespace std;


class Edge {
public:
    string sourceName;
    string destName;
    int weight;

    Edge() {}

    Edge(string sourceName, string destName, int w) {
        this->sourceName = sourceName;
        this->destName = destName;
        this->weight = w;
    }

    void setEdgeVal(string sourceName, string destName, int w) {
        this->sourceName = sourceName;
        this->destName = destName;
        weight = w;
    }

    void setWeight(int w) {
        weight = w;
    }

    const string &getDestName() const {
        return destName;
    }
    const string &getSrcName() const {
        return sourceName;
    }
    int getWeight() const {
        return weight;
    }

};

class Vertex {
public:
    int stationId;
    string stationName;
    int transitionTime;

    list<Edge> edgeList;

    Vertex() {
        this->stationId = 0;
        this->stationName = "";
    }
    Vertex(string name, int transitionTime) {
        this->stationName = name;
        this->transitionTime = transitionTime;
    }

    int getStationId() const {
        return stationId;
    }

    void setStationId(int stationId) {
        stationId = stationId;
    }

    string getStationName() const {
        return stationName;
    }

    void setStationName(string stationName) {
        stationName = stationName;
    }

    list<Edge>& getEdgeList() {
        return edgeList;
    }

    void printEdgeList(){
        if(edgeList.empty()) {
            return;
        }
        for (const Edge &e: edgeList) {
            cout << "(" << e.sourceName << ", " << e.destName << ", " << e.weight << ")"<< endl;
        }
    }
};


#endif //HW2_GRAPHHELPER_H
