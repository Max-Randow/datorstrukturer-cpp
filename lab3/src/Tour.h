// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment m_header

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
	Node* const m_head;
	int m_size;
};

#endif	// TOUR_H
