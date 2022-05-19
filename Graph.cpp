//
// Created by Admin on 5/9/2022.
//

#include "Graph.h"
#include "Bus.h"
#include "Rail.h"
#include "Sprinter.h"
#include "Tram.h"

//#define INTERCITY 15
//#define CENTRAL 10
//#define STAD 5

Graph::Graph(string vechile) {
    if (vechile == "bus") {
        this->vehicle = new Bus();
    } else if (vechile == "rail") {
        this->vehicle = new Rail();
    } else if (vechile == "sprinter") {
        this->vehicle = new Sprinter();
    } else {
        this->vehicle = new Tram();
    }
}

Graph::Graph(string vechile, int inter, int center, int stad){
    if (vechile == "bus") {
        this->vehicle = new Bus();
    } else if (vechile == "rail") {
        this->vehicle = new Rail();
    } else if (vechile == "sprinter") {
        this->vehicle = new Sprinter();
    } else {
        this->vehicle = new Tram();
    }
    this->intercity = inter;
    this->central=center;
    this->stad=stad;
}
//bool Graph::checkIfVertexExistByID(int vid)  {
//    for (int i = 0; i < vertices.size(); i++) {
//        if (vertices.at(i).getStationId() == vid) {
//            return true;
//        }
//    }
//    return false;
//}

bool Graph::checkIfVertexExistByName(string vname) {
    for (int i = 0; i < vertices.size(); i++) {
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

Vertex Graph::getVertexByID(int vid) {
    Vertex temp;
    for (int i = 0; i < vertices.size(); i++) {
        temp = vertices.at(i);
        if (temp.getStationId() == vid) {
            return temp;
        }
    }
    return temp;
}

//bool Graph::checkIfEdgeExistByID(int fromVertex, int toVertex) {
//    Vertex v = getVertexByID(fromVertex);
//    list<Edge> e;
//    e = v.getEdgeList();
//    for (auto it = e.begin(); it != e.end(); it++) {
//        if (it->getDestId() == toVertex) {
//            return true;
//            break;
//        }
//    }
//    return false;
//}

//void Graph::updateVertex(int oldVID, string vname) {
//    bool check = checkIfVertexExistByID(oldVID);
//    if (check) {
//        for (int i = 0; i < vertices.size(); i++) {
//            if (vertices.at(i).getStationId() == oldVID) {
//                vertices.at(i).setStationName(vname);
//                break;
//            }
//        }
//        cout << "Vertex(State) Updated Successfully " << endl;
//    }
//}

//void Graph::addEdgeByID(int fromVertex, int toVertex, int weight) {
//    bool check1 = checkIfVertexExistByID(fromVertex);
//    bool check2 = checkIfVertexExistByID(toVertex);
//
//    bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
//    if ((check1 && check2)) {
//
//        if (check3) {
//            cout << "Edge between " << getVertexByID(fromVertex).getStationName() << "(" << fromVertex << ") and "
//                 << getVertexByID(toVertex).getStationName() << "(" << toVertex << ") Already Exist" << endl;
//        } else {
//
//            for (int i = 0; i < vertices.size(); i++) {
//
//                if (vertices.at(i).getStationId() == fromVertex) {
//                    Edge e(fromVertex, toVertex, weight);
//                    vertices.at(i).edgeList.push_back(e);
//                }
//            }
//
//            cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
//        }
//    } else {
//        cout << "Invalid Vertex ID entered.";
//    }
//}

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

//void Graph::deleteEdgeByID(int fromVertex, int toVertex) {
//    bool check = checkIfEdgeExistByID(fromVertex, toVertex);
//    if (check) {
//        for (int i = 0; i < vertices.size(); i++) {
//            if (vertices.at(i).getStationId() == fromVertex) {
//                for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
//                    if (it->getDestId() == toVertex) {
//                        vertices.at(i).edgeList.erase(it);
//                        //cout<<"First erase"<<endl;
//                        break;
//                    }
//                }
//            }
//
//            if (vertices.at(i).getStationId() == toVertex) {
//
//                for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
//                    if (it->getDestId() == fromVertex) {
//                        vertices.at(i).edgeList.erase(it);
//                        //cout<<"second erase"<<endl;
//                        break;
//                    }
//                }
//            }
//        }
//        cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
//    }
//}

//void Graph::deleteVertexByID(int vid) {
//    int vIndex = 0;
//    for (int i = 0; i < vertices.size(); i++) {
//        if (vertices.at(i).getStationId() == vid) {
//            vIndex = i;
//        }
//    }
//    for (int i = 0; i < vertices.size(); i++) {
//        for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
//            if (it->getDestId() == vid) {
//                vertices.at(i).edgeList.erase(it);
//                break;
//            }
//        }
//
//    }
//    vertices.erase(vertices.begin() + vIndex);
//    cout << "Vertex Deleted Successfully" << endl;
//}

void Graph::printAllNeigborsByName(string vname) {
    if (vertices.empty()) {
        cout << " no outbound travel" << endl;
        return;
    }
    for (Vertex &v: vertices) {
        if (v.getStationName() == vname) {
            if (v.getEdgeList().empty()) {
                cout << " no outbound travel" << endl;
            }
            int i = 0;
            for (Edge &e: v.getEdgeList()) {
                if (i == v.getEdgeList().size() - 1) {
                    cout << e.getDestName() << endl;
                } else {
                    cout << e.getDestName() << "\t";
                }
                i++;
            }
        }
    }
}

void Graph::printGraph() {
    for (Vertex &v: vertices) {
        v.printEdgeList();
    }
}


void Graph::insertUpdateData(string srcName, string destName, string weight) {
    // check if vertices already exists
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
        } else if (isCentral(srcName)) {
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

Vertex Graph::getVertexByName(string vname) {
    Vertex temp;
    for (int i = 0; i < vertices.size(); i++) {
        if (temp.getStationName() == vname) {
            return temp;
        }
    }
    return temp;
}

void Graph::printOutbound(string vname) {
    cout << vehicle->getType() << ": ";
//    printAllNeigborsByName(vname);
    reachableFromV(vname);
}

void Graph::printInbound(string vname) {
    cout << vehicle->getType() << ": ";
    printAllVertexSources(vname);
}

void Graph::printAllVertexSources(string vname) {
    if (vertices.empty()) {
        cout << " no inbound travel" << endl;
        return;
    }
    vector<string> inbounds;
    for (Vertex &v: vertices) {
        for (Edge &e: v.getEdgeList()) {
            if (e.getDestName() == vname) {
                inbounds.push_back(v.getStationName());
            }
        }
    }

    if (inbounds.empty()) {
        cout << " no inbound travel" << endl;
        return;
    }

    int i = 0;
    for (string &s: inbounds) {
        if (i == inbounds.size() - 1) {
            cout << s << endl;
        } else {
            cout << s << "\t";
        }
        i++;
    }
}

void Graph::shortestPathTime(string src, string target) {
    int srcIndex = getVertexIndex(src);
    int targetIndex = getVertexIndex(target);
    if (srcIndex == -1 || targetIndex == -1) {

    }

    int size = vertices.size();
    long int distance[size];
    bool Tset[size];

    for (int i = 0; i < size; i++) {
        distance[i] = INTMAX_MAX;
        Tset[i] = false;
    }

    distance[srcIndex] = 0;

    for (unsigned int i = 0; i < size; i++) {
        int m = minDist(distance, Tset);
        Tset[m] = true;
        for (unsigned int j = 0; j < size; j++) {
            // updating the distance of neighbouring vertex
            bool isEdge = checkIfEdgeExistByName(vertices[m].getStationName(), vertices[j].getStationName());
            int edgeWeight = getEdgeWeight(vertices[m].getStationName(), vertices[j].getStationName());
            if (!Tset[i] && isEdge && distance[m] != INTMAX_MAX && distance[m] + edgeWeight < distance[j])
                distance[j] = distance[m] + edgeWeight;

        }
        cout<<"Vertex\t\tDistance from source vertex"<<endl;
        for(int k = 0; k<6; k++)
        {
            char str=65+k;
            cout<<str<<"\t\t\t"<<distance[k]<<endl;
        }

    }
}

unsigned int Graph::getVertexIndex(string vname) {
    for (unsigned int i = 0; i < vertices.size(); i++) {
        if (vertices[i].getStationName() == vname) {
            return i;
        }
    }
    return -1;
}

int Graph::minDist(const long distance[], const bool Tset[]) const {
    long int minimum = INTMAX_MAX, ind;
    for (int i = 0; i < vertices.size(); i++) {
        if (!Tset[i] && distance[i] <= minimum) {
            minimum = distance[i];
            ind = i;
        }
    }
    return ind;

}

int Graph::getEdgeWeight(string src, string target) {
    for (Vertex &v: vertices) {
        if (v.getStationName() == src) {
            for (Edge &e: v.getEdgeList()) {
                if (e.getDestName() == target) {
                    return e.getWeight();
                }
            }
        }
    }
    return -1;
}

//void Graph::reachableFromV(string startVertex){
//    int numVertices = vertices.size();
//    bool* visited = new bool[numVertices];
//    for (int i = 0; i < numVertices; i++)
//        visited[i] = false;
//    list<int> queue;
//    int vertexIndex = getVertexIndex(startVertex);
//    visited[vertexIndex] = true;
//    queue.push_back(vertexIndex);
//
//    list<int>::iterator i;
//
//
//    while (!queue.empty()) {
//        int currVertex = queue.front();
//        cout << "Visited " << currVertex << " ";
//        queue.pop_front();
//
//
//        for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i) {
//            int adjVertex = *i;
//            if (!visited[adjVertex]) {
//                visited[adjVertex] = true;
//                queue.push_back(adjVertex);
//            }
//        }
//}
//}

void Graph::reachableFromV(string startVertex) {
    int vertexIndex = getVertexIndex(startVertex);
    if(vertexIndex<0){
        cout<<"no outbound travel"<<endl;
        return;
    }
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
//        cout << vertexIndex << " ";
        cout << getVertexByID(vertexIndex).getStationName() << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it

        list<Edge>listV = vertices[vertexIndex].getEdgeList();
        for (auto adjecent:listV) {

            if (!visited[getVertexIndex(adjecent.getSrcName())]){
                visited[getVertexIndex(adjecent.getSrcName())] = true;
                queue.push_back(getVertexIndex(adjecent.getSrcName()));
            }

        }


    }
}


void Graph::transposeGraph(Graph *g, string vehicle){
    Graph transpose = Graph(vehicle);
    int size = g->vertices.size();
    for (int i = 0; i < size; i++){
        list<Edge>listV = vertices[i].getEdgeList();
        list<Edge>::iterator it;
        for ( it = listV.begin() ; it!=listV.end()  ; it ++) {
            transpose.addVertex(vertices[i]);
//            transpose.addVertex();// i dont know
//            transpose.addEdgeByName();

        }
    }


}
// A class to represent a graph object

