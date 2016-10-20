#include "limits.h"
#include <iostream>
#include <list>
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "Results.h"

int main(){
    const int vSize=5;

    Graph* graph = new ListGraph(vSize);
    graph->connectVertices(0, 1, 2);
    graph->connectVertices(0, 4, 1);
    graph->connectVertices(1, 2, 1);
    graph->connectVertices(2, 3, 2);
    graph->connectVertices(4, 2, 1);
    graph->connectVertices(4, 3, 4);

	int startNode = 0;
	int endNode = 3;

    Results* results = graph->runBellmanFord(startNode, endNode);

    int *distance = results->getDistances();
	int *previous = results->getPreviouses();

	for(int i = 0; i!= vSize; i++){
		std::cout<< "distance["<<i<<"]="<<distance[i]<<"\t"<<"previous["<<i<<"]="<<previous[i]<<std::endl;
	}

	std::list<int> route;
	std::cout<<"\nRoute: ";
	for(int i = endNode; i!= startNode; i=previous[i]){
		route.push_front(i);
	}
	route.push_front(startNode);

	for (std::list<int>::iterator it=route.begin(); it!=route.end(); ++it){
		std::cout<< *it <<" ("<<distance[*it]<<") -> ";
	}
	std::cout<<"\n";

	std::cout<< "Distance: " << distance[endNode] <<"\n";

}
