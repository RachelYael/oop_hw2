#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include "Graph.h"

#define MAX_LEN 32
#define INTERCITY 15
#define CENTRAL 10
#define STAD 5

//region statements
void readConfigData(string file, int &bus, int &tram, int &rail, int &sprinter, int &intercity, int &central, int &stad);

void readInputData(char *file, Graph &graph);

void printOutbound(string vertexName, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void printInbound(string vertexName, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void printUniExpress(string src, string target, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void printMultiExpress(Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void print(string &outputFile, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void loadData(string fileName, Graph &graph);
//endregion


void findUnion(Graph &tram, Graph &bus, Graph &rail, Graph &sprinter);

void findCommonEdges(Graph &graph, Graph &graph1, Graph &graph2, Graph &graph3);

void createCommonGraph(Graph &graph, Graph &graph1, Graph &graph2, Graph &graph3);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Error: Invalid input.\nYou must provide at least one input file " << std::endl;
        exit(1);
    }

    int bus = BUS_TIME, tram = TRAM_TIME, rail = RAIL_TIME, sprinter = SPRINTER_TIME;
    int intercity = INTERCITY, central = CENTRAL, stad = STAD;

    // handle config file
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            readConfigData(argv[i + 1], bus, tram, rail, sprinter, intercity, central, stad);
            i++;
        }
    }

    // handle output file
    string outputFile = "output.dat";
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            outputFile = argv[i + 1];
        }
    }


    Graph g_tram("tram", intercity, central, stad, tram);
    Graph g_bus("bus", intercity, central, stad, bus);
    Graph g_rail("rail", intercity, central, stad, rail);
    Graph g_sprinter("sprinter", intercity, central, stad, sprinter);

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]).find("tram") != string::npos) {
            readInputData(argv[i], g_tram);
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
        while (iss.good() && i < 3) {
            iss >> arr[i];
            ++i;
        }
        if (arr[0] == "load") {
            if (arr[1].find("bus") != string::npos) {
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
        } else if (arr[0] == "print") {
            //print to output file:
            ofstream out(outputFile);
            streambuf *coutbuf = std::cout.rdbuf(); //old buff
            cout.rdbuf(out.rdbuf()); //redirect
            print(outputFile, g_tram, g_bus, g_rail, g_sprinter);
            //return the output to standard output.
            cout.rdbuf(coutbuf);
        } else {
            cout << "Invalid command, please try again." << endl;
        }
    }

}

void readConfigData(string file, int &bus, int &tram, int &rail, int &sprinter, int &intercity, int &central, int &stad) {
    ifstream fileIn;
    fileIn.open(file.c_str());
    if (!fileIn) {
        cerr << "Error: Configuration file could not be opened." << endl;
        fileIn.close();
        exit(1);
    }

    string line;
    while (getline(fileIn, line)) {
        istringstream iss(line);
        if (line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        if (tokens[0] == "bus") {
            bus = stoi(tokens[1]);
        } else if (tokens[0] == "rail") {
            rail = stoi(tokens[1]);
        } else if (tokens[0] == "sprinter") {
            sprinter = stoi(tokens[1]);
        } else if (tokens[0] == "tram") {
            tram = stoi(tokens[1]);
        } else if (tokens[0] == "intercity") {
            intercity = stoi(tokens[1]);
        } else if (tokens[0] == "central") {
            central = stoi(tokens[1]);
        } else if (tokens[0] == "stad") {
            stad = stoi(tokens[1]);
        } else {
            cerr << "ERROR: Unknown data in config file - " << tokens[0] << " is not valid." << endl;
            fileIn.close();
            exit(1);
        }
    }
}

void loadData(string fileName, Graph &graph) {
    ifstream fileIn;
    fileIn.open(fileName.c_str());
    if (!fileIn) {
        cerr << "ERROR opening the specified file." << endl;
        fileIn.close();
    } else {
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
}

void print(string &outputFile, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {
    ofstream outFile;
    outFile.open(outputFile.c_str());
    if (!outFile) {
        cerr << "ERROR opening the specified file." << endl;
        outFile.close();
    } else {
        tram.printGraph();
        bus.printGraph();
        rail.printGraph();
        sprinter.printGraph();
    }
}

void printMultiExpress(Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {
    createCommonGraph(tram, bus, rail, sprinter);
}

void createCommonGraph(Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {
    Graph common("");

    for(Vertex &v: tram.getVertices()){
        for(Edge &e: v.getEdgeList()) {
            common.insertUpdateData(e.getSrcName(), e.getDestName(), to_string(e.getWeight()));
        }
    }

    for(Vertex &v: bus.getVertices()){
        for(Edge &e: v.getEdgeList()) {
            common.insertUpdateData(e.getSrcName(), e.getDestName(), to_string(e.getWeight()));
        }
    }

    for(Vertex &v: rail.getVertices()){
        for(Edge &e: v.getEdgeList()) {
            common.insertUpdateData(e.getSrcName(), e.getDestName(), to_string(e.getWeight()));
        }
    }

    for(Vertex &v: sprinter.getVertices()){
        for(Edge &e: v.getEdgeList()) {
            common.insertUpdateData(e.getSrcName(), e.getDestName(), to_string(e.getWeight()));
        }
    }


    common.printGraph();
}

void printUniExpress(string src, string target, Graph &tram, Graph &bus, Graph &rail, Graph &sprinter) {
    bus.printUniExpress(src, target);
    tram.printUniExpress(src, target);
    sprinter.printUniExpress(src, target);
    rail.printUniExpress(src, target);
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
        cerr << "Error: Input file could not be opened." << endl;
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
