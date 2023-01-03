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
#include "pqueue.h"

using namespace std;

vector<Node *> aStarImpl(BasicGraph& graph, Vertex* start, Vertex* end, double (*heuristic)(Vertex* const from, Vertex* const to)) {
    graph.resetData();
    return {};
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    return aStarImpl(graph, start, end, [](Vertex* const from, Vertex* const to) {
        return from->heuristic(to);
    });
}

/*
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    return aStar(graph, start, end, [](Vertex* const from, Vertex* const to) {
        return 0;
    })
}
*/

vector<Node*> constructPath(Vertex* const start, Vertex* const end) {
    vector<Vertex*> path;
    Vertex* vertex = end;

    while(vertex != start){
        path.push_back(vertex);
        vertex = vertex->previous;
    }

    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    PriorityQueue<Vertex*> queue;
    double const infinity = numeric_limits<double>::max();

    for(Vertex* const vertex : graph.getVertexSet()) {
        vertex->cost = infinity;
        queue.enqueue(vertex, infinity);
    }

    queue.changePriority(start, 0);
    start->cost = 0;
    start->visited = true;
    start->setColor(YELLOW);

    while(!queue.isEmpty()) {
        Vertex* current_vertex = queue.dequeue();
        current_vertex->setColor(GREEN);

        if(current_vertex == end) {
            return constructPath(start, end);
        }

        for(Vertex* const neighbor : graph.getNeighbors(current_vertex)){
            double const new_cost = current_vertex->cost + graph.getEdge(current_vertex, neighbor)->cost;

            if(neighbor->cost > new_cost) {
                neighbor->cost = new_cost;
                neighbor->previous = current_vertex;

                if(neighbor->visited) {
                    queue.changePriority(neighbor, new_cost);
                } else {
                    neighbor->visited = true;
                    neighbor->setColor(YELLOW);
                    queue.enqueue(neighbor, new_cost);
                }
            }
        }
    }

    return {};
}


bool depthFirstSearchImpl(BasicGraph const& graph, Vertex* const start, Vertex* const end) {
    start->visited = true;
    start->setColor(GREEN);

    if(start == end) {
        return true;
    }

    for(Vertex* const neighbor : graph.getNeighbors(start)) {
        if(!neighbor->visited && depthFirstSearchImpl(graph, neighbor, end)) {
            neighbor->previous = start;
            return true;
        }
    }

    start->setColor(GRAY);
    return false;
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    depthFirstSearchImpl(graph, start, end);

    return constructPath(start, end);
}

vector<Node*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    queue<Vertex*> queue;
    start->visited = true;
    start->setColor(YELLOW);
    queue.push(start);

    while(!queue.empty()) {
        Vertex* current_vertex = queue.front();
        queue.pop();
        current_vertex->setColor(GREEN);

        if(current_vertex == end){
            return constructPath(start, end);
        }

        for(Vertex* const neighbor : graph.getNeighbors(current_vertex)){
            if(neighbor->visited){
                continue;
            }

            neighbor->visited = true;
            neighbor->previous = current_vertex;
            neighbor->setColor(YELLOW);
            queue.push(neighbor);
        }
    }

    return {};
}
