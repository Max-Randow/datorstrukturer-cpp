/*
 * Authors: wilmi895 maxra518
 * Usage:
 * Implements graph search algorithms.
 * Depth and Breadth first search as well as dijkstras and A*.
 */

#include "costs.h"
#include "trailblazer.h"
#include "BasicGraph.h"
#include <queue>
#include <algorithm>
#include "pqueue.h"

using namespace std;

/*
 * Reconstructs a path between start and end vertex, returns this path.
 */
vector<Node*> constructPath(Vertex* const start, Vertex* const end) {
    vector<Vertex*> path;
    Vertex* vertex = end;

    while(vertex != start) {
        path.push_back(vertex);
        vertex = vertex->previous;
    }

    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

/*
 * A* algorithms implementation. Takes a graph, start node, end node and a
 * heuristic function to calculate visit priority.
 */
vector<Node *> aStarImpl(BasicGraph& graph, Vertex* start, Vertex* end, double (*heuristic)(Vertex* const from, Vertex* const to)) {
    graph.resetData();

    PriorityQueue<Vertex*> queue;

    for(Vertex* const vertex : graph.getVertexSet()) {
        vertex->cost = POSITIVE_INFINITY;
    }

    start->cost = 0;
    start->visited = true;
    start->setColor(YELLOW);
    queue.enqueue(start, heuristic(start, end));

    while(!queue.isEmpty()) {
        Vertex* current_vertex = queue.dequeue();
        current_vertex->visited = true;
        current_vertex->setColor(GREEN);

        // Reached end vertex, return path between start and end.
        if(current_vertex == end) {
            return constructPath(start, end);
        }

        for(Vertex* const neighbor : graph.getNeighbors(current_vertex)){
            if(neighbor->visited) {
                continue;
            }

            double const new_cost = current_vertex->cost + graph.getEdge(current_vertex, neighbor)->cost;
            double& neighborCost = neighbor->cost;

            // Update queue if a better cost to neighbor has been found.
            if(new_cost < neighborCost) {
                if(neighborCost != POSITIVE_INFINITY) {
                    queue.changePriority(neighbor, new_cost + heuristic(neighbor, end));
                } else {
                    neighbor->setColor(YELLOW);
                    queue.enqueue(neighbor, new_cost + heuristic(neighbor, end));
                }

                neighborCost = new_cost;
                neighbor->previous = current_vertex;
            }
        }
    }
    return {};
}

/*
 * A* algorithm using a vertex defined heuristic function.
 */
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    return aStarImpl(graph, start, end, [](Vertex* const from, Vertex* const to) {
        return from->heuristic(to);
    });
}

/*
 * Dijkstras algorithm using A* implementation but with 0 cost heuristic
 * to get dijkstras.
 */
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    return aStarImpl(graph, start, end, [](Vertex* const, Vertex* const) noexcept {
        return 0.0;
    });
}

/*
 * Depth first search algorithm implementation. Returns true if a path was found.
 */
bool depthFirstSearchImpl(BasicGraph const& graph, Vertex* const start, Vertex* const end) {
    start->visited = true;
    start->setColor(GREEN);

    // Found a path.
    if(start == end) {
        return true;
    }

    for(Vertex* const neighbor : graph.getNeighbors(start)) {
        // If this neighbor has not been visited and the recursive search step found a path.
        if(!neighbor->visited && depthFirstSearchImpl(graph, neighbor, end)) {
            neighbor->previous = start;
            return true;
        }
    }

    start->setColor(GRAY);
    return false;
}

/*
 * Depth first search algorithm. Returns a path if found between start and end.
 */
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    bool const pathFound = depthFirstSearchImpl(graph, start, end);

    if(pathFound) {
        return constructPath(start, end);
    }

    return {};
}

/*
 * Breadth first search algorithm. Returns a path if found between start and end.
 */
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

        // Reached end vertex, return path between start and end.
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
