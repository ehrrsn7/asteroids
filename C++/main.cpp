/**
ASTEROIDS
 */

/*
 TODO:
 
 - ship speed limit (one that works)
 - generate stars that pan upward in background
 - add/fix ui/text elements screen 'overlay':
    - in main menu: wireframe out a design (with instructions for functionality)
    - in resume/pause menus:
        - ship lives, current and high scores are displayed
    - in pause menu:
        - 'PAUSED' is displayed
        - instructions are displayed
 - add game states
 - add input functionality:
    - in main menu: add functionality based off instructions in wireframe
    - in pause/resume menus:
        - 'p' pauses/resumes the game
    - in pause menu:
        - 'r' restarts the game
 - all other functionality is taken care of
 
 ? is mouse input possible
*/

/*****************************************************
 * File: Driver.cpp
 * Author: Br. Burton
 *
 * Description: This file contains the main function
 *  that starts the game and the callback function
 *  that specifies what methods of the game class are
 *  called each time through the game loop.
 ******************************************************/
#include "game.h"
#include <iostream>
#include "ui/uiInteract.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 400

double Position::metersFromPixels = 40.0;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void update(const Interface *pUI, void *p) {
   Game *pGame = (Game *) p;

   pGame->update();
   pGame->handleInput(*pUI);
   pGame->display(*pUI);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv) {
   Position topLeft(-SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
   Position bottomRight(SCREEN_WIDTH/2, -SCREEN_HEIGHT/2);

   Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
   Game game(topLeft, bottomRight);
   std::cout << "Initialization complete.\n";
   ui.run(update, &game);

   return 0;
}
