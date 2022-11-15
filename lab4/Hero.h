/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Author: wilmi895, maxra518
 * Description:
 * Hero is the playable character. Defines method to draw hero to screen.
 */

#ifndef HERO_H
#define HERO_H

#include <QGraphicsScene>

#include "Unit.h"

class Hero : public Unit {
public:
	/*
	 * Draws this hero onto the given QGraphicsScene.
	 */
	void draw(QGraphicsScene* scene) const override;
	Hero* clone() const override;
};

#endif	// HERO_H
