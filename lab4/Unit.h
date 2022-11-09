/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 *
 * Author: wilmi895, maxra518
 * Description:
 * Unit is the base class for entities in the game. Defines
 * basic movement, position and draw functionality.
 */

#ifndef UNIT_H
#define UNIT_H

#include <QGraphicsScene>

#include "utilities.h"

/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:
    /*
     * Create a unit at a random position
     */
    Unit();

    /*
     * Create unit at given point
     */
    explicit Unit(const Point& p);

    virtual ~Unit() = default;

    /*
     * Return Point representation of Unit
     */
    Point asPoint() const;

    /*
     * Am I in the same square as u?
     */
    bool at(const Unit& u) const;


    /*
     * Take one step closer to u
     */
    virtual void moveTowards(const Unit&);


    /*
     * Teleport. Does not check for collision
     */
    void teleport();

    /*
     * Euclidean distance to u
     */
    double distanceTo(const Unit& u) const;

    /*
     * Draw object to scene
     */
    virtual void draw(QGraphicsScene* scene) const;

private:
    int x;	// x position of this unit
    int y;	// y position of this unit

    // private helpers
    void checkBounds();
};

#endif	// UNIT_H
