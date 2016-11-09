#ifndef GRAPH_H
#define GRAPH_H
#include "Results.h"

class Graph {
public:
    Graph(int size);
    virtual ~Graph();
    virtual void connectVertices(int start, int end, int distance) = 0;
    virtual int getVerticesDistance(int start, int end) = 0;
    virtual Results* runBellmanFord(int startNode, int endNode) = 0;
    virtual int runFordFulkerson(int start, int end) = 0;
protected:
    int *distance;
    int *previous;
private:
};

#endif // GRAPH_H
