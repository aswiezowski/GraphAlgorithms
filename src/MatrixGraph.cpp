#include "MatrixGraph.h"
#include "limits.h"

void MatrixGraph::initGraph(){
	for(int i = 0; i<size; i++){
		for(int j=0;j<size; j++){
				graph[i][j] = INT_MAX;
			}
	}
}

MatrixGraph::MatrixGraph(const int p_Size) : Graph(p_Size)
{
	this->size = p_Size;
	graph = new int *[size];
	for(int i=0;i<size; i++){
		graph[i] = new int[size];
	}
	initGraph();
}

MatrixGraph::~MatrixGraph(){
	for(int i=0;i<size; i++){
		delete graph[i];
	}
	delete graph;
}

void MatrixGraph::connectVertices(int start, int end, int distance){
	graph[start][end]=distance;
}

int MatrixGraph::getVerticesDistance(int start, int end){
	return graph[start][end];
}

Results* MatrixGraph::runBellmanFord(int startNode, int endNode){
	distance[startNode] = 0;

	for(int i = 0; i< size-1; i++){
		for(int u = 0;u<size;u++){
			for(int v=0; v<size; v++){
				int vDistance = getVerticesDistance(u, v);
				if(Numbers::isAdditionisSafe(distance[u], vDistance) && distance[v]> distance[u] + vDistance){
					distance[v] = distance[u] + vDistance;
					previous[v] = u;
				}
			}
		}
	}
	return new Results(distance, previous);
}
