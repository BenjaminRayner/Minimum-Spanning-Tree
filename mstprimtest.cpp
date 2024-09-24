#include <iostream>
#include <string>
#include "Graph.h"

int main() {

    std::string cmdLine;
    Graph graph;

    while (1) {
        std::getline(std::cin, cmdLine);

        int pos_1 = cmdLine.find(' ');
        std::string command = cmdLine.substr(0, pos_1);

        // Add verticies
        if (command == "n") {
            int m = stoi(cmdLine.substr(pos_1 + 1, cmdLine.length() - 1));
            graph.insertVertices(m);
        }

        // Insert edge between two nodes (u,v) with weight (w)
        if (command == "i") {
            int pos_2 = cmdLine.find_first_of(';');
            int pos_3 = cmdLine.find_last_of(';');
            int u = stoi(cmdLine.substr(pos_1 + 1, pos_2 - pos_1));
            int v = stoi(cmdLine.substr(pos_2 + 1, pos_3 - pos_2));
            double w = stod(cmdLine.substr(pos_3 + 1, cmdLine.length() - 1));

            graph.insertEdge(u, v, w);
        }

        // Remove edge from nodes (u,v)
        if (command == "e") {
            int pos_2 = cmdLine.find_first_of(';');
            int u = stoi(cmdLine.substr(pos_1 + 1, pos_2 - pos_1));
            int v = stoi(cmdLine.substr(pos_2 + 1, cmdLine.length() - 1));

            graph.eraseEdge(u, v);
        }

        // Checks if nodes (u,v) are adjacent with weight (w)
        if (command == "adjacent") {
            int pos_2 = cmdLine.find_first_of(';');
            int pos_3 = cmdLine.find_last_of(';');
            int u = stoi(cmdLine.substr(pos_1 + 1, pos_2 - pos_1));
            int v = stoi(cmdLine.substr(pos_2 + 1, pos_3 - pos_2));
            double w = stod(cmdLine.substr(pos_3 + 1, cmdLine.length() - 1));

            graph.adjacent_w(u,v,w);
        }

        // Number of adjacent verticies for node (u)
        if (command == "degree") {
            int u = stoi(cmdLine.substr(pos_1 + 1, cmdLine.length() - 1));
            graph.degree(u);
        }

        // Total edges in MST
        if (command == "edge_count") {
            graph.edgeCount();
        }

        // Delete all edges
        if (command == "clear") {
            graph.clear();
            std::cout << "success" << std::endl;
        }

        // Reduces graph into a MST from root node (u)
        if (command == "mst") {
            int u = stoi(cmdLine.substr(pos_1 + 1, cmdLine.length() - 1));
            graph.mst(u);
        }

        if (command == "exit") {
            break;
        }
    }

    return 0;
}