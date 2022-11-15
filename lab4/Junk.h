/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Author: wilmi895, maxra518
 * Description:
 * Junk is a robot which has crashed. Crashed robot, junk, cannot move.
 */


#ifndef JUNK_H
#define JUNK_H

#include <QGraphicsScene>

#include "Robot.h"
#include "Unit.h"

class Junk : public Robot {
public:
	explicit Junk(const Point& p) : Robot(p) {}

	/*
	 * Draws this junk onto the given QGraphicsScene.
	 */
	void draw(QGraphicsScene* scene) const override;

	/*
	 * did not crash yet
	 */
	bool canMove() const override;

	/*
	 * Crashes and remembers it
	 */
	void doCrash() override;

	/*
	 * Return whether the robot crashed
	 */
	bool justCrashed() const override;

	/*
	 * Take one step closer to u
	 */
	void moveTowards(const Point&) override;

	/*
	 * Clones Junk object
	 */
	Robot* clone() const override;
};

#endif	// JUNK_H
