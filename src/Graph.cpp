#include "Graph.h"

#include "limits.h"
#include "Numbers.h"

Graph::Graph(int size)
{
	distance = new int [size];
	previous = new int [size];

	for(int i = 0; i<size; i++){
		distance[i] = INT_MAX;
		previous[i] = -1;
	}
}

Graph::~Graph()
{
	//dtor
}
