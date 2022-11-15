/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Author: wilmi895, maxra518
 * Description:
 * Maintains the game state:  Location of all robots, junk and hero.
 * Junks crashed robots, draws playing field, and contains hero status + helper
 * methods.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QGraphicsScene>
#include <string>
#include <vector>

#include "Hero.h"
#include "Junk.h"
#include "Robot.h"
#include "Unit.h"

class GameState {
public:
	/*
	 * Create a GameState with randomly placed, but not
	 * overlapping hero and numberOfRobots robots
	 */
	explicit GameState(int numberOfRobots);

	~GameState();
	// Copy constuctor
	GameState(const GameState& gameState);
	GameState& operator=(const GameState& other);
	// Move semantics
	GameState(GameState&& gameState) noexcept;
	GameState& operator=(GameState&& other) noexcept;


	/*
	 * Clear and redraw entire playing field
	 */
	void draw(
		QGraphicsScene* scene) const;  // Clear and redraw entire playing field

	/*
	 * Teleport hero to random location
	 */
	void teleportHero();

	/*
	 * Move robots one step towards hero
	 */
	void moveRobots();

	/*
	 * Identify crashed robots
	 */
	void updateCrashes();

	/*
	 * Count identified crashed robots
	 */
	int countJustCrashed() const;

	/*
	 * Replace each identified crashed robot with a junk
	 */
	void junkTheCrashed();

	/*
	 * Are there still robots that did not crash?
	 */
	bool stillLiveRobots() const;

	/*
	 * Is hero in same place as robot or junk?
	 */
	bool heroDead() const;

	/*
	 * Move hero towards dir
	 */
	void moveHeroTowards(const Point& dir);

	/*
	 * Return hero
	 */
	Point getHeroAsPoint() const;

private:
	std::vector<Robot*> robots;	 // the robots
	// std::vector<Junk> junks;    // robots that have turned to junk
	Hero hero;	// the hero

	// private helpers
	bool isEmpty(const Unit& unit) const;
};

#endif	// GAMESTATE_H
