#include <iostream>
#include <iomanip>
#include "Graph.h"
#include "PriorityQ.h"
#include "illegal_exception.h"

//initialize member variables
Graph::Graph() {
    _vertexCount = 0;
    _edgeCount = 0;
}

//deletes all edges with clear, and deletes all vertices
//from _vertexSet
Graph::~Graph() {
    clear();
    for (int i{0}; i < _vertexCount; ++i) {
        delete _vertexSet[0];
        _vertexSet[0] = nullptr;
        _vertexSet.erase(_vertexSet.begin());
    }
}

//insert vertices into vertexSet labeled 0 to m-1
//resize _adjmatrix to accommodate m vertices
//updates vertex count in graph
void Graph::insertVertices(int m) {

    _adjList.resize(m);

    for (int i{0}; i < m; ++i) {
        _vertexSet.push_back(new Vertex(i));
    }

    _vertexCount = m;
    std::cout << "success" << std::endl;
}

//add edge to v with weight w to vertex u's adjacency list
//add edge to u with weight w to vertex v's adjacency list
//increment edge count by 2
void Graph::insertEdge(int const u, int const v, double const w) {

    //checking for valid input
    if (invalidInput(u,v,w)) {
        std::cout << "illegal argument" << std::endl;
        return;
    }

    //edge already exists?
    if (adjacent(u, v)) {
        //update weight on edge u to v
        for (int i{0}; i < _adjList[u].size(); ++i) {
            if (_adjList[u][i]->getv() == v) {
                _adjList[u][i]->setw(w);
                break;
            }
        }

        //update weight on edge v to u
        for (int i{0}; i < _adjList[v].size(); ++i) {
            if (_adjList[v][i]->getv() == u) {
                _adjList[v][i]->setw(w);
                break;
            }
        }
        std::cout << "success" << std::endl;
        return;
    }

    _adjList[u].push_back(new Edge(v,w));
    _adjList[v].push_back(new Edge(u,w));
    _edgeCount += 2;
    std::cout << "success" << std::endl;
}

//for all adjacent vertices to u, find v and delete
//edge to that vertex. Decrement edge count
void Graph::eraseEdge(int u, int v) {

    //checking for valid input
    if (invalidInput(u,v)) {
        std::cout << "illegal argument" << std::endl;
        return;
    }

    //edge exists?
    if (!adjacent(u, v)) {
        std::cout << "failure" << std::endl;
        return;
    }

    //deletes edge from u to v
    for (int i{0}; i < _adjList[u].size(); ++i) {
        if (_adjList[u][i]->getv() == v) {
            delete _adjList[u][i];
            _adjList[u][i] = nullptr;
            _adjList[u].erase(_adjList[u].begin() + i);
            break;
        }
    }

    //deletes edge from v to u
    for (int i{0}; i < _adjList[v].size(); ++i) {
        if (_adjList[v][i]->getv() == u) {
            delete _adjList[v][i];
            _adjList[v][i] = nullptr;
            _adjList[v].erase(_adjList[v].begin() + i);
            break;
        }
    }

    _edgeCount -= 2;
    std::cout << "success" << std::endl;
}

//for all adjacent vertices to u, return true if there's
//an edge to v in the adjacency list with a weight of w.
//Else, return false
bool Graph::adjacent_w(int u, int v, double w) {

    //checking for valid input
    if (invalidInput(u,v)) {
        std::cout << "illegal argument" << std::endl;
        return false;
    }

    for (int i{0}; i < _adjList[u].size(); ++i) {
        if (_adjList[u][i]->getv() == v && _adjList[u][i]->getw() == w) {
            std::cout << std::fixed << std::setprecision(2) << "adjacent " << u << " " << v << " " << w << std::endl;
            return true;
        }
    }
    std::cout << std::fixed << std::setprecision(2) << "not adjacent " << u << " " << v << " " << w << std::endl;
    return false;
}

//same thing as adjacent_w but without weight param
bool Graph::adjacent(int u, int v) {
    for (int i{0}; i < _adjList[u].size(); ++i) {
        if (_adjList[u][i]->getv() == v) {
            return true;
        }
    }
    return false;
}

//return the size of the adjacency list for u.
//this represents degree. (number of adjacent vertices)
void Graph::degree(int u) {
    if (invalidInput(u)) {
        std::cout << "illegal argument" << std::endl;
        return;
    }
    std::cout << "degree of " << u << " is " << _adjList[u].size() << std::endl;
}

//returns total edge count of graph
void Graph::edgeCount() const {
    std::cout << "edge count is " << _edgeCount << std::endl;
}

//for all vertices in the graph, delete all edges
//from that vertex
void Graph::clear() {
    for (int i{0}; i < _adjList.size(); ++i) {
        for (int j{0}; j < _adjList[i].size() + j; ++j) {
            delete _adjList[i][0];
            _adjList[i][0] = nullptr;
            _adjList[i].erase(_adjList[i].begin());
        }
    }
    _edgeCount = 0;
}

//generates a mst from the graph
void Graph::mst(int r) {
    double weight{0.00};

    //checking for valid input
    if (invalidInput(r)) {
        std::cout << "illegal argument" << std::endl;
        return;
    }

    //converting vector to array and
    //initializing keys
    Vertex* minHeap[_vertexCount];
    for (int i{0}; i < _vertexCount; ++i) {
        minHeap[i] = _vertexSet[i];
        minHeap[i]->setKey(2147483647);
    }

    //set starting vertex's key to 0 and
    //initialize PQ (generate minHeap)
    minHeap[r]->setKey(0);
    PriorityQ PQ(minHeap, _vertexCount, r);

    while (!PQ.isEmpty()) {
        //remove vertex with smallest key and equate to u.
        int u = PQ.extractMin()->getLabel();

        //if removed key is inf, graph is disconnected
        if (_vertexSet[u]->getKey() == 2147483647) {
            std::cout << "not connected" << std::endl;
            return;
        }
        //add weight to total.
        weight += _vertexSet[u]->getKey();

        //for each adjacent vertex 'v' to u, if it's in the PQ and
        //weight between u and v < v.key, set v's key to weight between
        //u and v, re-heapify PQ to reflect change, and set parent of v to u
        for (int i{0}; i < _adjList[u].size(); ++i) {
            int v = _adjList[u][i]->getv();

            if (PQ.inQ(_vertexSet[v]) && (w(u, v) < _vertexSet[v]->getKey())) {
                _vertexSet[v]->setKey(w(u, v));
                PQ.modifyKey(_vertexSet[v]);
            }
        }
    }

    std::cout << std::fixed << std::setprecision(2) << "mst " << weight << std::endl;
}

//returns weight between two vertices
double Graph::w(int u, int v) {

    for (int i{0}; i < _adjList[u].size(); ++i) {
        if (_adjList[u][i]->getv() == v) {
            return _adjList[u][i]->getw();
        }
    }

    return 0;
}

//checking for valid input
bool Graph::invalidInput(int u, int v, double w) const {
    try {
        if (u >= _vertexCount || v >= _vertexCount || w <= 0.00 || u == v) {
            throw illegal_exception(); // NOLINT(hicpp-exception-baseclass)
        }
    }
    catch (illegal_exception e) {
        return true;
    }

    return false;
}