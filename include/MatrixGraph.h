#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Results.h"
#include "Numbers.h"
#include "Graph.h"
#include <memory>
#include <list>

using namespace std;

class MatrixGraph : public Graph {
public:
    MatrixGraph(int size);
    ~MatrixGraph();
    void connectVertices(int start, int end, int distance);
    int getVerticesDistance(int start, int end);
    Results* runBellmanFord(int startNode, int endNode);
    int runFordFulkerson(int start, int end);
protected:

private:
    int **graph;
    int **residualNetwork;
    int size;
    void initGraph();
    int getVerticesCapacity(int start, int end);
    unique_ptr<list<int>> dfs(int start, int end);

};

#endif // MATRIXGRAPH_H
