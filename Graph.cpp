//
// Created by Admin on 5/9/2022.
//

#include "Graph.h"
#include "Bus.h"
#include "Rail.h"
#include "Sprinter.h"
#include "Tram.h"

Graph::Graph(string vechile) {
    if (vechile == "bus") {
        this->vehicle = new Bus();
    } else if (vechile == "rail") {
        this->vehicle = new Rail();
    } else if (vechile == "sprinter") {
        this->vehicle = new Sprinter();
    } else if(vechile == "tram"){
        this->vehicle = new Tram();
    } else {
        this->vehicle = new Vehicle();
    }
}

Graph::Graph(string vehicle, int inter, int center, int stad, int stopTime) {
    if (vehicle == "bus") {
        this->vehicle = new Bus(stopTime);
    } else if (vehicle == "rail") {
        this->vehicle = new Rail(stopTime);
    } else if (vehicle == "sprinter") {
        this->vehicle = new Sprinter(stopTime);
    } else {
        this->vehicle = new Tram(stopTime);
    }
    this->intercity = inter;
    this->central = center;
    this->stad = stad;
}

Graph::Graph(Graph &&other) noexcept {
    vertices = other.vertices;
    vehicle = other.vehicle;
}

bool Graph::checkIfVertexExistByName(string vname) {
    for (unsigned int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStationName().compare(vname) == 0) {
            return true;
        }
    }
    return false;
}

void Graph::addVertex(Vertex newVertex) {
    bool check = checkIfVertexExistByName(newVertex.getStationName());
    if (!check) {
        vertices.push_back(newVertex);
    }
}

Vertex& Graph::getVertexByID(int vid) {
    return vertices[vid];
}

void Graph::addEdgeByName(string fromVertex, string toVertex, int weight) {
    bool check = checkIfEdgeExistByName(fromVertex, toVertex);
    if (!check) {
        for (Vertex &v: vertices) {
            if (v.getStationName() == fromVertex) {
                Edge e(fromVertex, toVertex, weight);
                v.edgeList.push_back(e);
            }
        }
    } else {
        updateEdgeByName(fromVertex, toVertex, weight);
    }
}

bool Graph::checkIfEdgeExistByName(string vfrom, string vto) {
    for (Vertex &v: vertices) {
        if (v.getStationName() == vfrom) {
            for (Edge &e: v.getEdgeList()) {
                if (e.getDestName() == vto) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Graph::updateEdgeByName(string fromVertex, string toVertex, int newWeight) {
    for (Vertex &v: vertices) {
        if (v.getStationName() == fromVertex) {
            for (Edge &e: v.getEdgeList()) {
                if (e.getDestName() == toVertex) {
                    if (newWeight < e.getWeight()) {
                        e.setWeight(newWeight);
                    }
                }
            }
        }
    }
}

void Graph::printGraph() {
    cout << this->vehicle->getType() << ":" << endl;
    if(vertices.empty()) {
        cout << "this network is empty." << endl;
    }
    for (Vertex &v: vertices) {
        v.printEdgeList();
    }
}


void Graph::insertUpdateData(string srcName, string destName, string weight) {
    // check if vertices already exist
    bool isExist = checkIfVertexExistByName(srcName);
    if (!isExist) {
        if (isIntercity(srcName)) {
            addVertex(Vertex(srcName, intercity));
        } else if (isCentral(srcName)) {
            addVertex(Vertex(srcName, central));
        } else {
            addVertex(Vertex(srcName, stad));
        }
    }

    isExist = checkIfVertexExistByName(destName);
    if (!isExist) {
        if (isIntercity(destName)) {
            addVertex(Vertex(destName, intercity));
        } else if (isCentral(destName)) {
            addVertex(Vertex(destName, central));
        } else {
            addVertex(Vertex(destName, stad));
        }
    }

    addEdgeByName(srcName, destName, stoi(weight));
}

bool Graph::isIntercity(string vname) {
    string s = vname.substr(0, 2);
    return s == "IC";
}

bool Graph::isCentral(string vname) {
    string s = vname.substr(0, 2);
    return s == "CS";
}

Vertex* Graph::getVertexByName(string vname) {
    for(Vertex &v: vertices) {
        if(v.getStationName() == vname) {
            return &v;
        }
    }
    return nullptr;
}

void Graph::printOutbound(string vname) {
    cout << vehicle->getType() << ": ";
    int vertexIndex = getVertexIndex(vname);
    if (vertexIndex == -1) {
        cout << vname << " does not exist in the current network." << endl;
        return;
    }
    if(vertices[vertexIndex].getEdgeList().empty()) {
        cout << "no outbound travel" << endl;
        return;
    }
    vector<string> r = reachableFromV(vname);
    for(string &s: r) {
        cout << s << "\t";
    }
    cout << endl;
}

void Graph::printInbound(string vname) {
    Graph transposed(move(transposeGraph()));
    transposed.printOutbound(vname);
}

int Graph::shortestPathTime(int s, int t, int visited[], string src, string dest) {
    if (s == t) {
        return 0;
    }

    visited[s] = 1;
    long int ans = INTMAX_MAX;
    for(Edge &e: vertices[s].getEdgeList()){
        if(visited[getVertexIndex(e.getDestName())] == 0) {
            long int curr = shortestPathTime(getVertexIndex(e.getDestName()), t, visited, src, dest);
            if(curr < INTMAX_MAX) {
                if(e.getDestName() == src || e.getDestName() == dest) {
                    ans = min(ans, e.getWeight() + curr);
                } else {
                    ans = min(ans, e.getWeight() + curr+ this->vehicle->getDefStopTime());
                }
            }
        }
    }

    visited[s] = 0;
    return ans;
}

unsigned int Graph::getVertexIndex(string vname) {
    for (unsigned int i = 0; i < vertices.size(); i++) {
        if (vertices[i].getStationName() == vname) {
            return i;
        }
    }
    return -1;
}

vector<string> Graph::reachableFromV(string startVertex) {
    vector<string> reachable;
    int vertexIndex = getVertexIndex(startVertex);
    int numVertices = vertices.size();
    vector<bool> visited;
    visited.resize(numVertices, false);

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[vertexIndex] = true;
    queue.push_back(vertexIndex);

    while (!queue.empty()) {
        // Dequeue a vertex from queue and print it
        vertexIndex = queue.front();
        if(getVertexByID(vertexIndex).getStationName() != startVertex) {
            reachable.push_back(getVertexByID(vertexIndex).getStationName());
        }
        queue.pop_front();


        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it

        list<Edge> listV = vertices[vertexIndex].getEdgeList();
        for (Edge &e: listV) {
            vertexIndex = getVertexIndex(e.getDestName());
            if (!visited[vertexIndex]) {
                visited[vertexIndex] = true;
                queue.push_back(vertexIndex);
            }
        }
    }
    return reachable;
}


Graph Graph::transposeGraph() {
    Graph transpose(this->vehicle->getType());
    for(Vertex &v: this->vertices){
        transpose.addVertex(Vertex(v.getStationName(), 0));
    }

    for(Vertex &v: this->vertices){
        for(Edge &e: v.getEdgeList()) {
            transpose.addEdgeByName(e.getDestName(), e.getSrcName(), e.getWeight());
        }
    }
    return transpose;
}

void Graph::printUniExpress(string src, string dest) {
    cout << vehicle->getType() << ": ";
    int srcIndex = getVertexIndex(src);
    int destIndex = getVertexIndex(dest);
    if(srcIndex == -1) { // check if source node exists
        cout << src << " does not exist in the current network." << endl;
        return;
    }
    if(destIndex == -1) {  // check if destination node exists
        cout << dest << " does not exist in the current network." << endl;
        return;
    }

    // check if destination nose is reachable from source node
    vector<string> r = reachableFromV(src);
    if(!count(r.begin(), r.end(), dest)){
        cout << "route unavailable" << endl;
        return;
    }

    // fins the shortest path between 2 nodes
    int visited[vertices.size()];
    for (unsigned int i = 0; i < vertices.size(); i++) {
        visited[i] = 0;
    }
    visited[srcIndex] = 1;
    int time = shortestPathTime(srcIndex, destIndex, visited, src, dest);
    cout << time << endl;
}

vector<Vertex> &Graph::getVertices(){
    return vertices;
}
