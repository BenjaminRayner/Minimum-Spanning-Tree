#include "Edge.h"

//initializes edge vertex target v, and
//weight of edge, w
Edge::Edge(int v, double w) {
    _v = v;
    _w = w;
}

int Edge::getv() const {
    return _v;
}

double Edge::getw() const {
    return _w;
}

void Edge::setw(double w) {
    _w = w;
}
