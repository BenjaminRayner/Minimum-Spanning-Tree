#ifndef MST_EDGE_H
#define MST_EDGE_H

class Edge {

private:
    int _v;
    double _w;

public:
    Edge(int v, double w);

    int getv() const;
    double getw() const;
    void setw(double w);
};


#endif //MST_EDGE_H
