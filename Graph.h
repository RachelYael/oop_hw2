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

    vector<Vertex> &getVertices();

    Graph(string vehicle, int inter, int center, int stad, int stopTime);

    Graph(Graph &&other) noexcept;

    bool checkIfVertexExistByName(string vname);

    void addVertex(Vertex newVertex);

    Vertex &getVertexByID(int vid);

    Vertex* getVertexByName(string vname);

    bool checkIfEdgeExistByName(string vfrom, string vto);

    void addEdgeByName(string fromVertex, string toVertex, int weight);

    void updateEdgeByName(string fromVertex, string toVertex, int newWeight);

    void printGraph();

    void insertUpdateData(string srcName, string destName, string weight);

    void printOutbound(string vname);

    void printInbound(string vname);

    int shortestPathTime(int s, int t, int visited[], string src, string dest);

    vector<string> reachableFromV(string startVertex); //using BFS

    Graph transposeGraph();

    void printUniExpress(string src, string dest);

private:
    int intercity = 15, central = 10, stad = 5;

    bool isIntercity(string vname);

    bool isCentral(string vname);

    unsigned int getVertexIndex(string vname);

};

#endif //HW2_GRAPH_H
