/*
 * Author: wilmi895, maxra518
 * Description:
 * Tour describes a circular list of nodes with coordinate points.
 * Algorithms for tsp problem is defined in the class for inserting.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"


class Tour {
public:
	Tour() noexcept;
	Tour(Point a, Point b, Point c, Point d);
	~Tour();
	void show() const noexcept;
	void draw(QGraphicsScene* scene) const;
	int size() const noexcept;
	double distance() const noexcept;
	void insertNearest(Point p);
	void insertSmallest(Point p);
	void insertNoIntersections(Point p);

private:
	Node* m_head;

	static void twoOptSwap(Node* const segment1, Node* const segment2) noexcept;
	static bool intersects(Node const* const segment1,
						   Node const* const segment2) noexcept;
};

#endif	// TOUR_H
