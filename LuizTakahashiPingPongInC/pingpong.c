#include "pingpong.h"

void initGame(GameState* gameState) {
    // Initialize player paddle
    playerPaddle.x = 2;
    playerPaddle.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    playerPaddle.width = PADDLE_WIDTH;
    playerPaddle.height = PADDLE_HEIGHT;

    // Initialize AI paddle
    aiPaddle.x = SCREEN_WIDTH - 3 - PADDLE_WIDTH; // Position it on the right
    aiPaddle.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    aiPaddle.width = PADDLE_WIDTH;
    aiPaddle.height = PADDLE_HEIGHT;

    // Initialize the ball in the center of the screen
    gameBall.x = SCREEN_WIDTH / 2;
    gameBall.y = SCREEN_HEIGHT / 2;
    gameBall.velX = (rand() % 2 == 0) ? BALL_SPEED : -BALL_SPEED; // Random initial direction
    gameBall.velY = (rand() % 2 == 0) ? BALL_SPEED : -BALL_SPEED;
}

void updateGame(GameState* gameState) {
    // Update ball position
    updateBallPosition(&gameState->ball);

    // Check for collisions (with walls, paddles)
    checkBallCollisions(&gameState->ball, &gameState->playerPaddle, &gameState->aiPaddle);

    // Update AI paddle position to follow the ball
    updateAIPaddlePosition(&gameState->aiPaddle, gameState->ball);

    // Player paddle update would be based on input handled elsewhere in your game loop
}

void updateBallPosition(Ball* ball) {
    // Move the ball according to its velocity
    ball->x += ball->velX;
    ball->y += ball->velY;
}



void updateAIPaddlePosition(Paddle* aiPaddle, Ball ball) {
    // Basic AI to move the paddle towards the ball
    if (aiPaddle->y + PADDLE_HEIGHT / 2 < ball.y) {
        aiPaddle->y += PADDLE_SPEED; // Move down
    }
    else if (aiPaddle->y + PADDLE_HEIGHT / 2 > ball.y) {
        aiPaddle->y -= PADDLE_SPEED; // Move up
    }

    // Ensure the AI paddle stays within the screen bounds
    if (aiPaddle->y < 0) {
        aiPaddle->y = 0;
    }
    else if (aiPaddle->y > SCREEN_HEIGHT - PADDLE_HEIGHT) {
        aiPaddle->y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    }
}

void renderGame(const GameState* gameState) {
    clearScreen(); // Clear the console before rendering the new frame

    // Render player paddle
    for (int i = 0; i < gameState->playerPaddle.height; i++) {
        drawAtPosition(gameState->playerPaddle.x, gameState->playerPaddle.y + i, '|');
    }

    // Render AI paddle
    for (int i = 0; i < gameState->aiPaddle.height; i++) {
        drawAtPosition(gameState->aiPaddle.x, gameState->aiPaddle.y + i, '|');
    }

    // Render ball
    drawAtPosition(gameState->ball.x, gameState->ball.y, 'O');

    fflush(stdout); // Ensure everything is printed to the screen
}

void clearScreen() {
    // Portable way to clear the screen
#ifdef _WIN32
    system("cls");
#else
// Assume POSIX
    system("clear");
#endif
}

void drawAtPosition(int x, int y, char symbol) {
    // Move cursor to the correct position and draw the symbol
    // Note: This is a very basic and not performance-optimized way to render characters in console applications.
    // It's intended for simplicity and demonstration purposes.
    printf("\033[%d;%dH%c", y + 1, x + 1, symbol);
}




void handleInput(GameState* gameState) {
    // Check if a key has been pressed
    if (_kbhit()) {
        char ch = _getch(); // Get the pressed key without waiting for Enter

        // Move the player paddle up or down based on the key press
        switch (ch) {
        case 'w': // 'w' key moves the paddle up
            if (gameState->playerPaddle.y > 0) {
                gameState->playerPaddle.y -= PADDLE_SPEED;
            }
            break;
        case 's': // 's' key moves the paddle down
            if (gameState->playerPaddle.y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
                gameState->playerPaddle.y += PADDLE_SPEED;
            }
            break;
        default:
            // Handle other keys if necessary
            break;
        }
    }
}

void movePaddle(Paddle* paddle, int direction) {
    // Calculate new position
    int newY = paddle->y + (direction * PADDLE_SPEED);

    // Ensure the paddle stays within the game boundaries
    if (newY < 0) {
        newY = 0;
    }
    else if (newY > SCREEN_HEIGHT - paddle->height) {
        newY = SCREEN_HEIGHT - paddle->height;
    }

    // Update paddle position
    paddle->y = newY;
}

void checkBallCollisions() {
    // Check collision with player paddle
    if (gameBall.x == playerPaddle.x + PADDLE_WIDTH && gameBall.y >= playerPaddle.y && gameBall.y <= playerPaddle.y + PADDLE_HEIGHT) {
        gameBall.velX = -gameBall.velX; // Reverse ball's horizontal direction
        // Optionally adjust gameBall.velY based on where it hit the paddle for more dynamic gameplay
    }

    // Check collision with AI paddle
    if (gameBall.x == aiPaddle.x - 1 && gameBall.y >= aiPaddle.y && gameBall.y <= aiPaddle.y + PADDLE_HEIGHT) {
        gameBall.velX = -gameBall.velX; // Reverse ball's horizontal direction
        // Similar optional adjustment for gameBall.velY
    }

    // Check for scoring conditions
    if (gameBall.x <= 0) {
        // Player scores
        // Reset ball to the center and adjust velocity as needed
        resetBall(&gameBall, true); // Assuming true indicates player scored
    }
    else if (gameBall.x >= SCREEN_WIDTH - 1) {
        // AI scores
        // Reset ball to the center and adjust velocity as needed
        resetBall(&gameBall, false); // Assuming false indicates AI scored
    }
}

// Function to reset the ball after a score


void moveBall(Ball* ball) {
    // Update the ball's position based on its velocity
    ball->x += ball->velX;
    ball->y += ball->velY;

    // Check for collisions with the top or bottom of the screen
    if (ball->y <= 0 || ball->y >= SCREEN_HEIGHT - 1) {
        ball->velY = -ball->velY; // Reverse the Y velocity if it hits top/bottom
    }


}


void resetBall(Ball* ball) {
    // Reset the ball position to the center of the screen
    ball->x = SCREEN_WIDTH / 2;
    ball->y = SCREEN_HEIGHT / 2;

    // Set the ball's velocity to a new, randomly determined direction
    ball->velX = BALL_SPEED * ((rand() % 2) * 2 - 1); // Either -BALL_SPEED or BALL_SPEED
    ball->velY = BALL_SPEED * ((rand() % 2) * 2 - 1); // Either -BALL_SPEED or BALL_SPEED

    // Optionally introduce slight variation in speed or direction
    // This example introduces a small variation in the Y velocity
    int variation = (rand() % 3) - 1; // Randomly -1, 0, or 1
    ball->velY += variation;

    // Ensure the ball doesn't move too slowly in Y direction, which could make the game less challenging
    if (ball->velY == 0) {
        ball->velY = ((rand() % 2) * 2 - 1) * BALL_SPEED; // Reset to either -BALL_SPEED or BALL_SPEED if 0
    }
}