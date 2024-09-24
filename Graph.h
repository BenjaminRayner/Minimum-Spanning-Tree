#ifndef MST_GRAPH_H
#define MST_GRAPH_H

#include <vector>
#include "Vertex.h"
#include "Edge.h"

class Graph {

private:
    std::vector<Vertex*> _vertexSet;
    std::vector<std::vector<Edge*>> _adjList;
    int _edgeCount;
    int _vertexCount;

public:
    Graph();
    ~Graph();

    void insertVertices(int m);
    void insertEdge(int u, int v, double w);
    void eraseEdge(int u, int v);
    bool adjacent(int u, int v);
    bool adjacent_w(int u, int v, double w);
    void degree(int u);
    void edgeCount() const;
    void clear();
    void mst(int u);

    double w(int u, int v);
    bool invalidInput(int u, int v = -1, double w = 1.00) const;
};


#endif //MST_GRAPH_H
