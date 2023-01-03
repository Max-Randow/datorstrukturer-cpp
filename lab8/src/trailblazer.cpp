/*
 * Authors: wilmi895 maxra518
 * Usage:
 *
 */

#include "costs.h"
#include "trailblazer.h"
#include "BasicGraph.h"
#include <queue>
#include <algorithm>

using namespace std;

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}


bool depthFirstSearchImpl(BasicGraph& graph, Vertex* start, Vertex* end, vector<Vertex*>& path) {
    start->visited = true;
    start->setColor(GREEN);

    if(start == end) {
        return true;
    }

    for(Vertex* const neighbor : graph.getNeighbors(start)) {
        if(!neighbor->visited && depthFirstSearchImpl(graph, neighbor, end, path)) {
            path.push_back(neighbor);
            return true;
        }
    }

    start->setColor(GRAY);
    return false;
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    vector<Vertex*> path;

    depthFirstSearchImpl(graph, start, end, path);
    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}


using namespace std;

vector<Node*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    vector<Vertex*> path;
    queue<Vertex*> queue;
    start->visited = true;
    start->setColor(YELLOW);
    queue.push(start);

    while(!queue.empty()) {
        Vertex* current_vertex = queue.front();
        queue.pop();
        current_vertex->setColor(GREEN);

        if(current_vertex == end){
            while(current_vertex != start){
                path.push_back(current_vertex);
                current_vertex = current_vertex->previous;
            }

            path.push_back(start);
            reverse(path.begin(), path.end());
            break;
        }

        for(Vertex* const neighbour : graph.getNeighbors(current_vertex)){
            if(neighbour->visited){
                continue;
            }

            neighbour->visited = true;
            neighbour->previous = current_vertex;
            neighbour->setColor(YELLOW);
            queue.push(neighbour);
        }
    }

    return path;
}
