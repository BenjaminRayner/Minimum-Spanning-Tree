#ifndef MST_PRIORITYQ_H
#define MST_PRIORITYQ_H

#include <vector>
#include "Vertex.h"

class PriorityQ {

private:
    Vertex** _minHeap;
    int* _index;
    int _qSize;

public:
    PriorityQ(Vertex* A[], int s, int root);
    ~PriorityQ();

    void heapify(Vertex* A[], int i);
    Vertex* extractMin();
    void modifyKey(Vertex* v);
    bool isEmpty() const;
    bool inQ(Vertex* v);
};


#endif //MST_PRIORITYQ_H
