//
// Created by Admin on 5/9/2022.
//

#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;


class Edge{
public:
    int DestinationVertexId;
    int weight;
    Edge(){}
    Edge(int destVId, int w){
        DestinationVertexId = destVId;
        weight = w;
    }
    void setEdgeVal(int destVId, int w){
        DestinationVertexId = destVId;
        weight = w;
    }
    void setWeight(int w){
        weight=w;
    }
    int getDestinationVertexId(){
        return DestinationVertexId;
    }
    int getWeight(){
        return weight;
    }

};

class Vertex{
public:
    int stationId;
    string stationName;


    list<Edge> edgeList;
    Vertex(){
        stationId= 0;
        stationName="";
    }
    Vertex(int id, string name){
        stationId= id;
        stationName= name;
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

    list<Edge> getEdgeList() {
        return edgeList;
    }
    void printEdgeList() {
//        cout << "[";
        for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
            cout << it -> getDestinationVertexId() << "(" << it -> getWeight() << ") --> ";
//            cout << it -> getStationName() << "(" << it -> getWeight() << ") --> ";
        }
//        cout << "]";
        cout << endl;
    }
};
class Graph{
public:
    vector<Vertex> vertices;

    bool checkIfVertexExistByID(int vid) {
        bool flag = false;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).getStationId() == vid) {
                return true;
            }
        }
        return flag;
    }

    void addVertex(Vertex newVertex) {
        bool check = checkIfVertexExistByID(newVertex.getStationId());
        if (check == true) {
            cout << "Vertex with this ID already exist" << endl;
        } else {
            vertices.push_back(newVertex);
            cout << "New Vertex Added Successfully" << endl;
        }
    }

    Vertex getVertexByID(int vid) {
        Vertex temp;
        for (int i = 0; i < vertices.size(); i++) {
            temp = vertices.at(i);
            if (temp.getStationId() == vid) {
                return temp;
            }
        }
        return temp;
    }

    bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
        Vertex v = getVertexByID(fromVertex);
        list < Edge > e;
        e = v.getEdgeList();
        bool flag = false;
        for (auto it = e.begin(); it != e.end(); it++) {
            if (it -> getDestinationVertexId() == toVertex) {
                flag = true;
                return flag;
                break;
            }

        }
        return flag;
    }

    void updateVertex(int oldVID, string vname) {
        bool check = checkIfVertexExistByID(oldVID);
        if (check == true) {
            for (int i = 0; i < vertices.size(); i++) {
                if (vertices.at(i).getStationId() == oldVID) {
                    vertices.at(i).setStationName(vname);
                    break;
                }
            }
            cout << "Vertex(State) Updated Successfully " << endl;
        }
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight) {
        bool check1 = checkIfVertexExistByID(fromVertex);
        bool check2 = checkIfVertexExistByID(toVertex);

        bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
        if ((check1 && check2 == true)) {

            if (check3 == true) {
                cout << "Edge between " << getVertexByID(fromVertex).getStationName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStationName() << "(" << toVertex << ") Already Exist" << endl;
            } else {

                for (int i = 0; i < vertices.size(); i++) {

                    if (vertices.at(i).getStationId() == fromVertex) {
                        Edge e(toVertex, weight);
                        //edgeList.push_back(e);
                        //vertices.at(i).addEdgeToEdgelist(toVertex,weight);
                        vertices.at(i).edgeList.push_back(e);
                    } else if (vertices.at(i).getStationId() == toVertex) {
                        Edge e(toVertex, weight);
                        //edgeList.push_back(e);
                        //vertices.at(i).addEdgeToEdgelist(fromVertex,weight);
                        vertices.at(i).edgeList.push_back(e);
                    }
                }

                cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
            }
        } else {
            cout << "Invalid Vertex ID entered.";
        }
    }

    void updateEdgeByID(int fromVertex, int toVertex, int newWeight) {
        bool check = checkIfEdgeExistByID(fromVertex, toVertex);
        if (check == true) {
            for (int i = 0; i < vertices.size(); i++) {

                if (vertices.at(i).getStationId() == fromVertex) {
                    for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                        if (it -> getDestinationVertexId() == toVertex) {
                            it -> setWeight(newWeight);
                            break;
                        }

                    }

                } else if (vertices.at(i).getStationId() == toVertex) {
                    for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                        if (it -> getDestinationVertexId() == fromVertex) {
                            it -> setWeight(newWeight);
                            break;
                        }

                    }
                }
            }
            cout << "Edge Weight Updated Successfully " << endl;
        } else {
            cout << "Edge between " << getVertexByID(fromVertex).getStationName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStationName() << "(" << toVertex << ") DOES NOT Exist" << endl;
        }
    }

    void deleteEdgeByID(int fromVertex, int toVertex) {
        bool check = checkIfEdgeExistByID(fromVertex, toVertex);
        if (check == true) {
            for (int i = 0; i < vertices.size(); i++) {
                if (vertices.at(i).getStationId() == fromVertex) {
                    for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                        if (it -> getDestinationVertexId() == toVertex) {
                            vertices.at(i).edgeList.erase(it);
                            //cout<<"First erase"<<endl;
                            break;
                        }
                    }
                }

                if (vertices.at(i).getStationId() == toVertex) {

                    for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                        if (it -> getDestinationVertexId() == fromVertex) {
                            vertices.at(i).edgeList.erase(it);
                            //cout<<"second erase"<<endl;
                            break;
                        }
                    }
                }
            }
            cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
        }
    }

    void deleteVertexByID(int vid) {
        int vIndex = 0;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).getStationId() == vid) {
                vIndex = i;
            }
        }
        for (int i = 0; i < vertices.size(); i++) {
            for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                if (it -> getDestinationVertexId() == vid) {
                    vertices.at(i).edgeList.erase(it);
                    break;
                }
            }

        }
        vertices.erase(vertices.begin() + vIndex);
        cout << "Vertex Deleted Successfully" << endl;
    }

    void getAllNeigborsByID(int vid) {
        cout << getVertexByID(vid).getStationName() << " (" << getVertexByID(vid).getStationId() << ") --> ";
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).getStationId() == vid) {
                cout << "[";
                for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                    cout << it -> getDestinationVertexId() << "(" << it -> getWeight() << ") --> ";
                }
                cout << "]";

            }
        }

    }

    void printGraph() {
        for (int i = 0; i < vertices.size(); i++) {
            Vertex temp;
            temp = vertices.at(i);
            cout << temp.getStationName() << " (" << temp.getStationId() << ") --> ";
            temp.printEdgeList();
        }
    }
};
#endif //HW2_GRAPH_H
