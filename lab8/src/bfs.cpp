#include "BasicGraph.h"
#include "costs.h"
#include "trailblazer.h"
#include<queue>
#include<unordered_set>
#include<set>
#include<algorithm>


using namespace std;

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
        vector<Vertex*> path;
        queue<Vertex*> queue;
        queue.push(start);
        start->visited = true;
        start->setColor(GREEN);
        while(!queue.empty()){

            Vertex* node = queue.front();
            queue.pop();
            if(node == end){
                while(node != start){
                    path.push_back(node);
                    node = node->previous;
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                break;
            } 
            
            
            for(Vertex* neighbour : graph.getNeighbors(node)){
                if(!neighbour->visited){
                    queue.push(neighbour);
                    neighbour->setColor(YELLOW);
                    neighbour->visited = true;
                    neighbour->setColor(GREEN);
                    neighbour->previous = node;
                }
            }

        }
    return path;
}



