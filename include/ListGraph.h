#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "Numbers.h"
#include <list>
#include <memory>

using namespace std;

class ListGraph: public Graph {
public:
    ListGraph(int size);
    virtual ~ListGraph();
    void connectVertices(int start, int end, int distance);
    int getVerticesDistance(int start, int end);
    Results* runBellmanFord(int startNode, int endNode);
    int runFordFulkerson(int start, int end);
protected:

private:

    struct Arc {
        int start;
        int end;
        int distance;
        Arc();
        Arc(int start, int end, int distance): start(start), end(end), distance(distance) {}
    };
    list<Arc*> arcs;
    list<Arc*> residualArcs;
    int size;
    Arc* findResidualArc(int start, int end);
    int getCapacity(int start, int end);
    int getCapacityOrCreate(int start, int end);
    void setCapacity(int start, int end, int capacity);
    list<int> getAdjacent(int start);
    unique_ptr<list<int>> dfs(int start, int end);
};

#endif // LISTGRAPH_H
