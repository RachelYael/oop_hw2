#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

#include "Simulation.h"
#include "Graph.h"

#define MAX_LEN 32

//region statements
void readConfigData(string file,  int *bus, int *tram, int * rail, int* sprinter,int* intercity,int* central, int* stad);
void readInputData(char *file, Graph &graph);

void printOutbound(string vertexName, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void printInbound(string vertexName, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void printUniExpress(string src, string target, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void printMultiExpress(Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void print(Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void loadData(string fileName, Graph &graph);
//endregion



void setDefaultVal(int *bus, int *tram, int *sprinter, int *rail, int *intercity, int *central, int *stad);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Error: Invalid input.\nYou must provide at least one input file " << std::endl;
        exit(1);
    }
    int bus, tram, rail, sprinter;
    int intercity, central, stad;
    setDefaultVal(&bus, &tram, &sprinter , &rail,&intercity,& central, & stad);
    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-c") == 0) {
            readConfigData(argv[i+1],&bus, &tram, &rail, &sprinter,& intercity, &central,& stad);
            cout<<"read configuration file, update default values"<<endl;
            i++;
        }
    }
    Graph g_tram("tram",intercity,central,stad);
    Graph g_bus("bus",intercity,central,stad);
    Graph g_rail("rail",intercity,central,stad);
    Graph g_sprinter("sprinter",intercity,central,stad);

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]).find("tram") != string::npos) {
            readInputData(argv[i], g_tram);
            g_tram.printGraph();
        }
        if (string(argv[i]).find("bus") != string::npos) {
            readInputData(argv[i], g_bus);
        }
        if (string(argv[i]).find("rail") != string::npos) {
            readInputData(argv[i], g_rail);
            g_rail.printGraph();
        }
        if (string(argv[i]).find("sprinter") != string::npos) {
            readInputData(argv[i], g_sprinter);
        }

    }

    string input;
    while (1) {
        if (input == "EXIT")
            return 0;
        getline(cin, input);
        stringstream iss(input);
        string arr[3];
        int i = 0;
        while (iss.good() && i <  3) {
            iss >> arr[i];
            ++i;
        }
        if (arr[0] == "load") {
            if (arr[1].find("bus") != string::npos){
                loadData(arr[1], g_bus);
            } else if (arr[1].find("tram") != string::npos) {
                loadData(arr[1], g_tram);
            } else if (arr[1].find("rail") != string::npos) {
                loadData(arr[1], g_rail);
            } else {
                loadData(arr[1], g_sprinter);
            }
        } else if (arr[0] == "outbound") {
            printOutbound(arr[1], g_tram, g_bus, g_rail, g_sprinter);
        } else if (arr[0] == "inbound") {
            printInbound(arr[1], g_tram, g_bus, g_rail, g_sprinter);
        } else if (arr[0] == "uniExpress") {
            printUniExpress(arr[1], arr[2], g_tram, g_bus, g_rail, g_sprinter);
        } else if (arr[0] == "multiExpress") {
            printMultiExpress(g_tram, g_bus, g_rail, g_sprinter);
        } else if (arr[0] == "print")
            print(g_tram, g_bus, g_rail, g_sprinter);
    }

    return 0;
}

void setDefaultVal(int *bus, int *tram, int *sprinter, int *rail, int *intercity, int *central, int *stad) {
    *bus = 1;
    *tram=2;
    *sprinter=3;
    *rail=5;
    *intercity=15;
    *central=10;
    *stad=5;
}

void readConfigData(string file,  int *bus, int *tram, int * rail, int* sprinter,int* intercity,int* central, int* stad) {
//    vector<string> configVec;
    ifstream fileIn;
    fileIn.open(file.c_str());
    if (!fileIn) {
        cerr << "ERROR opening the specified file." << endl;
        fileIn.close();
        exit(1);
    }

    string line;
    while (getline(fileIn, line)) {
        istringstream iss(line);
        if(line[line.size()-1] == '\r'){
            line.erase(line.size() - 1);
        }
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
      if(tokens[0] == "bus"){
            *bus=stoi(tokens[1]);
            cout<<"bus"<<endl;
      }
      if(tokens[0] == "rail"){
            *rail=stoi(tokens[1]);
      }
      if(tokens[0] == "sprinter"){
            *sprinter=stoi(tokens[1]);
      }
      if(tokens[0] == "tram"){
            *tram=stoi(tokens[1]);
      }
      if(tokens[0] == "intercity"){
            *intercity=stoi(tokens[1]);
      }
      if(tokens[0] == "central"){
            *central=stoi(tokens[1]);
          cout<<"central"<<endl;

      }
      if(tokens[0] == "stad"){
            *stad=stoi(tokens[1]);
      }
        cout<<"out"<<endl;

    }
    cout<<"totly out"<<endl;
}

void loadData(string fileName, Graph &graph) {
    ifstream fileIn;
    fileIn.open(fileName.c_str());
    if (!fileIn) {
        cerr << "ERROR opening the specified file." << endl;
        fileIn.close();
        exit(1);
    }

    string line;
    while (getline(fileIn, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens[0].length() > MAX_LEN || tokens[1].length() > MAX_LEN) {
            cerr << "Error: Vertex name length is more than 32 chars" << endl;
            exit(1);
        }

        if (stoi(tokens[2]) < 0) {
            cerr << "Error: Duration can't be negative number" << endl;
            exit(1);
        }
        graph.insertUpdateData(tokens[0], tokens[1], tokens[2]);
    }

    cout << "Update was successful." << endl;
}

void print(Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {

}

void printMultiExpress(Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {

}

void printUniExpress(string src, string target, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {
    bus.shortestPathTime(src, target);
    tram.shortestPathTime(src, target);
    sprinter.shortestPathTime(src, target);
    rail.shortestPathTime(src, target);
}

void printInbound(string vertexName, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {
    bus.printInbound(vertexName);
    tram.printInbound(vertexName);
    sprinter.printInbound(vertexName);
    rail.printInbound(vertexName);
}

void printOutbound(string vertexName, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {
    bus.printOutbound(vertexName);
    tram.printOutbound(vertexName);
    sprinter.printOutbound(vertexName);
    rail.printOutbound(vertexName);
}

void readInputData(char *file, Graph &graph) {
    ifstream data;
    data.open(file);
    if (!data) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        data.close();
        exit(1);
    }

    string line;
    while (getline(data, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens[0].length() > MAX_LEN || tokens[1].length() > MAX_LEN) {
            cerr << "Error: Vertex name length is more than 32 chars" << endl;
            exit(1);
        }

        if (stoi(tokens[2]) < 0) {
            cerr << "Error: Duration can't be negative number" << endl;
            exit(1);
        }
        graph.insertUpdateData(tokens[0], tokens[1], tokens[2]);
    }

}
