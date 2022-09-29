// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment m_header

#include "Tour.h"

#include <iostream>

#include "Node.h"
#include "Point.h"

using namespace std;

Tour::Tour() noexcept : m_head(nullptr), m_size(0) {}

Tour::Tour(Point const a, Point const b, Point const c, Point const d) :
	m_head(new Node(a, nullptr)), m_size(4) {
	m_head->next			 = new Node(b);
	m_head->next->next		 = new Node(c);
	m_head->next->next->next = new Node(d, m_head);
}

Tour::~Tour() {
	if (m_head == nullptr) {
		return;
	}
	Node const* current_node = m_head;

	do {
		Node const* const next_node = current_node->next;
		delete current_node;
		current_node = next_node;
	} while (current_node != m_head);
}

/*
 * Draws out tour
 */
void Tour::show() const noexcept {
	if (m_head == nullptr) {
		return;
	}
	Node const* current_node = m_head;

	do {
		cout << current_node->point.toString() << endl;
		current_node = current_node->next;
	} while (current_node != m_head);
}

void Tour::draw(QGraphicsScene* const scene) const {
	if (m_head == nullptr) {
		return;
	}
	Node const* current_node = m_head;

	do {
		current_node->point.drawTo(current_node->next->point, scene);
		current_node = current_node->next;
	} while (current_node != m_head);
}

/*
 * Returns size of tour
 */
int Tour::size() const noexcept {
	/*
	if (m_head == nullptr) {
		return 0;
	}
	int tour_size			 = 0;
	Node const* current_node = m_head;

	do {
		tour_size++;
		current_node = current_node->next;
	} while (current_node != m_head);
	return tour_size;
	*/

	return m_size;
}

double Tour::distance() const {
	if (m_head == nullptr) {
		return 0.0;
	}
	double total_distance	 = 0.0;
	Node const* current_node = m_head;

	do {
		total_distance +=
			current_node->point.distanceTo(current_node->next->point);
		current_node = current_node->next;
	} while (current_node != m_head);

	return total_distance;
}

void Tour::insertNearest(Point const p) {
	m_size++;
	// TODO: write this member
}

void Tour::insertSmallest(Point const p) {
	m_size++;
	// TODO: write this member
}
