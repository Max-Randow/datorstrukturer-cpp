/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"

#include <iostream>

#include "Robot.h"
#include "constants.h"
#include "utilities.h"


GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        auto* robot = new Robot();
        while (!isEmpty(*robot)) {
            delete robot;
            robot = new Robot();
        }
        robots.push_back(robot);
    }
    teleportHero();
}

GameState::~GameState() {
    // Crash without copy constructors.
    for (Robot* robot : robots) {
        delete robot;
    }
}

GameState::GameState(const GameState& gameState) {
    for (const Robot* robot : gameState.robots) {
        robots.push_back(robot->clone());
    }
    hero = gameState.hero;
}
// Copy assignment
GameState& GameState::operator=(const GameState& other) {
    for (Robot* robot : robots) {
        delete robot;
    }

    robots.resize(other.robots.size());

    for (unsigned i = 0; i < robots.size(); i++) {
        robots[i] = other.robots[i]->clone();
    }
    hero = other.hero;

    return *this;
}
GameState::GameState(GameState&& gameState){
    robots = std::move(gameState.robots);
    hero = std::move(gameState.hero);
    gameState.robots.clear();

}
GameState& GameState::operator=(GameState&& other){
    for (Robot* robot : robots) {
        delete robot;
    }

    robots = std::move(other.robots);
    hero = std::move(other.hero);
    other.robots.clear();
    //other.robots.shrink_to_fit();

    return *this;
    
} 



void GameState::draw(QGraphicsScene* scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Robot* robot : robots) {
        robot->draw(scene);
    }
}

void GameState::teleportHero() {
    do {
        hero.teleport();
    } while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (Robot* robot : robots) {
        robot->moveTowards(hero);
    }
}

void GameState::updateCrashes() {
    for (unsigned i = 0; i < robots.size(); ++i) {
        for (unsigned o = i + 1; o < robots.size(); ++o) {
            if (robots[i]->at(*robots[o])) {
                robots[i]->doCrash();
                robots[o]->doCrash();
            }
        }
    }
}

int GameState::countJustCrashed() const {
    int numberDestroyed = 0;
    for (unsigned i = 0; i < robots.size(); ++i) {
        if (robots[i]->justCrashed()) {
            numberDestroyed++;
        }
    }
    return numberDestroyed;
}

void GameState::junkTheCrashed() {
    for (unsigned i = 0; i < robots.size(); ++i) {
        if (robots[i]->justCrashed()) {
            const Point p = robots[i]->asPoint();
            delete robots[i];
            robots[i] = new Junk(p);
        }
    }
}

bool GameState::stillLiveRobots() const {
    for (unsigned i = 0; i < robots.size(); ++i) {
        if (robots[i]->canMove()) {
            return true;
        }
    }
    return false;
}


bool GameState::heroDead() const {
    for (const Robot* robot : robots) {
        if (hero.at(*robot)) {
            return true;
        }
    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const { return hero.asPoint(); }

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for (const Robot* robot : robots) {
        if (robot->at(unit)) {
            return false;
        }
    }
    return true;
}
