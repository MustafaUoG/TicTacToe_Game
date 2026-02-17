# ENGG1410: Tic-Tac-Toe Simulation (Mini Project Part 1)

A  C implementation of Tic-Tac-Toe designed for the ENGG*1410 course. This project demonstrates array manipulation, heuristic AI logic, and dynamic memory handling.

## Project Overview
This simulation fulfills the requirements for Mini Project Part #1, focusing on procedural modularity and data abstraction.

### Key Features
* **Dynamic Grid Sizes:** Supports custom board configurations ranging from standard 3x3 up to 10x10.
* **Dual Game Modes:**
    * **PvP:** Two-player mode.
    * **PvAI:** Single-player mode against a logic-driven opponent.
* **Heuristic AI:** The computer opponent utilizes a prioritized decision tree:
    1.  **Win Check:** Executes an immediate winning move if available.
    2.  **Block Check:** Intercepts the player's potential winning move.
    3.  **Random Move:** Falls back to random selection if no strategic option exists.
* **Game Logging:** Exports the final board state to a text file for review (Custom Feature).

## Technical Implementation
The system is structured around the following core components as per design requirements:

* **Board Representation:** A 2D array manages the game states.
* **Win/Draw Detection:** Algorithms evaluate rows, columns, and diagonals (both standard and anti-diagonal) to determine game termination.
* **Input Validation:** Ensures moves are within bounds and targets are empty cells.

## Getting Started

### Compilation
Compile the source using GCC:
```bash
gcc -o tictactoe main.c
