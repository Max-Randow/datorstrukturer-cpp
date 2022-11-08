/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Robot.h"
#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk(const Point& p): Robot(p){}

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;
    
    /*
     * did not crash yet
     */
    bool canMove() const;

    /*
     * Crashes and remembers it
     */
    void doCrash();

    /*
     * Return whether the robot crashed
     */
    bool justCrashed() const;

    
    
};

#endif // JUNK_H
