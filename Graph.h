//
// Created by Admin on 5/9/2022.
//

#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H

#include <vector>
#include <valarray>
#include "GraphHelper.h"
#include "Vehicle.h"

class Graph {
public:
    vector<Vertex> vertices;
    Vehicle *vehicle;

    explicit Graph(string vechile);
    Graph(string vechile, int inter, int center, int stad);

    bool checkIfVertexExistByID(int vid);

    bool checkIfVertexExistByName(string vname);

    void addVertex(Vertex newVertex);

//    Vertex getVertexByID(int vid);
    Vertex getVertexByName(string vname);

//    bool checkIfEdgeExistByID(int fromVertex, int toVertex);
    bool checkIfEdgeExistByName(string vfrom, string vto);

    void updateVertex(int oldVID, string vname);

//    void addEdgeByID(int fromVertex, int toVertex, int weight);
    void addEdgeByName(string fromVertex, string toVertex, int weight);

    void updateEdgeByName(string fromVertex, string toVertex, int newWeight);

    void deleteEdgeByID(int fromVertex, int toVertex);

    void deleteVertexByID(int vid);

    void printAllNeigborsByName(string vname);

    void printGraph();

    void insertUpdateData(string srcName, string destName, string weight);

    void printOutbound(string vname);

    void printInbound(string vname);

    void printAllVertexSources(string vname);

    void shortestPathTime(string src, string target);

    int getEdgeWeight(string src, string target);

private:
    int intercity=15, central=10, stad=5;
    bool isIntercity(string vname);

    bool isCentral(string vname);

    unsigned int getVertexIndex(string vname);

    int minDist(const long distance[], const bool Tset[]) const;

    int getEdgeWeight();

};

#endif //HW2_GRAPH_H
