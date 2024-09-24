#include "PriorityQ.h"
#include <cmath>

//converts vertexSet to an array and uses
//that to build initial heap with minimum root.
//also indexing my index array to find vertex in heap
//in O(1) time.
PriorityQ::PriorityQ(Vertex* A[], int s, int root) {
    _minHeap = A;
    _qSize = s;

    int *temp = new int[s];
    _index = temp;

    for (int i{0}; i < _qSize; ++i) {
        _index[i] = i;
    }

    modifyKey(_minHeap[root]);
}

//deletes dynamically allocated index array
PriorityQ::~PriorityQ() {
    delete []_index;
    _index = nullptr;
}

//checks vertex at index i and re-heapifies to
//reflect a minHeap
void PriorityQ::heapify(Vertex* A[], int i) {

    int l = 2 * i + 1;
    int r = (2 * i) + 2;
    int smallest;

    if (l < _qSize && A[l]->getKey() < A[i]->getKey()) {
        smallest = l;
    }
    else {
        smallest = i;
    }

    if (r < _qSize && A[r]->getKey() < A[smallest]->getKey()) {
        smallest = r;
    }

    if (smallest != i) {
        //Swapping vertex index
        std::swap(_index[A[i]->getLabel()],_index[A[smallest]->getLabel()]);

        //Swapping the actual vertices
        std::swap(A[i], A[smallest]);

        heapify(A, smallest);
    }
}

//returns vertex with minimum key in heap
//and re-heapifies to restore minHeap.
//also adjusts index.
Vertex* PriorityQ::extractMin() {

    _index[_minHeap[_qSize - 1]->getLabel()] = 0;

    Vertex* min = _minHeap[0];
    _minHeap[0] = _minHeap[_qSize - 1];
    --_qSize;
    heapify(_minHeap, 0);
    return min;
}

//is called when a key is modified in one of the vertices
//we start at that node and work our way up until its key is greater
//than all below.
void PriorityQ::modifyKey(Vertex* v) {

    int pos = _index[v->getLabel()];
    while (pos > 0 && _minHeap[static_cast<int>(floor(pos/2))]->getKey() > v->getKey()) {
        //Swapping vertex index
        std::swap(_index[_minHeap[pos]->getLabel()],_index[_minHeap[static_cast<int>(floor(pos/2))]->getLabel()]);

        //Swapping the actual vertices
        std::swap(_minHeap[pos], _minHeap[static_cast<int>(floor(pos/2))]);
        pos = static_cast<int>(floor(pos/2));
    }
}

//checks if PQ size is 0
bool PriorityQ::isEmpty() const {
    if (_qSize == 0) {
        return true;
    }
    return false;
}

//if the key of vertex v is smaller than smallest entry,
//key cannot be in Q. Otherwise, it is.
bool PriorityQ::inQ(Vertex* v) {
    if (v->getKey() < _minHeap[0]->getKey()) {
        return false;
    }
    return true;
}