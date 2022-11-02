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
double Tour::distance() const noexcept {
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
		double const rel_distance =
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

/*
 * Swaps two node segments. Follows the swap algorithm described by the 2opt tsp
 * algorithm. Wiki: https://en.wikipedia.org/wiki/2-opt
 */
void Tour::twoOptSwap(Node* const segment1, Node* const segment2) noexcept {
	Node* const p1	   = segment1;
	Node* const p2	   = segment1->next;
	Node* const p3	   = segment2;
	Node* const p4	   = segment2->next;
	Node* current_node = p2;  // p2
	Node* next_node	   = p2->next;
	Node* prev_node	   = p4;

	while (current_node != p4) {
		// Reverse current node's pointer
		current_node->next = prev_node;
		// Move pointers one position ahead.
		prev_node	 = current_node;
		current_node = next_node;
		// Store next node
		next_node = next_node->next;
	}
	p1->next = p3;
}

/*
 * Checks if two 2D line segments intersects.
 * Segments here being two nodes with respective connected node.
 * See wiki:
 * https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment
 */
bool Tour::intersects(Node const* const segment1,
					  Node const* const segment2) noexcept {
	if (segment1 == segment2 || segment1->next == segment2 ||
		segment2->next == segment1) {
		return false;
	}
	Point const p1 = segment1->point;
	Point const p2 = segment1->next->point;
	Point const p3 = segment2->point;
	Point const p4 = segment2->next->point;

	double const denom =
		(p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

	if (denom == 0.0) {
		return false;
	}

	double const t =
		((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / denom;
	double const u =
		((p1.x - p3.x) * (p1.y - p2.y) - (p1.y - p3.y) * (p1.x - p2.x)) / denom;

	return (0.0 <= t) && (t <= 1.0) && (0.0 <= u) && (u <= 1.0);
}

/*
 * Inserts using insertSmallest algorithms and then swaps nodes to remove line
 * intersections.
 */
void Tour::insertNoIntersections(Point const p) {
	insertSmallest(p);

	Node* current_node = m_head;

	do {
		Node* node = current_node;

		do {
			if (intersects(current_node, node)) {
				twoOptSwap(current_node, node);
			}
			node = node->next;
		} while (node != m_head);

		current_node = current_node->next;
	} while (current_node != m_head);
}
