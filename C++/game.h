//
//  game.h
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef game_hpp
#define game_hpp

// import
#include <iostream> // debugging
#include <stdio.h>
#include <vector> // dynamic arrays
#include <map> // held keys
#include <cmath>

#include "vector/vector.h" // point
#include "ui/uiInteract.h" // user interaction

// import game objects
#include "game objects/moving objects/movingObject.h"
#include "game objects/moving objects/ship.h"
#include "game objects/moving objects/laser.h"
#include "game objects/ui (objects)/score.h"
#include "game objects/ui (objects)/level.h"
#include "game objects/moving objects/rocks.h"

class Game {
private:
    // screen positioning
    double screenLeft;
    double screenRight;
    double screenBottom;
    double screenTop;
    Position center;
    
    // game objects
    Ship* ship;
    std::vector<Laser> lasers;
    std::vector<Rock*> rocks;
    Level level;
    Score score;
    
    // in game.cpp:
    void setUpScreen(Position tl, Position br);
    void fireLaser();
    void asteroidBelt();
    Rock* createRock(int whichRock, Position pInit, Velocity vInit, bool isInitial);
    void wrapObjects();
    void wrap(MovingObject* obj);
    void handleCollisions();
    bool checkCollision(MovingObject* obj1, MovingObject* obj2);
    double getClosestDistance(const MovingObject &obj1, const MovingObject &obj2);
    
    // "bring out ur deaaaaaaaaaad"
    void cleanUpZombies();
    void cleanUpShip();
    void cleanUpLasers();
    void cleanUpRocks();
    void splitRock(Rock & rock, MovingObject & obj);
    
    // helps us reset everything
    void reset();
    void resetShip();
    void resetAllRocks();
    void removeAllRocks();
    void removeAllLasers();
    void resetScore();

public:
    Game(Position topLeft, Position bottomRight) {
        /* Set up the initial conditions of the game */
        setUpScreen(topLeft, bottomRight);
        
        /* GAME OBJECTS */
        ship = new Ship();
        asteroidBelt();
    }
    
    ~Game() {}
    
    void update() {
        if (ship != NULL) ship->update();
        
        // update lasers
        for (std::vector<Laser>::iterator it = lasers.begin(); it < lasers.end(); ++it) {
            it->update(); // no (*it)-> here, laser vector is not *pointer vector
        }
        
        // update rocks
        for (std::vector<Rock*>::iterator it = rocks.begin(); it < rocks.end(); ++it) {
            if (*it != NULL) (*it)->update(); // (*it)-> requred, rocks vector is a *pointer vector
        }

        wrapObjects();
        handleCollisions();
        cleanUpZombies();
        
        // TODO: handle game states
        // for example: when 0 rocks are on the screen, initiate next—level sequence
    }

    // 'const Interface & ui'
    // this is
    void display(const Interface & ui) {
        if (ship != NULL) ship->display();
        
        // display lasers
        for (std::vector<Laser>::iterator it = lasers.begin(); it < lasers.end(); ++it) {
            it->display();
        }   
        
        // display rocks
        for (std::vector<Rock*>::iterator it = rocks.begin(); it < rocks.end(); ++it) {
            if (*it != NULL) (*it)->display();
        }
        
        level.display();
        score.display();
    }
    
    void handleInput(const Interface & ui) {
        
        /* heldKeys defined/handled in uiInteract.cpp/.h */
        
        // reset
        if (ui.getHeldKey(R)) reset();
        
        // quit
        if (ui.getHeldKey(ESC)) exit(0);
        
        /* ship controls */
        // handle NULL ship
        if (ship != NULL) {
            
            // up
            // accelerate ship
            if (ui.getHeldKey(UP)) ship->accelerate();
            
            // down
            // apply ship 'brakes'
            if (ui.getHeldKey(DOWN)) ship->applyBrakes();

            // space
            // fire laser
            if (ui.getHeldKey(SPACE)) fireLaser();

            // left / right
            // rotate (accordingly)
            if (ui.getHeldKey(LEFT) || ui.getHeldKey(RIGHT)) {
                if (ui.getHeldKey(LEFT))  ship->rotate(LEFT);
                if (ui.getHeldKey(RIGHT)) ship->rotate(RIGHT);
            } else ship->stopRotating();
        }
    }
};


#endif /* game_hpp */
