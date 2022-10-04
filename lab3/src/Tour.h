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
	double distance() const;
	void insertNearest(Point p);
	void insertSmallest(Point p);

private:
	Node* m_head;
};

#endif	// TOUR_H
