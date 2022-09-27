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
    head = new Node(Point {0,0});
    head->next = head;
    
}
    
Tour::Tour(Point a, Point b, Point c, Point d){
    Node* tmp_node4 = new Node(d);
    Node* tmp_node3 = new Node(c, tmp_node4);
    Node* tmp_node2 = new Node(b, tmp_node3);
    Node* tmp_node1 = new Node(a, tmp_node2);
    head            = new Node({0,0}, tmp_node1);
    tmp_node4->next = head;
    
}

Tour::~Tour() {
	// TODO: write this member
}

/*
 * Draws out tour
 */
void Tour::show() {
    Node* current_node;
    for(current_node = head->next; current_node != head; current_node = current_node->next){
        cout<< "Current point "<<current_node->point.toString() <<endl;        
    } 
}

void Tour::draw(QGraphicsScene* scene) {
	// TODO: write this member
}

/*
 * Returns size of tour
 */
int Tour::size() {
	int tour_size = 0;
    Node* current_node;
    for(current_node = head->next; current_node != head; current_node = current_node->next){
        ++size;
    }
    return size;
}

double Tour::distance() {
	// TODO: write this member
	return 0.0;
}

void Tour::insertNearest(Point p) {
	// TODO: write this member
}

void Tour::insertSmallest(Point p) {
	// TODO: write this member
}
