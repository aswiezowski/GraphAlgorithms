#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Results.h"
#include "Numbers.h"
#include "Graph.h"

class MatrixGraph : public Graph
{
	public:
		MatrixGraph(int size);
		~MatrixGraph();
		void connectVertices(int start, int end, int distance);
		int getVerticesDistance(int start, int end);
		Results* runBellmanFord(int startNode, int endNode);
	protected:

	private:
		int **graph;
		int size;
		void initGraph();
};

#endif // MATRIXGRAPH_H
