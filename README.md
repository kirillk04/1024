# 1024 C++
 
1024 Game in C++
Overview
This C++ program implements the classic 1024 game with a console-based interface. The goal of the game is to combine tiles with the same numbers to reach the tile with the value of 1024. The player can move tiles in four directions—up, down, left, and right—to achieve this objective.

How to Play
The game initializes with a 4x4 grid of numbered tiles.
Use arrow keys to shift tiles in the desired direction.
Tiles with the same number will merge into a single tile with a doubled value.
The game ends when the player successfully reaches the 1024 tile or when no more moves are possible.
Implementation Details
The program defines a Board class responsible for managing the game board and its operations.
Tiles are dynamically allocated based on the grid size.
The game randomly places initial tiles on the board.
Players can shift tiles in four directions to merge them.
The game dynamically updates the grid and checks for win/lose conditions.

Game Controls
Use arrow keys (up, down, left, right) to move tiles in the respective direction.
Press 'S' to exit the game.

Customization
You can customize the grid size or initial conditions by modifying the constructor parameters in the source code.
