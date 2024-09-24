#ifndef MST_VERTEX_H
#define MST_VERTEX_H

class Vertex {

private:
    int _vertexLabel;
    double _key;

public:
    Vertex();
    explicit Vertex(int m);

    int getLabel() const;
    double getKey() const;
    void setKey(double k);
};


#endif //MST_VERTEX_H
