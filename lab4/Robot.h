/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Author: wilmi895, maxra518
 * Description:
 * Robot moves around and moves toward player. Rembembers if it has crashed.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsScene>

#include "Unit.h"

class Robot : public Unit {
	bool crashed = false;

public:
	explicit Robot(const Point& p) : Unit(p) {}

	Robot() = default;

	/*
	 * did not crash yet
	 */
	virtual bool canMove() const;

	/*
	 * Crashes and remembers it
	 */
	virtual void doCrash();

	/*
	 * Return whether the robot crashed
	 */
	virtual bool justCrashed() const;

	/*
	 * Draws this robot onto the given QGraphicsScene.
	 */
	virtual void draw(QGraphicsScene* scene) const override;

	/*
	 * Clones Robot object
	 */
	virtual Robot* clone() const override;
};

#endif	// ROBOT_H
