#ifndef PINGPONG_H
#define PINGPONG_H
#define _CRT_NO_SECURE_WARNINGS
#include <stdlib.h> 
//#include <ncurses.h>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>


#include <time.h>

#include <stdbool.h>
// Game settings
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define PADDLE_HEIGHT 4
#define PADDLE_WIDTH 1
#define BALL_SPEED 1
#define PADDLE_SPEED 1  // Speed at which the paddles can move
#define FRAME_DELAY 1000/60 // Frame delay for 60 FPS

// Enumeration for direction, can be useful for paddle movement and AI decision making
typedef enum {
    UP,
    DOWN,
    NONE // Useful for no movement
} Direction;

// Game object structures
typedef struct {
    int x, y;           // Position
    int width, height;  // Size
    Direction dir;      // Direction of movement
} Paddle;

typedef struct {
    int x, y;       // Position
    int velX, velY; // Velocity
} Ball;

typedef struct {
    Paddle playerPaddle;
    Paddle aiPaddle;
    Ball ball;
    bool running; // Game state flag
} GameState;

Paddle playerPaddle;
Paddle aiPaddle;
Ball gameBall;

// Function prototypes

/**
 * Initializes game objects and state.
 */
void initGame(GameState* gameState);

/**
 * Updates the game state, including moving the paddles and the ball, and checking for collisions.
 */


void updateBallPosition(Ball* ball);
void checkBallCollisions(Ball* ball, Paddle* playerPaddle, Paddle* aiPaddle);
void updateAIPaddlePosition(Paddle* aiPaddle, Ball ball);

/**
 * Renders the game state to the screen.
 */
void clearScreen();
void drawAtPosition(int x, int y, char symbol);
void renderGame(const GameState* gameState);
/**
 * Handles player input, potentially adjusting the direction of the player's paddle.
 */
void handleInput(GameState* gameState);

/**
 * Moves the paddle based on its current direction.
 * @param paddle A pointer to the paddle to be moved.
 */
void movePaddle(Paddle* paddle, int direction);
void checkBallCollisions();
void resetBall(Ball* ball, bool playerScored);
void moveBall(Ball* ball);
/**
 * Moves the ball according to its velocity and handles collisions with walls and paddles.
 */


/**
 * Checks for collisions between the ball and the paddles or the walls, and adjusts the game state accordingly.
 */


/**
 * Resets the game state after a score or at the start of a new game.
 */
void resetBall(Ball* ball);

#endif // PINGPONG_H