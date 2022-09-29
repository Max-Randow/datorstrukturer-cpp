// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Tour.h"

#include <iostream>

#include "Node.h"
#include "Point.h"

using namespace std;


Tour::Tour() {
    head = nullptr;
    
}
    
Tour::Tour(Point a, Point b, Point c, Point d){
    Node* tmp_node4 = new Node(d);
    Node* tmp_node3 = new Node(c, tmp_node4);
    Node* tmp_node2 = new Node(b, tmp_node3);
    head            = new Node(a, tmp_node2);
    tmp_node4->next = head;
    
}

Tour::~Tour() {
	// TODO: write this member
}

/*
 * Draws out tour
 */
void Tour::show() {
    Node* current_node = head;
    if(current_node == nullptr){
        return;
    }
    do{
        cout<<"Current node: "<< current_node->point.toString() <<endl;
        current_node = current_node->next;
    } while (current_node != head);

}

void Tour::draw(QGraphicsScene* scene) {
    Node* current_node = head;
    if(current_node == nullptr){
        return;
    }
    do{
        current_node->point.drawTo(current_node->next->point, scene);  
   } while (current_node != head);


}

/*
 * Returns size of tour
 */
int Tour::size() {
	int tour_size = 0;
    Node* current_node = head;
    if(current_node == nullptr){
        return 0;
    }
    do{
        tour_size++;
        current_node = current_node->next;
    } while (current_node != head);
    return tour_size;
}

double Tour::distance() {
    double total_distance = 0.0;
    Node* current_node = head;
    if(current_node == nullptr){
        return 0.0;
    }
    do{
        total_distance += current_node->point.distanceTo(current_node->next->point);
        current_node = current_node->next;
    } while (current_node != head);

    return total_distance;

}

void Tour::insertNearest(Point const p) {
	// TODO: write this member
}

void Tour::insertSmallest(Point const p) {
	// TODO: write this member
}
