/*
 * Author: wilmi895, maxra518
 * Description:
 * Tour describes a circular list of nodes with coordinate points.
 * Algorithms for tsp problem is defined in the class for inserting.
 */

#include "Tour.h"

#include <cmath>
#include <iostream>
#include <limits>

#include "Node.h"
#include "Point.h"

using namespace std;

/*
 * Default constructor.
 */
Tour::Tour() noexcept : m_head(nullptr) {}

/*
 * Helper constructor for testing 4 points.
 */
Tour::Tour(Point const a, Point const b, Point const c, Point const d) :
	m_head(new Node(a, nullptr)) {
	m_head->next			 = new Node(b);
	m_head->next->next		 = new Node(c);
	m_head->next->next->next = new Node(d, m_head);
}

/*
 * Destructor deallocates all nodes in tour.
 */
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

/*
 * Draws Tour to a scene.
 */
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
}

/*
 * Calculates the distance of tour.
 */
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
/*
 * Inserts node to nearest node to P
 */
void Tour::insertNearest(Point const p) {
	if (m_head == nullptr) {
		m_head		 = new Node(p);
		m_head->next = m_head;
		return;
	}
	double closest_distance = numeric_limits<double>::max();
	Node* closest_node		= nullptr;
	Node* current_node		= m_head;

	do {
		// Choose the nearest point.
		double const tmp_distance = current_node->point.distanceTo(p);
		if (tmp_distance < closest_distance) {
			closest_node	 = current_node;
			closest_distance = tmp_distance;
		}
		current_node = current_node->next;
	} while (current_node != m_head);

	closest_node->next = new Node(p, closest_node->next);
}

/*
 * Inserts node where the total distance is increased minimally.
 */
void Tour::insertSmallest(Point const p) {
	if (m_head == nullptr) {
		m_head		 = new Node(p);
		m_head->next = m_head;
		return;
	}
	double min_rel_distance = numeric_limits<double>::max();
	Node* current_node		= m_head;
	Node* chosen_node		= nullptr;

	do {
		// Calculate relative difference when inserting p.
		double rel_distance =
			current_node->point.distanceTo(p) +
			p.distanceTo(current_node->next->point) -
			current_node->point.distanceTo(current_node->next->point);

		// Choose minimal distance change.
		if (rel_distance < min_rel_distance) {
			min_rel_distance = rel_distance;
			chosen_node		 = current_node;
		}
		current_node = current_node->next;
	} while (current_node != m_head);

	chosen_node->next = new Node(p, chosen_node->next);
}
