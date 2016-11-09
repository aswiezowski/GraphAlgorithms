#include "MatrixGraph.h"
#include "limits.h"
#include <stack>
#include <algorithm>

void MatrixGraph::initGraph() {
    for(int i = 0; i<size; i++) {
        for(int j=0; j<size; j++) {
            graph[i][j] = INT_MAX;
        }
    }

    for(int i = 0; i<size; i++) {
        for(int j=0; j<size; j++) {
            residualNetwork[i][j] = INT_MAX;
        }
    }
}

MatrixGraph::MatrixGraph(const int p_Size) : Graph(p_Size) {
    this->size = p_Size;
    graph = new int *[size];
    for(int i=0; i<size; i++) {
        graph[i] = new int[size];
    }
    residualNetwork = new int *[size];
    for(int i=0; i<size; i++) {
        residualNetwork[i] = new int[size];
    }
    initGraph();
}

MatrixGraph::~MatrixGraph() {
    for(int i=0; i<size; i++) {
        delete graph[i];
    }
    delete graph;
}

void MatrixGraph::connectVertices(int start, int end, int distance) {
    graph[start][end]=distance;
}

int MatrixGraph::getVerticesDistance(int start, int end) {
    return graph[start][end];
}

int MatrixGraph::getVerticesCapacity(int start, int end) {
    return residualNetwork[start][end];
}

Results* MatrixGraph::runBellmanFord(int startNode, int endNode) {
    distance[startNode] = 0;

    for(int i = 0; i< size-1; i++) {
        for(int u = 0; u<size; u++) {
            for(int v=0; v<size; v++) {
                int vDistance = getVerticesDistance(u, v);
                if(Numbers::isAdditionisSafe(distance[u], vDistance) && distance[v]> distance[u] + vDistance) {
                    distance[v] = distance[u] + vDistance;
                    previous[v] = u;
                }
            }
        }
    }
    return new Results(distance, previous);
}

unique_ptr<list<int>> MatrixGraph::dfs(int start, int end) {
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
        for(int i=0; i<size; i++) {
            if(getVerticesCapacity(current, i)==INT_MAX) {
                continue;
            }
            if(visited[i]==false && getVerticesCapacity(current, i)>0) {
                adjacent.push(i);
                previous[i] = current;
                visited[i] = true;
            }
        }

    }
    return route;
}

int MatrixGraph::runFordFulkerson(int start, int end) {

    for(int i = 0; i<size; i++) {
        for(int j = 0; j<size; j++) {
            if(graph[i][j] == INT_MAX) {
                residualNetwork[i][j] = 0;
            } else {
                residualNetwork[i][j]= graph[i][j];
            }

        }
    }
    int maxFlow = 0;
    unique_ptr<list<int>> route = dfs(start,end);
    while(!route->empty()) {
        int pathFlow = INT_MAX;
        list<int>::iterator itLast = route->end();
        --itLast;
        for(list<int>::iterator it=route->begin() ; it != itLast; ++it) {
            pathFlow = min(pathFlow, residualNetwork[*it][*next(it)]);
        }

        for(list<int>::iterator it=route->begin() ; it != itLast; ++it) {
            residualNetwork[*it][*next(it)] -= pathFlow;
            residualNetwork[*next(it)][*it] += pathFlow;
        }

        maxFlow += pathFlow;

        route = dfs(start,end);
    }
    return maxFlow;

}
