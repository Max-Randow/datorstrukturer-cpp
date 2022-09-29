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


Tour::Tour() {}

Tour::Tour(Point const a, Point const b, Point const c, Point const d) {
	Node* tmp_node4 = new Node(d);
	Node* tmp_node3 = new Node(c, tmp_node4);
	Node* tmp_node2 = new Node(b, tmp_node3);
	head			= new Node(a, tmp_node2);
	tmp_node4->next = head;
}

Tour::~Tour() {
	// TODO: write this member
}

/*
 * Draws out tour
 */
void Tour::show() const {
	if (head == nullptr) {
		return;
	}
	Node const* current_node = head;

	do {
		cout << "Current node: " << current_node->point.toString() << endl;
		current_node = current_node->next;
	} while (current_node != head);
}

void Tour::draw(QGraphicsScene* scene) const {
	if (head == nullptr) {
		return;
	}
	Node const* current_node = head;

	do {
		current_node->point.drawTo(current_node->next->point, scene);
		current_node = current_node->next;
	} while (current_node != head);
}

/*
 * Returns size of tour
 */
int Tour::size() const {
	if (head == nullptr) {
		return 0;
	}
	int tour_size			 = 0;
	Node const* current_node = head;

	do {
		tour_size++;
		current_node = current_node->next;
	} while (current_node != head);
	return tour_size;
}

double Tour::distance() const {
	if (head == nullptr) {
		return 0.0;
	}
	double total_distance	 = 0.0;
	Node const* current_node = head;

	do {
		total_distance +=
			current_node->point.distanceTo(current_node->next->point);
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
