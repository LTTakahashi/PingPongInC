#include "pingpong.h"

GameState gameState;

int main() {
    // Initialize random seed
    srand(time(NULL));

    // Initialize the game state
    initGame(&gameState);

    // Main game loop
    while (gameState.running) {
        // Handle user input
        handleInput(&gameState);

        // Update game state
        updateGame(&gameState);

        // Render the game to the console
        renderGame(&gameState);

        // Simple way to control game speed, not ideal for real games
#ifdef _WIN32
        Sleep(100); // Sleep 100 milliseconds (Windows-specific)
#else
        usleep(100 * 1000); // Sleep 100 milliseconds (POSIX-specific)
#endif
    }

    return 0;
}