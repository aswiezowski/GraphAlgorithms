#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "Numbers.h"
#include <list>

class ListGraph: public Graph
{
	public:
		ListGraph(int size);
		virtual ~ListGraph();
		void connectVertices(int start, int end, int distance);
		int getVerticesDistance(int start, int end);
		Results* runBellmanFord(int startNode, int endNode);
	protected:

	private:
		struct Arc;
		struct Vertex{
			std::list<Arc*> arcs;
			int number;
		};
		struct Arc{
			Vertex* nextVertex;
			int distance;
			Arc();
			Arc(Vertex* nextVertex, int distance): nextVertex(nextVertex), distance(distance){}
		};
		void initVertices();
		int size;
		Vertex * vertices;
};

#endif // LISTGRAPH_H
