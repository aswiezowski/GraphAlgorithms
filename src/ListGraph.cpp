#include "ListGraph.h"

ListGraph::ListGraph(int size) : Graph(size)
{
	this->size = size;
	initVertices();
}

void ListGraph::initVertices(){
	vertices = new Vertex[size];
	for(int i = 0; i<size; i++){
		vertices[i].number = i;
	}
}


ListGraph::~ListGraph()
{
	delete [] vertices;
}

void ListGraph::connectVertices(int start, int end, int distance){
	vertices[start].arcs.push_back(new Arc(&vertices[end], distance));
}

int ListGraph::getVerticesDistance(int start, int end){
	/*std::list<Arc*> arcs = vertices[start].arcs;
	for (std::list<Arc*>::iterator it=arcs.begin(); it!=arcs.end(); ++it){
		if((*it)->nextVertex == vertices[end]){
			return (*it)->distance;
		}
	}
*/
	throw "No ";
}


Results* ListGraph::runBellmanFord(int startNode, int endNode){
	distance[startNode] = 0;

	for(int i = 0; i< size-1; i++){
		for(int u = 0;u<size;u++){
			std::list<Arc*> arcs = vertices[u].arcs;
			for (std::list<Arc*>::iterator it=arcs.begin(); it!=arcs.end(); ++it){
				int vDistance = (*it)->distance;
				int v = (*it)->nextVertex->number;
				if(Numbers::isAdditionisSafe(distance[u], vDistance) && distance[v]> distance[u] + vDistance){
					distance[v] = distance[u] + vDistance;
					previous[v] = u;
				}
			}
		}
	}
	return new Results(distance, previous);
}
