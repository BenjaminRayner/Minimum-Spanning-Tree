#include "Vertex.h"

Vertex::Vertex() {
    _vertexLabel = -1;
    _key = 2147483647;
}

//Initializes vertex label, sets key to
//high number, and parent to null
Vertex::Vertex(int m) {
    _vertexLabel = m;
    _key = 2147483647;
}

int Vertex::getLabel() const {
    return _vertexLabel;
}

double Vertex::getKey() const {
    return _key;
}

void Vertex::setKey(double k) {
    _key = k;
}
