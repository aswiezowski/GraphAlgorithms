#include "ListGraph.h"

#include "limits.h"
#include <stack>
#include <algorithm>

ListGraph::ListGraph(int size) : Graph(size) {
    this->size = size;
}

ListGraph::~ListGraph() {
}

void ListGraph::connectVertices(int start, int end, int distance) {
    arcs.push_back(new Arc(start, end, distance));
}

int ListGraph::getVerticesDistance(int start, int end) {
    throw "No ";
}


Results* ListGraph::runBellmanFord(int startNode, int endNode) {
    distance[startNode] = 0;

    for(int i = 0; i< size-1; i++) {
        for (list<Arc*>::iterator it=arcs.begin(); it!=arcs.end(); ++it) {
            int vDistance = (*it)->distance;
            int u = (*it)->start;
            int v = (*it)->end;
            if(Numbers::isAdditionisSafe(distance[u], vDistance) && distance[v]> distance[u] + vDistance) {
                distance[v] = distance[u] + vDistance;
                previous[v] = u;
            }
        }
    }
    return new Results(distance, previous);
}

int ListGraph::runFordFulkerson(int start, int end) {
    for (list<Arc*>::iterator it=arcs.begin(); it!=arcs.end(); ++it) {
        residualArcs.push_back(new Arc(**it));
    }

    int maxFlow = 0;
    unique_ptr<list<int>> route = dfs(start,end);
    while(!route->empty()) {
        int pathFlow = INT_MAX;
        list<int>::iterator itLast = route->end();
        --itLast;
        for(list<int>::iterator it=route->begin() ; it != itLast; ++it) {
            pathFlow = min(pathFlow, getCapacity(*it, *next(it)));
        }

        for(list<int>::iterator it=route->begin() ; it != itLast; ++it) {
            setCapacity(*it, *next(it), getCapacityOrCreate(*it, *next(it))-pathFlow);
            setCapacity(*next(it), *it, getCapacityOrCreate(*next(it), *it)+pathFlow);
        }

        maxFlow += pathFlow;

        route = dfs(start,end);
    }
    return maxFlow;

}

int ListGraph::getCapacity(int start, int end) {
    Arc *arc = findResidualArc(start, end);
    if(arc==NULL) {
        throw "No arc found";
    }
    return arc->distance;
}

ListGraph::Arc* ListGraph::findResidualArc(int start, int end) {
    for (list<Arc*>::iterator it=residualArcs.begin(); it!=residualArcs.end(); ++it) {
        if((*it)->start == start && (*it)->end == end) {
            return *it;
        }
    }
    return NULL;
}

int ListGraph::getCapacityOrCreate(int start, int end) {
    Arc *arc = findResidualArc(start, end);
    if(arc==NULL) {
        arc = new Arc(start,end, 0);
    }
    return arc ->distance;
}

void ListGraph::setCapacity(int start, int end, int capacity) {
    Arc *arc = findResidualArc(start, end);
    if(arc == NULL) {
        residualArcs.push_back(new Arc(start,end, capacity));
    } else {
        arc->distance = capacity;
    }
}

unique_ptr<list<int>> ListGraph::dfs(int start, int end) {
    stack<int> adjacent;
    bool visited[size] = {false};

    adjacent.push(start);
    visited[start] = true;
    unique_ptr<list<int>> route(new list<int>);
    while(!adjacent.empty()) {
        int current = adjacent.top();
        adjacent.pop();

        if(current == end) {
            for(int i=end; i!=start; i = previous[i]) {
                route->push_front(i);
            }
            route->push_front(start);
            return route;
        }
        list<int> currentAdjacent = getAdjacent(current);
        for (list<int>::iterator it=currentAdjacent.begin(); it!=currentAdjacent.end(); ++it) {
            if(visited[*it]==false && getCapacity(current, *it)>0) {
                adjacent.push(*it);
                previous[*it] = current;
                visited[*it] = true;
            }
        }
    }
    return route;
}

list<int> ListGraph::getAdjacent(int start) {
    list<int> adjacent;
    for (list<Arc*>::iterator it=residualArcs.begin(); it!=residualArcs.end(); ++it) {
        if((*it)->start == start) {
            adjacent.push_back((*it)->end);
        }
    }
    return adjacent;
}
